#include <iostream>
#include "wavFunctions.h"

#define headerSize 44

int main(){
    FILE *wavFile;
    FILE *wavCopia;
    FILE *invert;
    FILE *texto;
    FILE *normal;
    
    //Opening the archives for reading and writing
    wavFile = fopen("applause.wav", "rb");
    wavCopia = fopen("copia.wav", "wb");
    invert = fopen("invert.wav", "wb");
    texto = fopen("saida.txt", "wb");
    normal = fopen("normal.txt", "wb");

    if(wavFile == NULL){
        cout << "\nCannot open this file!";
    }

    wavHeader(wavFile);
    fclose(wavFile);
    wavFile = fopen("applause.wav", "rb");

    copyAudio(wavFile, wavCopia);
    invertAudio(wavFile, invert);

    fclose(wavFile);

    wavFile = fopen("applause.wav", "rb");
    int dataSize;
    
    dataSize = getFileSizeWithoutHeader(wavFile, headerSize);
    short int audio[dataSize]; 
    fread(audio, sizeof(short int), dataSize, wavFile);

    double audioDouble[dataSize];
    for (int i = 0; i < dataSize; i++) {
        audioDouble[i] = static_cast<double>(audio[i]);
    }

    normalizeAudio(audioDouble, dataSize, normal);
    translateAudioByMean(audioDouble, dataSize, texto);

    fclose(wavFile);
    fclose(wavCopia);
    fclose(invert);
    fclose(texto);
    fclose(normal);

    return 0;
}