#ifndef WAV_FUNC
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Caio Sobrinho da Silva
//RA: 211044156
using namespace std;

//Struct used for header
typedef struct header_file{
    char riff[4];
    int chunk_size; 
    char format[4];
    char subchunk1_id[4];
    int subchunk1_size;
    short int audio_format;
    short int num_channels;
    int sample_rate;
    int byte_rate;
    short int block_align;
    short int bits_per_sample;
    char subchunk2_id[4];
    int subchunk2_size;
}header;

int getFileSize(FILE *arq);
int getFileSizeWithoutHeader(FILE *arq, int headerSize);
void copyAudio(FILE *arq, FILE *copy);
void invertAudio(FILE *arq, FILE *inverted);
void wavHeader(FILE *arq);
void normalizeAudio(double *audio, int size, FILE *fp);
void translateAudioByMean(double *audio, int size, FILE *fp);
double energy(double *input_vector, int length);
void a3(double *s, int M);
double zcr(double* input_vector, int length);
void b3(double *s ,int M);

#endif