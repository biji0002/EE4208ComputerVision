import numpy as np 
import base_faces_lib as bfl
from PIL import Image
imgNum = 35
numEigValue = 300
eigVector = bfl.eigenVectorImportnew()
print eigVector.shape

baseMatrix = bfl.ini_img_base()    #35*10000
baseMatrixT = baseMatrix.transpose()   #10000*35
print baseMatrixT.shape



face_avg = np.empty((1,10000),float)            #1*10000
face_avg = baseMatrix.sum(axis = 0)/imgNum
avgMatrix = np.empty((imgNum,10000),float)      #35*10000
for cnt in range (0,imgNum):

	avgMatrix[cnt]=baseMatrix[cnt] - face_avg

transMatrix=avgMatrix.transpose()               #10000*35
print transMatrix.shape



eigFaces = np.empty((numEigValue,imgNum),complex)       #300*35
number = 0
#img = Image.open('cap/0.jpg')
eigFaces = np.dot(eigVector,transMatrix)
eigFacesT = eigFaces.transpose()          
#print eigFaces
print eigFacesT.shape
eigFacesOutput = np.resize(eigFacesT,(imgNum*numEigValue,1))

print eigFacesOutput.shape
np.savetxt('eigFaces',eigFacesOutput)

print eigFacesT
