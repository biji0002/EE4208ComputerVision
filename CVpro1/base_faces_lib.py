import cv2
import numpy
import math
from PIL import Image


#mean adjustment for a 1d array
def mean_adjustment(array_1d):
	mean = array_1d.mean()
	print(mean)
	for x in range(0, len(array_1d)):
		temp = int(array_1d[x]) - int(mean)
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
	no_of_image = 5
	baseMatrix = numpy.zeros((no_of_image,10000))

	for x in range(0, no_of_image):
		img = Image.open('%s.png' % x).convert('L')  #import the image base
		img_arr_2d = numpy.asarray(img)              #convert the image to 2d array
		img_arr_1d = img_arr_2d.flatten()            #convert the image 2d array to 1d array
		img_arr_1d = mean_adjustment(img_arr_1d)     #perform the mean adjustment for teh 1d array
		print(img_arr_1d)
		baseMatrix[x,:] = img_arr_1d[:]              #save the mean adjusted array in the the base matrix

	return baseMatrix

