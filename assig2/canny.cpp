#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <stdint.h>


uint8_t img_header[5];

#define row                     *(uint16_t *)(img_header)
#define col                     *(uint16_t *)(img_header + 2)
#define pixel_size              *(uint8_t *)(img_header + 4)

int main(void)
{
	using namespace std;

	//Input the raw image, read the raw image to a matrix
	FILE *input;
	uint8_t get_char;
	input = fopen("raw_images/cana.raw","rb");;

	for (int i = 0; i < 5; i++)
	{
		img_header[i] = fgetc(input);

	}

	//define all image arrays
	int img[row][col]; 			//Original image
	int img_gaussian[row][col]; //Image after gaussian mask
	int img_sobel[row][col];  	//Image after sobel mask using lower treshold
	int img_nms[row][col];  	//Image after non maximum supression using lower treshold


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




	//Image after sobel mask





	//Image after non maximum suppression





	return 0;
}
