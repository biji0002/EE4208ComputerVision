import cv2
import numpy as np
from PIL import Image
import base_faces_lib as bfl
imgNum = 35

numEigValue = 300

baseMatrix = bfl.ini_img_base()    #35*10000
baseMatrixT = baseMatrix.transpose()   #10000*35
print baseMatrixT.shape



face_avg = np.empty((1,10000),float)            #1*10000
face_avg = baseMatrix.sum(axis = 0)/imgNum
avgMatrix = np.empty((imgNum,10000),float)      #35*10000
for cnt in range (0,imgNum):

	avgMatrix[cnt]=baseMatrix[cnt] - face_avg

transMatrix=avgMatrix.transpose()               #10000*35
def convertComplex(complex_number):
	
	complex_number = complex_number.replace("+-", "-")
	#t = complex(''.join(complex_number.split()))
	#print complex_number
	t = complex(complex_number)
	result = (t.real*t.real + t.imag*t.imag)**(1.0/2)
	return result

eigenVector = bfl.eigenVectorImportnew()   #300*10000
eigFaces = np.empty((numEigValue,imgNum),complex)       #300*35
number = 0
#img = Image.open('cap/0.jpg')
eigFaces = np.dot(eigenVector,transMatrix)
eigFacesT = eigFaces.transpose() 



no_of_image = 35

baseMatrix = bfl.ini_img_base()   #35*10000


face_avg = np.empty((1,10000),float)            #1*10000
face_avg = baseMatrix.sum(axis = 0)/imgNum
avgMatrix = np.empty((imgNum,10000),float)      #35*10000
for cnt in range (0,imgNum):

	avgMatrix[cnt]=baseMatrix[cnt] - face_avg

transMatrix=avgMatrix.transpose()               #10000*35
print transMatrix.shape

RecEigenFace = np.empty((300,imgNum),complex)       #300*35

RecEigenFace = np.dot(eigenVector,transMatrix)   #300*35
RecEigenFaceTrans = RecEigenFace.transpose()   #35*300

for x in range(0,imgNum):
	minDiff = 1000000000
	for i in range(0,imgNum):
		#tempFace = eigenFaces[i]  #1*300
		#print tempFace.shape
		#result = np.empty((1,300),)
		#tempFace = eigenFaces[i]
		#tempFaceT = tempFace.transpose()
		#print tempFace.shape
		#print RecEigenFaceTrans.shape
		sum1 = 0
		for j in range(0,300):
			sum1 = sum1 + np.square(RecEigenFaceTrans[x,j])

		sum1 = np.sqrt(sum1)

		sum2 = 0
		for k in range(0,300):
			sum2 = sum2 + np.square(eigFacesT[i,k])
		
		sum2 = np.sqrt(sum2)
		diff = np.absolute(sum2 - sum1)
		 

		#result = RecEigenFaceTrans[x,:] - eigenFaces[i,:]
		#result1 = np.square(result)
		
		#result2 = np.sum(result1)
		#diff = np.sqrt(result2)
		#diff = np.sum(result)
		#print diff
		if diff<minDiff:
			minDiff = diff 
			nearestFace = i
			
			#print ("recognized as ", nearestFace)
			#print ("minimun difference is ",minDiff)
	print("this picture is",x,"recognized as ",nearestFace,"minimun difference is ",minDiff)
#print ("recognized as ", nearestFace)
#print ("minimun difference is ",minDiff)

#new = RecEigenFaceTrans[1,1] - eigenFaces[1,1]

print eigenFaces
