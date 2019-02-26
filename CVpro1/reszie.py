import numpy as np
import cv2

face_cascade = cv2.CascadeClassifier('opencv/data/haarcascades/haarcascade_frontalface_default.xml')


img = cv2.imread('frame_screenshot_25.02.2019.png')
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

faces = face_cascade.detectMultiScale(
        gray,
        scaleFactor=1.3,
        minNeighbors=5
    )

	
crop_img = img[y:y+h, x:x+w].copy()
cv2.imshow('img2',crop_img)

cv2.waitKey(0)
cv2.destroyAllWindows()