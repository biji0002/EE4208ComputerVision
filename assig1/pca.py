import cv2
import numpy as np
from PIL import Image
import base_faces_lib as bfl
from numpy import linalg as la


#initialize the database imgNum*10000
baseMatrix,imgNum,numEigValue = bfl.ini_img_base() 
print imgNum,numEigValue
#get the shape of the matrix imgNum*10000
x,y=baseMatrix.shape
print (x,y)
#find the face_average 1*10000
face_avg = baseMatrix.sum(axis = 0)/x
print face_avg.shape
#face minus face_average imgNum*10000
avgMatrix = np.empty((imgNum,10000),float)
for cnt in range (0,imgNum):

	avgMatrix[cnt]=baseMatrix[cnt] - face_avg

transMatrix=avgMatrix.transpose()
print transMatrix.shape
#calculate covariance matrix
covMatrix=np.cov(transMatrix)
#calculate eigenvalue and eigenvectors
eigenValues, eigenVectors = la.eig(covMatrix)
#obtain eigenvectors sorted based on eigenvalues
idx = eigenValues.argsort()[::-1]   
w = eigenValues[idx]
v = eigenVectors[:,idx]
#save eigenvectors with top eigenvalues
w1 = w[0:numEigValue]
v1 = v[0:10000,0:numEigValue]
v_prime = np.reshape(v1,(10000*numEigValue,1))
np.savetxt("eignevalue",w1)
np.savetxt("eignevector",v_prime)