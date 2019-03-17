import cv2
import numpy as np
from PIL import Image
import base_faces_lib as bfl
from numpy import linalg as la

imgNum = 10
numEigValue = 2
#initialize the database imgNum*10000
baseMatrixT = np.array([[2.5,0.5,2.2,1.9,3.1,2.3,2,1,1.5,1.1],[2.4,0.7,2.9,2.2,3.0,2.7,1.6,1.1,1.6,0.9]])
baseMatrix = baseMatrixT.transpose()
x,y=baseMatrix.shape
print (x,y)
#find the face_average 1*10000
face_avg = baseMatrix.sum(axis = 0)*1.0/x
print face_avg
#face minus face_average imgNum*10000
avgMatrix = np.empty((imgNum,2),float)

for cnt in range (0,imgNum):

	avgMatrix[cnt]=baseMatrix[cnt] - face_avg

transMatrix=avgMatrix.transpose()
print avgMatrix
covMatrix=np.cov(transMatrix)
w,v = la.eig(covMatrix)

w1 = w[0:numEigValue]
v1 = v[0:2,0:numEigValue]
v_prime = np.reshape(v1,(2*numEigValue,1))
np.savetxt("eignevalue",w1)
np.savetxt("eignevector",v_prime)

print covMatrix
print transMatrix.shape
print w1
print v1