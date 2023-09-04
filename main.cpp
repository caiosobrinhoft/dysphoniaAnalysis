#include <iostream>
#include "wavFunctions.h"
#include "svm.c"

#define headerSize 44

int main(){
    FILE *wavFile;
    FILE *wavCopia;
    FILE *invert;
    FILE *texto;
    FILE *normal;
    FILE *base;
    
    //Opening the archives for reading and writing
    wavFile = fopen("491-a_lhl.wav", "rb");
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
    wavFile = fopen("491-a_lhl.wav", "rb");

    copyAudio(wavFile, wavCopia);
    invertAudio(wavFile, invert);

    fclose(wavFile);

    wavFile = fopen("491-a_lhl.wav", "rb");
    int16_t *audio = (int16_t *)malloc(dataSize);
    fseek(wavFile, headerSize, SEEK_SET);
    fread(audio, dataSize, 1, wavFile);

    double *V3 = new double[dataSize];

    double *audioDouble = (double*)malloc(dataSize*sizeof(double));
    double *audioDoubleCopy = (double*)malloc(dataSize*sizeof(double));

    for (int i = 0; i < dataSize; i++) {
        audioDouble[i] = static_cast<double>(audio[i]);
        audioDoubleCopy[i] = static_cast<double>(audio[i]);
    }

    normalizeAudio(audioDouble, dataSize, normal);
    translateAudioByMean(audioDouble, dataSize, texto);
    normalizeAudio(audioDoubleCopy, dataSize, normal);
    translateAudioByMean(audioDoubleCopy, dataSize, texto);

    /*for (int i = 0; i < dataSize; i++){
        V3[i] = audioDouble[i]; }//usado "puro"
        */
    
    a3(audioDouble, dataSize);
    //b3(audioDoubleCopy, dataSize);
    
    for (int i = 0; i < dataSize; i++) {
        V3[i] = audioDouble[i];
        //V3[i] = audioDoubleCopy[i];//usado para diferentes a3 e b3
    }

    fclose(wavFile);
    fclose(wavCopia);
    fclose(invert);
    fclose(texto);
    fclose(normal);
    fclose(base);

double V1[] = 	
	{   
        0.029327, 0.032867, 0.030334, 0.022217,
        0.020691, 0.024902, 0.027924, 0.025940,
        0.021454, 0.017487, 0.014954, 0.010773,
        0.000336,-0.012085,-0.021332,-0.031189,
        -0.046173,-0.059082,-0.066742,-0.071228,
        -0.364532,-0.445984,-0.528900,-0.610138,
        -0.693665,-0.767639,-0.809906,-0.825165,
        -0.828003,-0.817719,-0.787567,-0.751678,
        -0.713043,-0.643463,-0.542267,-0.431122,
        -0.339355,-0.252197,-0.146912,-0.035492,
        -0.298157,-0.230909,-0.171316,-0.123792,
        -0.079900,-0.028904, 0.023649, 0.061377,
        0.100467, 0.140693, 0.178486, 0.202783,
        0.222085, 0.237754, 0.247908, 0.248070,
        0.241030, 0.235678, 0.224908, 0.203043,
        -0.000825, 0.004290, 0.011089, 0.018613,
        0.026138, 0.033068, 0.039240, 0.044916,
        0.050625, 0.056269, 0.061681, 0.066763,
        0.072572, 0.077819, 0.082275, 0.087093,
        0.092274, 0.096465, 0.100855, 0.104782,
        -0.007690,-0.024811,-0.043732,-0.063232,
        -0.080475,-0.094971,-0.106293,-0.115723,
        -0.124207,-0.130035,-0.133179,-0.134399,
        -0.133118,-0.132294,-0.129913,-0.125793,
        -0.122498,-0.120605,-0.118164,-0.114594,
        0.419016, 0.435956, 0.446150, 0.447083,
        0.436142, 0.416063, 0.386038, 0.342306,
        0.290585, 0.231498, 0.167687, 0.103565,
        0.041028,-0.014702,-0.064650,-0.111895,
        -0.152395,-0.182575,-0.207845,-0.228359,
        -0.346908,-0.259305,-0.155004,-0.040481,
        0.076898, 0.170416, 0.242727, 0.303730,
        0.362038, 0.414068, 0.454630, 0.487626,
        0.506579, 0.513983, 0.510161, 0.493018,
        0.456239, 0.394712, 0.313710, 0.224498,
        0.257092, 0.265042, 0.270239, 0.270641,
        0.263619, 0.250719, 0.232530, 0.211000,
        0.187645, 0.161784, 0.129396, 0.090080,
        0.050701, 0.012126,-0.033285,-0.083305,
        -0.127540,-0.169332,-0.212114,-0.253813,
        -0.040135,-0.054028,-0.066966,-0.079829,
        -0.091003,-0.097839,-0.102249,-0.109086,
        -0.120406,-0.130256,-0.138195,-0.146060,
        -0.150544,-0.159291,-0.161791,-0.157454,
        -0.148192,-0.144590,-0.146869,-0.147898,
        -0.080455,-0.040699,-0.039867,-0.068533,
        -0.068922,-0.044414,-0.041198,-0.074522,
        -0.117605,-0.119102,-0.080566,-0.053008,
        -0.069032,-0.113502,-0.129304,-0.093818,
        -0.062822,-0.092043,-0.139063,-0.137122,
        -0.195036,-0.195772,-0.199194,-0.206806,
        -0.205943,-0.198043,-0.196411,-0.197915,
        -0.197051,-0.191678,-0.187584,-0.190654,
        -0.191070,-0.184801,-0.173031,-0.161933,
        -0.155728,-0.142743,-0.125983,-0.111943,      
        -0.350702,-0.448248,-0.586051,-0.684136,
        -0.732876,-0.770978,-0.781548,-0.750648,
        -0.733751,-0.775994,-0.819987,-0.817934,
        -0.793430,-0.753240,-0.659396,-0.534518,
        -0.474200,-0.449157,-0.343600,-0.196540,
        -0.296754,-0.284556,-0.273906,-0.264104,
        -0.252791,-0.236467,-0.219811,-0.204076,
        -0.189078,-0.173122,-0.154660,-0.137967,
        -0.120610,-0.105354,-0.089509,-0.076796,
        -0.064451,-0.056675,-0.049637,-0.042267,
        -0.048662,-0.051649,-0.058307,-0.064032,
        -0.072869,-0.081269,-0.089172,-0.095893,
        -0.099253,-0.100933,-0.106347,-0.115993,
        -0.130678,-0.138457,-0.141942,-0.146360,
        -0.153889,-0.165028,-0.172869,-0.178034,
        0.130829, 0.103356, 0.069749, 0.066150,
        0.110351, 0.186081, 0.243410, 0.237936,
        0.208485, 0.235756, 0.301298, 0.322435,
        0.275497, 0.222172, 0.203670, 0.229217,
        0.263230, 0.266677, 0.241535, 0.236060,
        -0.060773,-0.059532,-0.057297,-0.054690,
        -0.051462,-0.047303,-0.044199,-0.041281,
        -0.037929,-0.035198,-0.030728,-0.026507,
        -0.022782,-0.018375,-0.012540,-0.006766,
        -0.002173, 0.001117, 0.003973, 0.004718,
        -0.040135,-0.054028,-0.066966,-0.079829,
-0.091003,-0.097839,-0.102249,-0.109086,
-0.120406,-0.130256,-0.138195,-0.146060,
-0.150544,-0.159291,-0.161791,-0.157454,
-0.148192,-0.144590,-0.146869,-0.147898,
-0.147163,-0.144443,-0.137019,-0.125698,
-0.110923,-0.098868,-0.096369,-0.097030,
-0.092326,-0.084607,-0.080859,-0.079609,
-0.073140,-0.064834,-0.061011,-0.067407,
-0.076301,-0.084460,-0.086298,-0.088062,
-0.088577,-0.088136,-0.084240,-0.085857,
-0.092914,-0.101367,-0.106954,-0.114746,
-0.120112,-0.124228,-0.129080,-0.130256,
-0.138709,-0.154954,-0.167524,-0.171935,
-0.170538,-0.172743,-0.172596,-0.166642,
-0.153999,-0.146428,-0.138415,-0.130109,
-0.120038,-0.111511,-0.103205,-0.094825,
-0.086151,-0.077698,-0.078359,-0.076522,
-0.070641,-0.059321,-0.048662,-0.042855,
-0.037415,-0.033152,-0.028889,-0.029036,
    };
          
    double V2[] = 
    {
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1, 
    -1,
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1, 
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    };//os 3+3 resultados correspondentes. -1 significa classe A e 1 significa classe B. No caso, sao duas classes

    svm n;
    int numero_de_amostras_de_cada_exemplo_de_entrada=4;  
    int numero_de_exemplos_de_treinamento=40+60; 
    int numero_de_amostras_de_cada_exemplo_de_saida=1; //uma saida pra  cada  entrada 
    n.init(numero_de_amostras_de_cada_exemplo_de_entrada,numero_de_exemplos_de_treinamento,numero_de_amostras_de_cada_exemplo_de_saida); 
    n.train(V1,V2); // treinamento da rede
    double* V4 = new double[numero_de_amostras_de_cada_exemplo_de_saida]; // vetor onde a saida vai ser carregada. Mesmo tendo um so elemento tem que ser vetor...
    n.pass(V3,V4);
    for(int i=0;i<numero_de_amostras_de_cada_exemplo_de_saida;i++)//ajuste para realizar a separacao em dois planos somente. Como a saida deveria ser 1 ou -1, o meio do hiperplano separador esta centrado em 0. Sendo assim, e ja que podem aparecer valores nao pertencentes aos exemplos de treinamento, tudo que estiver de 0 para cima e' considerado como pertencente a classe 1 e tudo que estiver abaixo de 0 e' considerado como pertencente a classe -1.
        std::cout<<"\nResultado: SAIDA["<<i<<"] = "<<((V4[i]<0)?-1:1); //saida
    std::cout<<"\n\n";
        return 0;
}