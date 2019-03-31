#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <cmath>
#include <iostream>
#include <fstream>
#include <stdint.h>

using namespace std;
uint8_t img_header[5];

#define img_row                     *(uint16_t *)(img_header)
#define img_col                     *(uint16_t *)(img_header + 2)
#define img_pixel_size              *(uint8_t *)(img_header + 4)
/************************************************************************/
	// define gaussian filter function
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
/************************************************************************/

int main(void)
{
	//define gaussian filter size and variance

	int kernal_size = 5;
	double sigma = 1;
	double** filter = GaussianFilter(kernal_size,sigma);
/************************************************************************/
	//load image
	FILE *input;
	uint8_t get_char;
	input = fopen("cana.raw","rb");;

	for (int i = 0; i < 5; i++)
	{
		img_header[i] = fgetc(input);

	}

	int img[img_row][img_col];

	cout<<"img row = "<<img_row<<endl;
	cout<<"img col = "<<img_col<<endl;

	for (int i = 0; i < img_row; i++)
	{
		for (int j = 0; j < img_col; j++)
		{
			img[i][j] = fgetc(input);
//			printf("%02x ", img[i][j]);
		}
//		printf("\n");
	}

	printf("%02x \n", img[img_row-1][img_col-3]);
	printf("%02x \n", img[img_row-1][img_col-2]);
	printf("%02x \n", img[img_row-1][img_col-1]);
/************************************************************************/
	// implementing Gaussion Filter to 
	int imgGaussion[img_row][img_col];
	int kernalOffset = (kernal_size-1)/2;
	for (int i = kernalOffset; i < img_row-kernalOffset; i++)
	{
		for (int j = kernalOffset; j < img_col-kernalOffset; j++)
		{
			int sum = 0;
			for (int cout_x = 0; cout_x<kernal_size; cout_x++)
			{
				for (int cout_y = 0; cout_y<kernal_size; cout_y++)
				{
					sum += img[i-kernalOffset+cout_x][j-kernalOffset+cout_y]*filter[cout_x][cout_y];
				}
			}
			imgGaussion[i][j] = sum;
		}
	}

	for (int i = kernalOffset; i<img_row-kernalOffset;i++)
	{
		for (int j = kernalOffset; j>0;j--)
		{
		imgGaussion[i][j-1] = imgGaussion[i][j];
		imgGaussion[i][img_col-j] = imgGaussion[i][img_col-j-1];			
		}
	}
	for (int j = kernalOffset; j<img_col-kernalOffset; j++)
	{	
		for (int i = kernalOffset; i>0; i--)
		{
		imgGaussion[i-1][j] = imgGaussion[i][j];
		imgGaussion[img_row-i][j] = imgGaussion[img_row-i-1][j];
		}
	}
	for (int cnt = kernalOffset; cnt>0; cnt--)
	{
		imgGaussion[cnt-1][cnt-1] = imgGaussion[kernalOffset][kernalOffset];
		imgGaussion[cnt-1][img_col-cnt] = imgGaussion[kernalOffset][img_col-kernalOffset-1];
		imgGaussion[img_row-cnt][cnt-1] = imgGaussion[img_row-kernalOffset-1][kernalOffset];
		imgGaussion[img_row-cnt][img_col-cnt] = imgGaussion[img_row-kernalOffset-1][img_col-kernalOffset-1];
	}


/****************************************************************************/
//Image after sobel mask
	int row = img_row;
	int col = img_col;
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
					sum = sum + sobelx[a][b]*imgGaussion[i+a-1][j+b-1];
				}
			}
			img_sobel_x[i][j] = sum/8;
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
					sum = sum + sobely[a][b]*imgGaussion[i+a-1][j+b-1];
				}
			}
			img_sobel_y[i][j] = sum/8;
		}
	}
	for (int j = 1; j<col-1; j++){
		img_sobel_x[0][j] = img_sobel_x[1][j];
		img_sobel_x[row-1][j] = img_sobel_x[row-2][j];
		img_sobel_y[0][j] = img_sobel_y[1][j];
		img_sobel_y[row-1][j] = img_sobel_y[row-2][j];
	}
	for (int i = 1; i<col-1; i++){
		img_sobel_x[i][0] = img_sobel_x[i][1];
		img_sobel_x[i][col-1] = img_sobel_x[1][col-2];
		img_sobel_y[i][0] = img_sobel_y[i][1];
		img_sobel_y[i][col-1] = img_sobel_y[1][col-2];
	}
	img_sobel_x[0][0] = img_sobel_x[1][1];
	img_sobel_x[0][col-1] = img_sobel_x[1][col-2];
	img_sobel_x[row-1][0] = img_sobel_x[row-2][1];
	img_sobel_x[row-1][row-1] = img_sobel_x[row-2][col-2];
	img_sobel_y[0][0] = img_sobel_y[1][1];
	img_sobel_y[0][col-1] = img_sobel_y[1][col-2];
	img_sobel_y[row-1][0] = img_sobel_y[row-2][1];
	img_sobel_y[row-1][row-1] = img_sobel_y[row-2][col-2];





/****************************************************************************/
//save image

	FILE* pgmimg; 
    pgmimg = fopen("output.pgm", "wb"); 
    fprintf(pgmimg, "P2\n");  
    fprintf(pgmimg, "%d %d\n", row, col);  
    fprintf(pgmimg, "255\n");  
    int count = 0; 
    for (int i = 0; i < row; i++) { 
        for (int j = 0; j < col; j++) { 
            fprintf(pgmimg, "%d ", imgGaussion[i][j]); 
        } 
        fprintf(pgmimg, "\n"); 
    } 
    fclose(pgmimg);



	return 0;
}
