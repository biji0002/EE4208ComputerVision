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
///////side
	for(int i = 0;i<row;i++)
	{
		img_gaussian[i][0] = img_gaussian[i][1];
		img_gaussian[i][col-1] = img_gaussian[i][col-2];
	}
	for(int j = 0;j<col;j++)
	{
		img_gaussian[0][j] = img_gaussian[1][j];
		img_gaussian[row-1][j] = img_gaussian[row-2][j];
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
					sum = sum + sobely[a][b]*img_gaussian[i+a-1][j+b-1];
				}
			}
			img_sobel_y[i][j] = sum/8;
		}
	}


	//Image after non maximum suppression

 cout<<"image_sobel_x[i][j] is "<<img_sobel_x[7][4]<<endl;
    float magnitude[row][col];
    float norm[row][col];
    int direction[row][col];
    float tolerance = 0;
    float treshold ;

    float total = 0;
     
    //////////////NMS Way_1
    for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{   


			magnitude[i][j] = sqrt(pow(img_sobel_x[i][j],2)+pow(img_sobel_y[i][j],2));
			norm[i][j] = (img_sobel_x[i][j]*img_sobel_y[i][j])/magnitude[i][j];
			
			
			if(norm[i][j] > 0)
			{	
				direction[i][j] = 45;
			}
			else
			{
				direction[i][j] = 135;
			}

			if((-tolerance)<=img_sobel_x[i][j]<=tolerance)
			{
				direction[i][j] = 90;
			}
			else
			{

			}

			if((-tolerance)<=img_sobel_y[i][j]<=tolerance)
			{
				direction[i][j] = 0;
			}
			else
			{

			}

			

		}
	}
///////////NMS_Way2
	/*for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{   

			
			magnitude[i][j] = sqrt(pow(img_sobel_x[i][j],2)+pow(img_sobel_y[i][j],2));
            if(img_sobel_x[i][j]!=0)
            {
			norm[i][j] = atan(img_sobel_y[i][j]/img_sobel_x[i][j])*180/PI;
			float difference1 = fabs(norm[i][j]-0);
			float difference2 = fabs(norm[i][j]-45);
			float difference3 = fabs(norm[i][j]-90);
			float difference4 = fabs(norm[i][j]-135);

			float min = difference1;
			norm[i][j] = 0;
			  if(difference2<min)
			  {
                   norm[i][j] = 45;
			  }
			  if(difference3<min)
			  {
                   norm[i][j] = 90;
			  }
			  if(difference4<min)
			  {
                   norm[i][j] = 135;
			  }
		    }
		    else
		    {
		    	norm[i][j] = 90;
		    }
			
			

			

		}
	}*/
	
	float magnitude_NMS[row][col];
////apply MNS
	for (int i = 1; i < row-1; i++)
	{
		for (int j = 1; j < col-1; j++)
		{
			switch(direction[i][j])
			{
				case 0:
				if(magnitude[i][j]>=magnitude[i-1][j] && magnitude[i][j]>=magnitude[i+1][j])
				{
					magnitude_NMS[i][j] = magnitude[i][j];
					magnitude_NMS[i-1][j] = 0;
					magnitude_NMS[i+1][j] = 0;
				}
				else
				{
					magnitude_NMS[i][j] = 0;
				}
				break;
				case 45:
				if(magnitude[i][j]>=magnitude[i-1][j-1] && magnitude[i][j]>=magnitude[i+1][j+1])
				{
					magnitude_NMS[i][j] = magnitude[i][j];
					magnitude_NMS[i-1][j-1] = 0;
					magnitude_NMS[i+1][j+1] = 0;
				}
				else
				{
					magnitude_NMS[i][j] = 0;
				}
				break;
				case 90:
				if(magnitude[i][j]>=magnitude[i][j-1] && magnitude[i][j]>=magnitude[i][j+1])
				{
					magnitude_NMS[i][j] = magnitude[i][j];
					magnitude_NMS[i][j-1] = 0;
					magnitude_NMS[i][j+1] = 0;
				}
				else
				{
					magnitude_NMS[i][j] = 0;
				}
				break;
				case 135:
				if(magnitude[i][j]>=magnitude[i-1][j+1] && magnitude[i][j]>=magnitude[i+1][j-1])
				{
					magnitude_NMS[i][j] = magnitude[i][j];
					magnitude_NMS[i-1][j+1] = 0;
					magnitude_NMS[i+1][j-1] = 0;
				}
				else
				{
					magnitude_NMS[i][j] = 0;
				}
				break;
			}

		}
	}
//////sides
	for(int i = 0;i<row;i++)
	{
		magnitude_NMS[i][0] = 0;
		magnitude_NMS[i][col-1] = 0;
	}
	for(int j = 0;j<col;j++)
	{
		magnitude_NMS[0][j] = 0;
		magnitude_NMS[row-1][j] = 0;
	}
	//////////compute treshold
    int total_num = 0;
    for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if(-1<magnitude_NMS[i][j]&&magnitude_NMS[i][j]<256)
			{
				total = total + magnitude_NMS[i][j];
				total_num++;
			}
		}
	}
	treshold = (total/total_num)*4;
	cout<<"treshold is "<<treshold<<endl;
	///float imgmax = 0;
	/////////apply treshold,larger to 255, smaller to 0
    for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if(magnitude_NMS[i][j]>treshold)
			{
				magnitude_NMS[i][j] = 255;
			}
			else
			{
				magnitude_NMS[i][j] = 0;
			}

		}
	}
	/////cout<<"max is "<<imgmax<<endl;
    
    cout<<"debug"<<endl;

	//display img
	FILE* pgmimg; 
    pgmimg = fopen("output_fruit_NMS.pgm", "wb"); 
    fprintf(pgmimg, "P2\n");  
    fprintf(pgmimg, "%d %d\n", col, row);  
    fprintf(pgmimg, "255\n");  
    int count = 0; 
    for (int i = 0; i < row; i++) { 
        for (int j = 0; j < col; j++) { 
            int temp = magnitude_NMS[i][j]; 
            
            // Writing the gray values in the 2D array to the file 
            fprintf(pgmimg, "%d ", temp); 
        } 
        fprintf(pgmimg, "\n"); 
    } 
    fclose(pgmimg);

	return 0;
}
