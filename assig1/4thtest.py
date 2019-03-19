import cv2
import numpy as np
from PIL import Image
import base_faces_lib as bfl
imgNum = 35
numEigValue = 300

def calcEigFaces():
	baseMatrix = bfl.ini_img_base()    #35*10000
	baseMatrixT = baseMatrix.transpose()   #10000*35
	print baseMatrixT.shape

	face_avg = np.empty((1,10000),float)            #1*10000
	face_avg = baseMatrix.sum(axis = 0)/imgNum
	avgMatrix = np.empty((imgNum,10000),float)      #35*10000
	for cnt in range (0,imgNum):

		avgMatrix[cnt]=baseMatrix[cnt] - face_avg

	transMatrix=avgMatrix.transpose()               #10000*35

	eigenVector = bfl.eigenVectorImportnew()   #300*10000
	eigFaces = np.empty((numEigValue,imgNum),complex)       #300*35
	number = 0
	#img = Image.open('cap/0.jpg')
	eigFaces = np.dot(eigenVector,transMatrix)
	eigFacesT = eigFaces.transpose() 
	return eigFacesT