#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <cmath>

using namespace std;
uint8_t img_header[5];

#define row                     *(uint16_t *)(img_header)
#define col                     *(uint16_t *)(img_header + 2)
#define pixel_size              *(uint8_t *)(img_header + 4)

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
	return Gkernal;
}

int main(void)
{



	cout<<endl<<"GKernal is passed to filter: "<<endl;

	//Input the raw image, read the raw image to a matrix
	FILE *input;
	uint8_t get_char;
	input = fopen("raw_images/cana.raw","rb");;

	//read the image header
	for (int i = 0; i < 5; i++)
	{
		img_header[i] = fgetc(input);

	}

	//define all image arrays
	int img[row][col]; 			//Original image
	int img_gaussian[row][col]; //Image after gaussian mask
	int img_sobel[row][col];	//Image afte sobel mask
	int img_nms[row][col];  	//Image after non maximum supression


	//read the image in to 2d array
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			img[i][j] = fgetc(input);     //read the image to an array
		}
		
	}

	//printf("%02x \n", img[row-1][col-2]);

	//Image after gaussian mask
	
	double sigma = 1;
	int kernal_size, gaussianoffset;

	if(sigma <0.8){
		kernal_size = 3;
		gaussianoffset = 1;
	}
	else if(sigma <1.2){
		kernal_size = 5;
		gaussianoffset = 2;
	}
	else if(sigma <1.6){
		kernal_size = 7;
		gaussianoffset = 3;
	}
	else if(sigma <2){
		kernal_size = 9;
		gaussianoffset = 4;
	}
	else if(sigma <2.4){
		kernal_size = 11;
		gaussianoffset = 5;
	}
	else if(sigma <2.8){
		kernal_size = 13;
		gaussianoffset = 6;
	}
	else{
		kernal_size = 15;
		gaussianoffset = 7;
	}


	double** filter = GaussianFilter(kernal_size,sigma);




	for (int i = 1; i < row-1; i++)
	{
		for (int j = 1; j < col-1; j++)
		{
			int sum = 0;
			for (int a = 0; a < kernal_size; a++)
			{
				for (int b = 0; b < kernal_size; b++)
				{
					sum = sum + filter[a][b]*img[i+a-gaussianoffset][j+b-gaussianoffset];
				}
			}
			img_gaussian[i][j] = sum;

		}
	}


	//print image after gaussion

	//Image after sobel mask
	int sobelx[3][3] = {{-1, -2, -1},{0, 0, 0},{1, 2, 1}};
	int sobely[3][3] = {{-1, 0, 1},{-2, 0, 2},{-1, 0, 1}};
	int img_sobel_x[row][col];  	//Image after sobel mask x
	int img_sobel_y[row][col];  	//Image after sobel mask y

	for (int i = 1; i < row-1; i++)
	{
		for (int j = 1; j < col-1; j++)
		{
			int sum = 0;
			for (int a = 0; a < 3; a++)
			{
				for (int b = 0; b < 3; b++)
				{
					sum = sum + sobelx[a][b]*img_gaussian[i+a-1][j+b-1];
				}
			}
			img_sobel_x[i][j] = sum;
		}
	}

	for (int i = 1; i < row-1; i++)
	{
		for (int j = 1; j < col-1; j++)
		{
			int sum = 0;
			for (int a = 0; a < 3; a++)
			{
				for (int b = 0; b < 3; b++)
				{
					sum = sum + sobely[a][b]*img_gaussian[i+a-1][j+b-1];
				}
			}
			img_sobel_y[i][j] = sum;
		}
	}


	//Image after non maximum suppression





	return 0;
}
