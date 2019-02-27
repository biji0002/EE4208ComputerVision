import base_faces_lib as lib
import numpy

def zncc_test(input_img):
	#mean adjust and normalised the imput image
	input_img = lib.mean_adjustment(input_img)
	input_img = lib.normalised_vector(input_img)
	print(input_img)

	#import the mean adjusted image base matrix
	base_matrix_normalised = lib.ini_img_base()

	array_similarity = numpy.zeros(len(base_matrix_normalised))
	array_key = numpy.arange(0,len(base_matrix_normalised))

	#normalised the image base matrix
	for x in range(0, len(base_matrix_normalised)):
		base_matrix_normalised[x,:] = lib.normalised_vector(base_matrix_normalised[x,:])
		#print(base_matrix_normalised[x,:])
		#vector inner product
		simmilarity = 0;
		for y in range(0, 10000):
			simmilarity = simmilarity + input_img[y]*base_matrix_normalised[x,y]
		array_similarity[x] = simmilarity


	#selection sort of the simmilarity array
	for i in range(len(array_similarity)):
		swap = i + numpy.argmin(array_similarity[i:])
		(array_similarity[i], array_similarity[swap]) = (array_similarity[swap], array_similarity[i])
		(array_key[i], array_key[swap]) = (array_key[swap], array_key[i])

	print(array_key)
	print(array_similarity)
    
	return array_key[len(array_key)-1]