import cv2
import numpy as np
from PIL import Image
import base_faces_lib as bfl
from numpy import linalg as la
from tempfile import TemporaryFile



imgNum = 35
numEigValue = 300
outfile = TemporaryFile()

#initialize the database imgNum*10000
baseMatrix = bfl.ini_img_base() 
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

covMatrix=np.cov(transMatrix)
eigenValues, eigenVectors = la.eig(covMatrix)

idx = eigenValues.argsort()[::-1]   
w = eigenValues[idx]
v = eigenVectors[:,idx]

w1 = w[0:numEigValue]
v1 = v[0:10000,0:numEigValue]
v_prime = np.reshape(v1,(10000*numEigValue,1))
np.savetxt("eignevalue",w1)
np.savetxt("eignevector",v_prime)

print covMatrix.shape
print transMatrix.shape