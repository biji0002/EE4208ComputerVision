import numpy as np
from numpy import linalg as la

a = np.array([[2,3,4],[1,2,5]])
b = np.resize(a,(2*3,1))
c = np.resize(b,(2,3))
print c

