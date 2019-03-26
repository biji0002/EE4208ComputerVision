#include <iostream>
#include <stdlib.h>
#include <cmath>
using namespace std;

void GaussianFilter (int kernal_size, double sigma, int img, int img_row, int img_col) {
	int bound = (kernal_size-1)/2;
	double Gkernal[kernal_size][kernal_size];
	double sum = 0;
	cout<<"Kernal size is: "<<kernal_size<<endl;
	for (int x = -bound; x <= bound; x++){
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

}





int main(){
	int kernal_size = 7;
	double sigma = 1;
	double filter[kernal_size][kernal_size];
	GaussianFilter(kernal_size,sigma,1,1,1);
	
	return 0;
}