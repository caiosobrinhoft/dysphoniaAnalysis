#ifndef WAV_FUNC
#include <iostream>
#include <cmath>
#include "wavFunctions.h"

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

void wavHeader(FILE *arq){
    header header;

    fread(&header,1, sizeof(header), arq);
    cout << "\nFile type: "<< header.riff[0]<<header.riff[1]<<header.riff[2]<<header.riff[3];
    cout << "\nFile size, without the header: "<<getFileSize(arq)-(sizeof(header.riff) + sizeof(header.chunk_size));
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

void normalizeAudio(double *audio, int size, FILE *arq){
    double maxAmplitude = 0.0;

    for(int i = 0; i < size; i++){
        double amplitude = std::abs(audio[i]);
        if(amplitude > maxAmplitude)
            maxAmplitude = amplitude;
    }

    for(int i = 0; i < size; i++){
        audio[i] /= maxAmplitude;
        fprintf(arq, "%.10lf\n", audio[i]);
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


#endif