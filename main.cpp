#include <iostream>
#include "wavFunctions.h"

#define headerSize 44

int main(){
    FILE *wavFile;
    FILE *wavCopia;
    FILE *invert;
    FILE *texto;
    FILE *normal;
    FILE *base;
    
    //Opening the archives for reading and writing
    wavFile = fopen("1984-a_n.wav", "rb");
    wavCopia = fopen("copia.wav", "wb");
    invert = fopen("invert.wav", "wb");
    texto = fopen("saida.txt", "w");
    normal = fopen("normal.txt", "w");
    base = fopen("base.txt", "w");

    if(wavFile == NULL){
        cout << "\nCannot open this file!";
    }

    int dataSize = wavHeader(wavFile, headerSize);
    fclose(wavFile);
    wavFile = fopen("1984-a_n.wav", "rb");

    copyAudio(wavFile, wavCopia);
    invertAudio(wavFile, invert);

    fclose(wavFile);

    wavFile = fopen("1984-a_n.wav", "r");
    int16_t *audio = (int16_t *)malloc(dataSize);
    fseek(wavFile, headerSize, SEEK_SET);
    fread(audio, dataSize, 1, wavFile);

    double *audioDouble = (double*)malloc(dataSize*sizeof(double));
    for (int i = 0; i < dataSize; i++) {
        audioDouble[i] = static_cast<double>(audio[i]);
        fprintf(base, "%d\n", audio[i]);
    }

    normalizeAudio(audioDouble, dataSize, normal);
    translateAudioByMean(audioDouble, dataSize, texto);
    a3(audioDouble, dataSize);
    b3(audioDouble, dataSize);
    
    fclose(wavFile);
    fclose(wavCopia);
    fclose(invert);
    fclose(texto);
    fclose(normal);
    fclose(base);

    return 0;
}