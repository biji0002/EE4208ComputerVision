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
	input = fopen("raw_images/fruit.raw","rb");;

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
	
	double sigma = 0.5;
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
			filter[x+gaussianoffset][y+gaussianoffset] =  exp(-expo)/(sigma*sqrt(2*M_PI));
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
			img_sobel[i][j] = img[i][j];

		}
	}

	//printf("Image has convolute with gaussian\n");

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

    int magnitude[row][col];
    int treshold = 0 ;
    int magnitude_NMS[row][col];

    for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			magnitude[i][j] = sqrt(pow(img_sobel_x[i][j],2)+pow(img_sobel_y[i][j],2));
	}
	
	for (int i = 1; i < row-1; i++)
	{
		for (int j = 1; j < col-1; j++)
		{
			if (magnitude[i][j] != 0)
			{
				float angle = atan(float(img_sobel_y[i][j])/img_sobel_x[i][j])*180/PI;
				if (angle < 0)
					angle = angle + 180;

				if (angle < 22.5 || angle >= 157.5)
				{
					if(magnitude[i][j]>=magnitude[i-1][j] && magnitude[i][j]>=magnitude[i+1][j])
					{
						magnitude_NMS[i][j] = magnitude[i][j];
						magnitude_NMS[i-1][j] = 0;
						magnitude_NMS[i+1][j] = 0;
					}
				}

				if (angle >=22.5 && angle < 67.5)
				{
					if(magnitude[i][j]>=magnitude[i-1][j-1] && magnitude[i][j]>=magnitude[i+1][j+1])
					{
						magnitude_NMS[i][j] = magnitude[i][j];
						magnitude_NMS[i-1][j-1] = 0;
						magnitude_NMS[i+1][j+1] = 0;
					}
				}

				if (angle >= 67.5 && angle < 112.5)
				{
					if(magnitude[i][j]>=magnitude[i][j-1] && magnitude[i][j]>=magnitude[i][j+1])
					{
						magnitude_NMS[i][j] = magnitude[i][j];
						magnitude_NMS[i][j-1] = 0;
						magnitude_NMS[i][j+1] = 0;
					}
				}

				if (angle >= 112.5 && angle < 157.5)
				{
					if(magnitude[i][j]>=magnitude[i-1][j+1] && magnitude[i][j]>=magnitude[i+1][j-1])
					{
						magnitude_NMS[i][j] = magnitude[i][j];
						magnitude_NMS[i-1][j+1] = 0;
						magnitude_NMS[i+1][j-1] = 0;
					}
				}

			}
		}
	}


	//display img
	FILE* pgmimg; 
    pgmimg = fopen("test_img/test.pgm", "wb"); 
    fprintf(pgmimg, "P2\n");  
    fprintf(pgmimg, "%d %d\n", col, row);  
    fprintf(pgmimg, "255\n");  
    int count = 0; 
    for (int i = 0; i < row; i++) { 
        for (int j = 0; j < col; j++) {
        	int temp = magnitude_NMS[i][j];
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
