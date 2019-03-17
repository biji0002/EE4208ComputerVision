import cv2
import numpy as np
from PIL import Image
import base_faces_lib as lib
from numpy import linalg as la
from tempfile import TemporaryFile
import simplejson

outfile = TemporaryFile()

#img = Image.open('cap/bi_jianxin/crop0.jpg').convert('L')
#img_arr_2d = np.asarray(img)              #convert the image to 2d array
#img_arr_1d = img_arr_2d.flatten()

#img1 = Image.open('cap/bi_jianxin/crop1.jpg').convert('L')
#img1_arr_2d = np.asarray(img1)              #convert the image to 2d array
#img1_arr_1d = img1_arr_2d.flatten()

#avg = (img_arr_1d+img1_arr_1d)/2


#initialize the database 40*10000
baseMatrix = lib.ini_img_base() 
#get the shape of the matrix 40*10000
x,y=baseMatrix.shape
print (x,y)
#find the face_average 1*10000
face_avg = baseMatrix.sum(axis = 0)/x
#face minus face_average 40*10000
avgMatrix = np.empty((40,10000),int)
for cnt in range (0,40):

	avgMatrix[cnt]=baseMatrix[cnt] - face_avg

transMatrix=avgMatrix.transpose()

#[2]={img_arr_1d,img1_arr_1d}
#covar,mean =cv2.calcCovarMatrix(img_arr_1d,img1_arr_1d,flags = 0)
#print img1_arr_1d

covMatrix=np.cov(transMatrix)
w,v = la.eig(covMatrix)



w1 = w[0:200]
v1 = v[0:200,0:10000]
v_prime = np.reshape(v1,(400*10000,1))
np.savetxt("eignevalue",w1)
np.savetxt("eignevector",v_prime)

#f1 = open("eignevalue","r")
#w = f1.read().splitlines()




print covMatrix.shape

print transMatrix.shape