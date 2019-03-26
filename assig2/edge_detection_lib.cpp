#include <iostream>
#include <stdlib.h>
#include <cmath>
using namespace std;

double** GaussianFilter (int kernal_size, double sigma) {
	int bound = (kernal_size-1)/2;
	double** Gkernal=0;
	Gkernal = new double*[kernal_size];
	double sum = 0;
	cout<<"Kernal size is: "<<kernal_size<<endl;
	for (int x = -bound; x <= bound; x++){
		Gkernal[x+bound] = new double[kernal_size];

		for (int y = -bound; y <= bound; y++){
			double expo =(x*x+y*y)/(2*sigma*sigma);
			Gkernal[x+bound][y+bound] =  exp(-expo)/(sigma*sqrt(2*M_PI));
			sum += Gkernal[x+bound][y+bound];
			cout<< Gkernal[x+bound][y+bound]<<" ";
		}
		cout<< endl;
	}
	cout<<"Sum of kernal is: "<<sum<<endl<<endl;
	cout<<"Normalized kernal is: "<<endl;
	for (int x = 0; x<kernal_size; x++){
		for (int y = 0; y<kernal_size; y++){
			Gkernal[x][y]/=sum;
			cout<< Gkernal[x][y]<<" ";
		}
		cout<< endl;
	}
	return Gkernal;
}



int main(){
	int kernal_size = 3;
	double sigma = 1;
	double** filter = GaussianFilter(kernal_size,sigma);
	cout<<endl<<"GKernal is passed to filter: "<<endl;
	for (int i = 0; i<kernal_size; i++){
		for(int j = 0; j<kernal_size; j++){
			cout<< filter[i][j]<<" ";
		}
		cout<<endl;
	}
	
	return 0;
}