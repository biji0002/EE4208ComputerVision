import numpy as np 
from PIL import Image
import cv2

def convertComplex(complex_number):
	
	complex_number = complex_number.replace("+-", "-")
	#t = complex(''.join(complex_number.split()))
	#print complex_number
	t = complex(complex_number)
	result = (t.real*t.real + t.imag*t.imag)**(1.0/2)
	return result


eigVector = np.empty((200,10000),float)
filepath2 = 'eignevector'  
with open(filepath2) as fp:  
	vec = fp.readline()
	row = 1

	while row <200:
		col = 1
   		while col<10000:
			#print("Line {}: {}".format(cnt, line.strip()))
			#cmpl = complex(line)
			#print line
			cmpl = convertComplex(vec)
			#fl = (cmpl.real*cmpl.real+cmpl.imag*cmpl.imag)**(1.0/2)
			#print fl
			eigVector[row-1,col-1] = cmpl
			vec = fp.readline()
			col += 1
		row +=1
print eigVector.shape


eigFaces = np.empty((40,200),float)
number = 0
#img = Image.open('cap/0.jpg')
for number in range(0,40):	
	img = Image.open('cap/'+str(number)+'.jpg').convert('L')
	img_array_temp = np.asarray(img.getdata())
	img_array = np.reshape(img_array_temp,(10000,1))
	eigFace = np.dot(eigVector,img_array)
	cnt = 0
	for cnt in range(0,200):
		eigFaces[number,cnt] = eigFace[cnt,0]
	number += 1
	#print img_array.shape
print eigFaces
print eigFaces.shape
eigFacesOutput = np.resize(eigFaces,(40*200,1))
print eigFacesOutput.shape
np.savetxt('eigFaces',eigFacesOutput)


