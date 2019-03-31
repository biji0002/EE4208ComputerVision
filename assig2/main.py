import numpy as np
import struct


imgfile = "raw_images/cana.raw"
f = open(imgfile,"rb")

print(struct.unpack('i', f.read(2)))