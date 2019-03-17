import cv2
import numpy as np
from PIL import Image
import base_faces_lib as lib
from numpy import linalg as la
from tempfile import TemporaryFile
import simplejson


baseMatrix = np.array([[2.5,2.4],[0.5,0.7],[2.2,2.9],[1.9,2.2],[3.1,3.0],[2.3,2.7],[2,1.6],[1,1.1],[1.5,1.6],[1.1,0.9]])
#get the shape of the matrix 40*10000
x,y=baseMatrix.shape
print (x,y)

face_avg = baseMatrix.sum(axis = 0)*1.0/x

avgMatrix = np.empty((10,2))

for cnt in range (0,10):

	avgMatrix[cnt]=baseMatrix[cnt] - face_avg

transMatrix=avgMatrix.transpose()


#[2]={img_arr_1d,img1_arr_1d}
#covar,mean =cv2.calcCovarMatrix(img_arr_1d,img1_arr_1d,flags = 0)
#print img1_arr_1d

covMatrix=np.cov(transMatrix)
w,v = la.eig(covMatrix)

print covMatrix
print w
print v
