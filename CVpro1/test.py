import cv2
import numpy as np
import eigenFacesImport as efi
from PIL import Image
import base_faces_lib as lib


path = "cap/3.jpg"
img = cv2.imread(path)

def rgb2gray(rgb):

    r, g, b = rgb[:,:,0], rgb[:,:,1], rgb[:,:,2]
    gray = 0.2989 * r + 0.5870 * g + 0.1140 * b

    return gray

imgGray = rgb2gray(img)

baseMatrix = lib.ini_img_base() 
#get the shape of the matrix 40*10000
x,y=baseMatrix.shape
#find the face_average 1*10000
face_avg = baseMatrix.sum(axis = 0)/x


eigenFaces = efi.eigenFacesImport()
eigenVector = efi.eigenVectorImport()


faceVec = np.resize(imgGray,(10000,1))
RecEigenFace = np.dot(eigenVector,faceVec)
RecEigenFaceTrans = RecEigenFace.transpose()
print RecEigenFaceTrans.shape


minDiff = 1000000000
for i in range(0,40):
	tempFace = eigenFaces[i]
	print tempFace.shape

	result = np.absolute(np.array(RecEigenFaceTrans) - np.array(tempFace))
	diff = np.sum(result)
	#print diff
	if diff<minDiff:
		minDiff = diff 
		nearestFace = i
		print ("recognized as ", nearestFace)
		print ("minimun difference is ",minDiff)

print ("recognized as ", nearestFace)
print ("minimun difference is ",minDiff)


