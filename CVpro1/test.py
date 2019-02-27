import cv2
import numpy
import math
from PIL import Image
import zncc
import pca
import base_faces_lib as lib


img = Image.open('1.png').convert('L')  #import the image base
img_arr_2d = numpy.asarray(img)              #convert the image to 2d array
img_arr_1d = img_arr_2d.flatten()

#input the test image
#array = numpy.asarray[img_arr_1d]
array = img_arr_1d
print(array)
mean = array.mean()
array[9998] = array[9998]- mean
print(array)