import cv2
import numpy
import math
from PIL import Image
import zncc
import pca
import base_faces_lib as lib


#import the mean adjusted image base matrix
base_matrix_normalised = lib.ini_img_base()

#input the test image
img = Image.open('pan_zexu9.jpg').convert('L')  
img_arr_2d = numpy.asarray(img)              #convert the image to 2d array
img_arr_1d = img_arr_2d.flatten()
test_array = numpy.zeros(len(img_arr_1d))
for x in range(0, len(img_arr_1d)):
	test_array[x] = img_arr_1d[x]

#Perform zncc test
#return the image no in database 
image_no = zncc.zncc_test(test_array, base_matrix_normalised)


#print the match result
print('The imput image matched the image %s.png in the database' %image_no)