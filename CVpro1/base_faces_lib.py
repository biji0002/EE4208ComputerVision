import cv2
import numpy
import math
from PIL import Image


#mean adjustment for a 1d array
def mean_adjustment(array_1d):
	mean = array_1d.mean()
	for x in range(0, len(array_1d)):
		temp = array_1d[x] - mean
		array_1d[x] = temp
	return array_1d


#normalise the vector in a 1d array and return the array
def normalised_vector(array_1d):
	total = 0
	for x in range(0, len(array_1d)):
		total = total + array_1d[x]*array_1d[x]

	total = math.sqrt(total)
	for x in range(0, len(array_1d)):
		array_1d[x] = array_1d[x] / total
	return array_1d


#Ini func that create and return the mean adjusted database matrix
def ini_img_base():
	#Create the base 100*10000 matrix
	no_of_image = 40
	baseMatrix = numpy.zeros((no_of_image,10000))
	array_int = numpy.zeros(10000)

	for x in range(0, no_of_image):
		img = Image.open('cap/%s.jpg' % x).convert('L')  #import the image base
		img_arr_2d = numpy.asarray(img)              #convert the image to 2d array
		img_arr_1d = img_arr_2d.flatten()			 #convert the image 2d array to 1d array
		for y in range(0, len(img_arr_1d)):
			array_int[y] =  img_arr_1d[y]          
		#array_int = mean_adjustment(array_int)     #perform the mean adjustment for teh 1d array
		baseMatrix[x,:] = array_int[:]              #save the mean adjusted array in the the base matrix

	return baseMatrix
