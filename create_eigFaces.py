import numpy as np 
import base_faces_lib as bfl
from PIL import Image
imgNum = 35

eigVector = bfl.eigenVectorImportnew()
print eigVector.shape

eigFaces = np.empty((imgNum,200),float)
number = 0
#img = Image.open('cap/0.jpg')
for number in range(0,imgNum):	
	img = Image.open('cap/'+str(number)+'.jpg').convert('L')
	img_array_temp = np.asarray(img.getdata())
	img_array = np.reshape(img_array_temp,(10000,1))
	eigFace = np.dot(eigVector,img_array)
	cnt = 0
	for cnt in range(0,200):
		eigFaces[number,cnt] = eigFace[cnt,0]
	number += 1
	#print img_array.shape
#print eigFaces
print eigFaces.shape
eigFacesOutput = np.resize(eigFaces,(imgNum*200,1))
print eigFacesOutput.shape
np.savetxt('eigFaces',eigFacesOutput)


