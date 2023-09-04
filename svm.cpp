#include<stdio.h>
#include<math.h>
#include<string.h>
#include "svm.c"
int main()
{
double V1[] = 	
		{
0.1, 0.2, 0.3, 0.5,
0.4, 0.5, 0.6, 0.5, 
0.7, 0.8, 0.9, 0.2,  
0.2, 0.4, 0.6, 0.2,
0.8, 0.1, 0.3, 0.8,
0.5, 0.7, 0.9, 0.9
		  }; //6 exemplos de treinamento com 4 elementos (parametros) cada   

double V2[] = 
		{
1,
1,
1, 
-1,
-1,
-1,
		  };//os 3+3 resultados correspondentes. -1 significa classe A e 1 significa classe B. No caso, sao duas classes

svm n;
int numero_de_amostras_de_cada_exemplo_de_entrada=4;  
int numero_de_exemplos_de_treinamento=3+3; 
int numero_de_amostras_de_cada_exemplo_de_saida=1; //uma saida pra  cada  entrada 
n.init(numero_de_amostras_de_cada_exemplo_de_entrada,numero_de_exemplos_de_treinamento,numero_de_amostras_de_cada_exemplo_de_saida); 
n.train(V1,V2); // treinamento da rede
double V3[]={0.5, 0.7, 0.9, 0.9}; //caso de teste
double* V4 = new double[numero_de_amostras_de_cada_exemplo_de_saida]; // vetor onde a saida vai ser carregada. Mesmo tendo um so elemento tem que ser vetor...
n.pass(V3,V4);
for(int i=0;i<numero_de_amostras_de_cada_exemplo_de_saida;i++)//ajuste para realizar a separacao em dois planos somente. Como a saida deveria ser 1 ou -1, o meio do hiperplano separador esta centrado em 0. Sendo assim, e ja que podem aparecer valores nao pertencentes aos exemplos de treinamento, tudo que estiver de 0 para cima e' considerado como pertencente a classe 1 e tudo que estiver abaixo de 0 e' considerado como pertencente a classe -1.
      std::cout<<"\nResultado: SAIDA["<<i<<"] = "<<((V4[i]<0)?-1:1); //saida
std::cout<<"\n\n";
}

 