///////////////////////////////////////////////////
//////////////////////////////////////////////////
class svm
{
private:
	
	double* a;
	double** b;
	double** w;
	double** fis;

	int number_of_input_neurons;
	int number_of_hidden_neurons;
	int number_of_output_neurons;
	
public:
	svm();
	~svm();
	void init(int,int,int);
	void train(double*,double*);//input vector, desired output vector 
	void pass(double*,double*);//input vector, output vector.	
};

