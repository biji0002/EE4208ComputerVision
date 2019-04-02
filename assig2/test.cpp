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
	int x =1 , y = 1;

	float direction = atan(float(y)/x) * 180/3.1415926;

	printf("%lf\n", direction);





	return 0;
}
