import numpy as np




def convertComplex(complex_number):
	
	complex_number = complex_number.replace("+-", "-")
	#t = complex(''.join(complex_number.split()))
	#print complex_number
	t = complex(complex_number)
	result = (t.real*t.real + t.imag*t.imag)**(1.0/2)
	return result


eigValue = np.empty((200,1),float)
filepath1 = 'eignevalue'  
with open(filepath1) as fp:  
   val = fp.readline()
   cnt = 1
   while cnt<200:
       cmpl = convertComplex(val)
       fl = (cmpl.real*cmpl.real+cmpl.imag*cmpl.imag)**(1.0/2)
       print fl
       eigValue[cnt-1,0] = fl
       val = fp.readline()
       cnt += 1
print eigValue.shape

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

