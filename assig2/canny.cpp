#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <stdint.h>


uint8_t img_header[5];

#define img_row                     *(uint16_t *)(img_header)
#define img_col                     *(uint16_t *)(img_header + 2)
#define img_pixel_size              *(uint8_t *)(img_header + 4)

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
	int img[img_row*img_col]; 			//Original image
	int img_gaussian[img_row*img_col]; //Image after gaussian mask
	int img_sobel_low[img_row*img_col];  	//Image after sobel mask using lower treshold
	int img_nms_low[img_row*img_col];  	//Image after non maximum supression using lower treshold
	int img_sobel_high[img_row*img_col];  	//Image after sobel mask using higher treshold
	int img_nms_high[img_row*img_col];  	//Image after non maximum supression using higher treshild
	int img_ht[img_row*img_col]; 		// Image after hysterisis tresholding 


	for (int i = 0; i < img_row*img_col; i++)
	{
		img[i] = fgetc(input);     //read the image to an array
	}

	//Image after gaussian mask




	//Image after sobel mask





	//Image after non maximum suppression





	//Image after hysterisis tresholding





	return 0;
}
