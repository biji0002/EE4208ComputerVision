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



	return 0;
}
