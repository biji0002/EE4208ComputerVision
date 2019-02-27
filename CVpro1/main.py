import cv2
import numpy
import math
from PIL import Image
import zncc
import pca


#input the test image
img = Image.open('1.png').convert('L')  #import the image base
img_arr_2d = numpy.asarray(img)              #convert the image to 2d array
img_arr_1d = img_arr_2d.flatten()

image_no = zncc.zncc_test(img_arr_1d)

print(image_no)