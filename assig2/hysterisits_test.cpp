#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int grow_edges(int row, int col, int input_image_low[], int input_image_high[])
{
	int m = 0, n=0;
	int input_l[row][col];
	int input_h[row][col];

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			input_l[i][j] = input_image_low[m];
			input_h[i][j] = input_image_high[m];
			m++;
		}
	}

	for (int i = 1; i < row-1; i++)
	{
		for (int j = 1; j < col-1; j++)
		{
			if (input_h[i][j] == 1 && input_l[i][j] == 1)
			{
				//convert to 2d for recursive
				int k = 0;
				for (int c = 0; c < row; c++)
				{
					for (int d = 0; d < col; d++)
					{
						temp[k] = input_h[c][d];
						k++;
					}
				}

				grow_edges(row, col, input_image_low, temp);

				k = 0;
				for (int c = 0; c < row; c++)
				{
					for (int d = 0; d < col; d++)
					{
						input_h[c][d] = temp[k];
						k++;
					}
				}

			}

		}



	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			input_image_high[n] = input_h[i][j];
			n++;
		}
	}

	return 0;
}

int hysterisys_tresholding(int row, int col, int input_image_low[], int input_image_high[], int output_img[])
{
	int m = 0, n=0;
	int input_l[row][col];
	int input_h[row][col];
	int output[row][col];
	int temp[row*col];
	int counter[row][col];

	//convert 1d input array to 2d array
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			input_l[i][j] = input_image_low[m];
			input_h[i][j] = input_image_high[m];
			m++;
		}
	}

	for (int i = 1; i < row-1; i++)
	{
		for (int j = 1; j < col-1; j++)
		{
			if (input_h[i][j] == 1 && input_l[i][j] == 1)
			{
				//convert to 2d for recursive
				int k = 0;
				for (int c = 0; c < row; c++)
				{
					for (int d = 0; d < col; d++)
					{
						temp[k] = input_h[c][d];
						k++;
					}
				}

				grow_edges(row, col, input_image_low, temp);

				k = 0;
				for (int c = 0; c < row; c++)
				{
					for (int d = 0; d < col; d++)
					{
						input_h[c][d] = temp[k];
						k++;
					}
				}

			}

		}
	}

	//convert 2d output array to 1d
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


int main(void)
{
	return 0;
}
