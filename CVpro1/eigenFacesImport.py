import numpy as np

def eigenFacesImport():

	eigenFaces = np.empty((40,200),float)
	filepath = 'eigFaces'  
	with open(filepath) as fp:  
		vec = fp.readline()
		row = 1

		while row <40:
			col = 1
	   		while col<200:

				eigenFaces[row-1,col-1] = vec
				vec = fp.readline()
				col += 1
			row +=1

	print eigenFaces.shape
	return eigenFaces


def convertComplex(complex_number):
	
	complex_number = complex_number.replace("+-", "-")
	#t = complex(''.join(complex_number.split()))
	#print complex_number
	t = complex(complex_number)
	result = (t.real*t.real + t.imag*t.imag)**(1.0/2)
	return result

def eigenVectorImport():

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
	print ("eigenVector",eigVector.shape)
	return eigVector 



