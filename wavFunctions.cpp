#ifndef WAV_FUNC
#include <iostream>
#include <cmath>
#include "wavFunctions.h"
#include <math.h>

using namespace std;

int getFileSize(FILE *arq){
    int fileSize = 0;
    fseek(arq, 0, SEEK_END);
    fileSize = ftell(arq);
    
    fseek(arq, 0, SEEK_SET);
    return fileSize;
}

int getFileSizeWithoutHeader(FILE *arq, int headerSize) {
    fseek(arq, 0, SEEK_END);
    int fileSize = ftell(arq);
    fseek(arq, headerSize, SEEK_SET);
    int dataSize = fileSize - headerSize;
    return dataSize;
}

int wavHeader(FILE *arq, int headerSize){
    header header;

    fread(&header,1, sizeof(header), arq);
    cout << "\nFile type: "<< header.riff[0]<<header.riff[1]<<header.riff[2]<<header.riff[3];
    cout << "\nFile size, without the header: "<<getFileSize(arq)-headerSize;
    fseek(arq, sizeof(header), SEEK_SET);
    cout << "\nSubtype: "<< header.format[0]<<header.format[1]<<header.format[2]<<header.format[3];
    cout << "\nIdentifier: " << header.subchunk1_id[0]<<header.subchunk1_id[1]<<header.subchunk1_id[2]<<header.subchunk1_id[3];
    cout << "\nChunk Size: "<< header.subchunk1_size;
    cout << "\nAudio Format(Form of compression): "<<header.audio_format;
    cout << "\nNumber of channels: "<< header.num_channels;
    if(header.num_channels == 1){
        cout <<", Mono";
    }
    else
        cout <<", Stereo";
    cout << "\nSample rate: " << header.sample_rate;
    header.byte_rate = (header.sample_rate)*(header.num_channels)*(header.bits_per_sample/8);
    cout << "\nByte rate: " << header.byte_rate;
    header.block_align = (header.num_channels)*(header.bits_per_sample/8);
    cout << "\nBlock Align: " << header.block_align;
    cout << "\nBits per sample: " << (header.bits_per_sample) << " bits";
    cout << "\nSubchunk id: " <<header.subchunk2_id[0]<<header.subchunk2_id[1]<<header.subchunk2_id[2]<<header.subchunk2_id[3];
    cout <<"\nData size: " <<header.subchunk2_size << endl;
    return header.subchunk2_size;
}

void copyAudio(FILE *arq, FILE *copy){
    header header;
    fseek(arq, 0, SEEK_SET);
    fread(&header, 1, sizeof(header), arq);
    short int data[header.subchunk2_size];
    fwrite(&header, 1, sizeof(header), copy);
    fread(&data, header.subchunk2_size, 1, arq);
    fwrite(data, 1, header.subchunk2_size, copy);
}

void invertAudio(FILE *arq, FILE *inverted){
    header header;
    fseek(arq, 0, SEEK_SET);
    fread(&header, 1, sizeof(header), arq);
    fwrite(&header, 1, sizeof(header), inverted);
    short int data[header.subchunk2_size];
    short int invertedData[header.subchunk2_size];
    fread(&data, header.subchunk2_size, 1, arq);


    int i = 0;
    int j = 1;
    while (i < header.subchunk2_size && j < header.subchunk2_size)
    {
        invertedData[i] = data[j];
        invertedData[j] = data[i];
        i+=2;
        j+=2;
    }
    fwrite(invertedData, 1, header.subchunk2_size, inverted);
}

void normalizeSignal(double *signal, int size, double targetAmplitude, FILE *arq) {
    double maxAmplitude = 0.0;

    // Encontre o valor máximo absoluto no sinal.
    for (int i = 0; i < size; i++) {
        maxAmplitude = fmax(maxAmplitude, fabs(signal[i]));
    }

    // Verifique se o sinal já está normalizado.
    if (maxAmplitude == 0.0) {
        return;
    }

    // Normalize o sinal dividindo cada amostra pelo valor máximo.
    for (int i = 0; i < size; i++) {
        signal[i] /= maxAmplitude;
    }

    // Aplique o ganho para atingir a amplitude alvo, se especificado.
    if (targetAmplitude != 1.0) {
        for (int i = 0; i < size; i++) {
            signal[i] *= targetAmplitude;
            fprintf(arq, "%lf\n", signal[i]);
        }
    }
    
}

void normalizeAudio(double *audio, int size, FILE *arq){
    double maxAmplitude = 0.0;

    for(int i = 0; i < size; i++){
        maxAmplitude = std::max(maxAmplitude, std::abs(audio[i]));
    }
    for(int i = 0; i < size; i++){
        int j = i+1;
        audio[i] = audio[i]/maxAmplitude;
        fprintf(arq, "% lf,", audio[i]);

        if (j % 4 == 0)
        {
            fprintf(arq, "\n");
        }
        
    }
}

void translateAudioByMean(double* audio, int size, FILE *arq) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += audio[i];
    }
    double mean = sum / size;

    for (int i = 0; i < size; i++) {
        audio[i] -= mean;
        fprintf(arq, "%.10lf\n", audio[i]);
    }
}
double energy(double *input_vector, int length){
    double e=0;
    for(int i = 0; i < length; i++)
        e += pow(input_vector[i],2);
    return(e);
}

void a3(double *s, int M){
    int L = 0;
    double C = 5; //5%
    int T = ((100/C)-((int)(100/C))==0)?(100/C)-1:(int)(100/C); //number of elements in T
    double *f = new double[T]; //dynamic vetor declaration
    double z =energy(&s[0], M)*((double)(C)/100);
    
    printf("\nValues of A3 method to inspect constancy in action of the physical entity responsible for generating the signal: \n");
    for (int k = 0; k < T; k++)
    {
        while (energy(&s[0], L) < ((k+1)*z))
            L++;
        f[k] = (double)(L)/(double)(M);
        printf("%.10lf\n", f[k]);
    }
    
}

double zcr(double* input_vector, int length){
    double z = 0;
    for(int i=0;i<length - 1;i++)
        z += (input_vector[i] * input_vector[i + 1] < 0)?1:0;
    return(z);
}

void b3(double *s ,int M){
    double mean = 0;

    for(int k = 0; k < M; k++)
        mean+=s[k]/(double)(M);
    for(int k = 0; k < M; k++)
        s[k]-= mean;

    int L = 0;
    double C = 5;
    int T = ((100/C) - ((int)(100/C)) == 0)?(100/C) - 1 : (int)(100/C);
    double *f = new double[T];
    double z = zcr(&s[0],M)*((double)(C)/100);

    printf("\nValues of B3 method inspect the constancy in frequency of the physical entity responsible for generating signal: \n");
    for(int k = 0; k < T; k++){
        while(zcr(&s[0], L)<((k + 1)*z))
            L++;
        f[k] = (double)(L)/(double)(M);
        printf("%.10lf\n", f[k]);

    }
}

#endif