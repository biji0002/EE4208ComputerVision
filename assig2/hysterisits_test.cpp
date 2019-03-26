#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
	return 0;
}

int hysterisys_tresholding(int row, int col, int input_image_low[], int input_image_high[], int output_img[])
{
	int m = 0, n=0;
	int input_l[row][col];
	int input_h[row][col];
	int output[row][col];

	int counter[row][col] = {{0}};

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			input_l[i][j] = input_image_low[m];
			input_h[i][j] = input_image_high[m];
			m++;
		}
	}



	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			output_img[n] = output[i][j];
			n++;
		}
	}

	return 0;
}