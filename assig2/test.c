#include <stdio.h>
main() {
   int i, j;
   int w = 13, h = 13;
   // This 2D array will be converted into an image The size is 13 x 13
   int image[13][13] = {
      { 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15 },
      { 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31},
      { 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47},
      { 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63},
      { 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79},
      { 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95 },
      { 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111},
      { 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127},
      { 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143},
      { 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159},
      { 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175},
      { 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191},
      { 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207}
   };
   FILE* pgmimg;
   pgmimg = fopen("my_pgmimg.pgm", "wb"); //write the file in binary mode
   fprintf(pgmimg, "P2\n"); // Writing Magic Number to the File
   fprintf(pgmimg, "%d %d\n", w, h); // Writing Width and Height into the
   fprintf(pgmimg, "255\n"); // Writing the maximum gray value
   int count = 0;
   for (i = 0; i < h; i++) {
      for (j = 0; j < w; j++) {
         fprintf(pgmimg, "%d ", image[i][j]); //Copy gray value from

      }
      fprintf(pgmimg, "\n");
   }
   fclose(pgmimg);
}