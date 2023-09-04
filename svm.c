#include "svm.h"
#include<math.h>
#include<iostream>

double svmfunction(double*,double*,int,double);
double dist(double*,double*,int);
void linear_system_solver(double**, double*, double*, int);
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
svm::svm()
{

}
////////////////////////////////////////////////////////////////
svm::~svm()
{

}
////////////////////////////////////////////////////////////////
void svm::init(int n_i_n,int n_h_n,int n_o_n)
{
number_of_input_neurons=n_i_n;
number_of_hidden_neurons=n_h_n;
number_of_output_neurons=n_o_n;

a=new double[number_of_hidden_neurons];
b=new double*[number_of_hidden_neurons];
for(int i=0;i<number_of_hidden_neurons;i++)
	b[i]=new double[number_of_input_neurons];
w=new double*[number_of_output_neurons];
for(int i=0;i<number_of_output_neurons;i++)
	w[i]=new double[number_of_hidden_neurons];
for(int i=0;i<number_of_output_neurons;i++)
	for(int j=0;j<number_of_hidden_neurons;j++)
		w[i][j]=0;
fis=new double*[number_of_hidden_neurons];
for(int i=0;i<number_of_hidden_neurons;i++)
	fis[i]=new double[number_of_hidden_neurons];
}
////////////////////////////////////////////////////////////////
void svm::pass(double* input_signal, double* output_signal)
{
for(int i=0;i<number_of_output_neurons;i++)
	{
	output_signal[i]=0;
	for(int j=0;j<number_of_hidden_neurons;j++)
		output_signal[i]+=w[i][j]*svmfunction(&input_signal[0],&b[j][0],number_of_input_neurons,a[j]);
	}
}
////////////////////////////////////////////////////////////////
void svm::train(double* input_signal, double* desired_output_signal)
{
//non-supervised training
//centers
int k=0;
for(int i=0;i<number_of_hidden_neurons;i++)
	{
	for(int j=0;j<number_of_input_neurons;j++)
		b[i][j]=input_signal[j+k];
	k+=number_of_input_neurons;
	}	
//variances
for(int i=0;i<number_of_hidden_neurons;i++)
	a[i]=1;
//supervised training
//weights
std::cout<<"\n\n";
double* outs=new double[number_of_hidden_neurons];
double m;
int lcpivo;
int p;
for(int c=0;c<number_of_output_neurons;c++)
	{
	std::cout<<"\nNEURON "<<c;
	p=0;
	for(int i=0;i<number_of_hidden_neurons;i++)
		{
		for(int j=0;j<number_of_hidden_neurons;j++)
			fis[i][j]=svmfunction(&input_signal[p],&b[j][0],number_of_input_neurons,a[j]);
		p+=number_of_input_neurons;
		}

	p=0;
	for(int u=0;u<number_of_hidden_neurons;u++)
		{
		outs[u]=desired_output_signal[p+c];
		p+=number_of_output_neurons;
		}	
									
	linear_system_solver(fis, outs, &w[c][0], number_of_hidden_neurons);
	}
}
//////////////////////////////////////////////////////////////////
double svmfunction(double* input_signal,double* mean,int number_of_input_neurons,double variance) //kernel gaussiano
{
return(exp(-(pow(dist(input_signal,mean,number_of_input_neurons),2)/(2*variance))));
}
//////////////////////////////////////////////////////////////////
double dist(double* x, double* y, int length)
{
double d=0;
for(int i=0;i<length;i++)
	d+=pow((x[i]-y[i]),2);
return(sqrt(d));
}
////////////////////////////////////////////////////////////////
void linear_system_solver(double** m_a, double* m_b, double* r, int order)
{
double** matrix_a = new double*[order];
for(int i=0;i<order;i++)
	matrix_a[i]=new double[order];
for(int i=0;i<order;i++)
  for(int j=0;j<order;j++)
    matrix_a[i][j]=m_a[i][j];

double* matrix_b = new double[order];
for(int i=0;i<order;i++)
  matrix_b[i]=m_b[i];

//escalonando
double m;
int lcpivo=0;
do
   {
    for(int k=lcpivo;k<order-1;k++)
      {
      if(matrix_a[lcpivo][lcpivo]==0)
		m=0;
      else
		m=(-matrix_a[k+1][lcpivo]/matrix_a[lcpivo][lcpivo]);
      for(int j=lcpivo+1;j<order;j++)
		matrix_a[k+1][j]+=matrix_a[lcpivo][j]*m;
      matrix_a[k+1][lcpivo]=0;
      matrix_b[k+1]+=matrix_b[lcpivo]*m;
      }
    lcpivo++;
    }while(lcpivo<order-1);

//resolvendo
for(int i=0;i<order;i++)
   r[i]=matrix_b[i];
if(matrix_a[order-1][order-1]==0)
   r[order-1]=0;
else
   r[order-1]=matrix_b[order-1]/matrix_a[order-1][order-1];
for(int i=order-2;i>=0;i--)
   {
   for(int j=i;j<order-1;j++) 
       r[i]-=matrix_a[i][j+1]*r[j+1];
   if(matrix_a[i][i]==0)
       r[i]=0;
   else
       r[i]/=matrix_a[i][i];
    }
}
/////////////////////////////////////////////////////
