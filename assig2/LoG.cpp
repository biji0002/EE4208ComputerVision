#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <cmath>


using namespace std;

uint8_t img_header[5];

#define col                     *(uint16_t *)(img_header)
#define row                     *(uint16_t *)(img_header + 2)
#define pixel_size              *(uint8_t *)(img_header + 4)
#define PI 3.14159265


int main(void)
{
	//Input the raw image, read the raw image to a matrix
	FILE *input;
	uint8_t get_char;
	input = fopen("cana.raw","rb");;

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

	printf("no of rows: %d  , no of cols : %d \n", row, col);


	//Image after gaussian mask
	
	double sigma = 0.8;
	int kernal_size;

	if(sigma <0.8){
		kernal_size = 3;
	}
	else if(sigma <1.2){
		kernal_size = 5;
	}
	else if(sigma <1.6){
		kernal_size = 7;
	}
	else if(sigma <2){
		kernal_size = 9;
	}
	else if(sigma <2.4){
		kernal_size = 11;
	}
	else if(sigma <2.8){
		kernal_size = 13;
	}
	else{
		kernal_size = 15;
	}

	int gaussianoffset = (kernal_size-1)/2;

	float filter[kernal_size][kernal_size];
	int gaussian_mask[kernal_size][kernal_size];
	
	for (int x = -gaussianoffset; x <= gaussianoffset; x++){
		for (int y = -gaussianoffset; y <= gaussianoffset; y++){
			float expo =(x*x+y*y)/(2*sigma*sigma);
			filter[x+gaussianoffset][y+gaussianoffset] =  -(1-expo)/(pow(sigma,2)*M_PI)*exp(-expo);
		}
	}

	float temp = filter[0][0];
	int scale = 0;

	for (int i = 0; i < kernal_size; i++)
	{
		for (int j = 0; j < kernal_size; j++)
		{
			gaussian_mask[i][j] = round(filter[i][j] / temp);
			scale = scale + gaussian_mask[i][j];
			printf("%d   ", gaussian_mask[i][j]);
		}
		printf(" \n");
	}

	//printf("%d   ", gaussian_mask[0][0]);


	printf("The scale is %d \n", scale);



	for (int i = gaussianoffset; i < row-gaussianoffset; i++)
	{
		for (int j = gaussianoffset; j < col-gaussianoffset; j++)
		{
			int sum = 0;
			for (int a = 0; a < kernal_size; a++)
			{
				for (int b = 0; b < kernal_size; b++)
				{
					sum = sum + gaussian_mask[a][b] * img[i-gaussianoffset+a][j-gaussianoffset+b];

				}
			}

			img_gaussian[i][j] = round(sum/scale);

		}
	}




	//display img
	FILE* pgmimg; 
    pgmimg = fopen("fruit_nms_LoG_neg.pgm", "wb"); 
    fprintf(pgmimg, "P2\n");  
    fprintf(pgmimg, "%d %d\n", col, row);  
    fprintf(pgmimg, "255\n");  
    int count = 0; 
    for (int i = 0; i < row; i++) { 
        for (int j = 0; j < col; j++) {
        	int temp = img_gaussian[i][j];
        	if (temp>255)
        		temp = 255;
        	if (temp<0)
        		temp = 0;
            fprintf(pgmimg, "%d ", temp); 
        } 
        fprintf(pgmimg, "\n"); 
    } 
    fclose(pgmimg);

	return 0;
}