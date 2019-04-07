import cv2
import numpy as np

#import cv2 Classifiers
face_cascade = cv2.CascadeClassifier('haarcascades/haarcascade_frontalface_default.xml')
number = 0

for number in range (62,64):

    frame = cv2.imread(str(number)+'.jpg')
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(
        gray,
        scaleFactor=1.3,
        minNeighbors=5
    )
    cnt = 0
    # Draw a rectangle around the faces and eyes
    for (x, y, w, h) in faces:

        cv2.rectangle(frame,(x,y),(x+w,y+h),(0,255,0),2)
        #crop the image, resize to 100*100
        roi_gray = gray[y:y+h, x:x+w]
        resized = cv2.resize(roi_gray,(100,100))
        #save image in crop folder,required to create before running code
        #cv2.imwrite('cap/'+str(number)+'.jpg',resized)
        cv2.imwrite(str(number)+'.jpg',resized)
        cv2.waitKey(0)
    cnt += 1
    # Display the resulting frame
    #cv2.imshow('Video', frame)