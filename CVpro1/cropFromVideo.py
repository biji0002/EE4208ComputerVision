import cv2
import numpy as np

#import cv2 Classifiers
face_cascade = cv2.CascadeClassifier('opencv/data/haarcascades/haarcascade_frontalface_default.xml')
video_capture = cv2.VideoCapture(0)
number = 0

while(number<10):
    # Capture frame-by-frame
    ret, frame = video_capture.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    faces = face_cascade.detectMultiScale(
        gray,
        scaleFactor=1.3,
        minNeighbors=5
    )
    
    # Draw a rectangle around the faces and eyes
    for (x, y, w, h) in faces:

        cv2.rectangle(frame,(x,y),(x+w,y+h),(0,255,0),2)
        #crop the image, resize to 100*100
        roi_gray = gray[y:y+h, x:x+w]
        resized = cv2.resize(roi_gray,(100,100))
        #save image in crop folder,required to create before running code
        cv2.imwrite('CVpro1/cap/crop'+str(number)+'.jpg',resized)
        number = number +1
        print(w,h)
        cv2.waitKey(150)

    # Display the resulting frame
    cv2.imshow('Video', frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything is done, release the capture
video_capture.release()
cv2.destroyAllWindows()