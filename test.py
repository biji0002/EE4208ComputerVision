import cv2
import numpy as np
from PIL import Image
import base_faces_lib as bfl
imgNum = 35

eigenFaces = bfl.eigenFacesImport()
eigenVector = bfl.eigenVectorImportnew()
def rgb2gray(rgb):

    r, g, b = rgb[:,:,0], rgb[:,:,1], rgb[:,:,2]
    gray = 0.2989 * r + 0.5870 * g + 0.1140 * b

    return gray


for num in range (0,imgNum):

	path = 'cap/'+str(num)+'.jpg'
	img = cv2.imread(path)
	imgGray = rgb2gray(img)
	faceVec = np.resize(imgGray,(10000,1))
	RecEigenFace = np.dot(eigenVector,faceVec)
	RecEigenFaceTrans = RecEigenFace.transpose()
	#print RecEigenFaceTrans.shape


	minDiff = 1000000000
	for i in range(0,imgNum):
		tempFace = eigenFaces[i]
		#print tempFace.shape

		result = np.absolute(np.array(RecEigenFaceTrans) - np.array(tempFace))
		diff = np.sum(result)
		#print diff
		if diff<minDiff:
			minDiff = diff 
			nearestFace = i
			#print ("recognized as ", nearestFace)
			#print ("minimun difference is ",minDiff)
	print("this picture is",num,"recognized as ", nearestFace)
	#print ("recognized as ", nearestFace)
	#print ("minimun difference is ",minDiff)


