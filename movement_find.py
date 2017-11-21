
# detects background vs. foreground based on motion

import cv2

import numpy as np

cap = cv2.VideoCapture('ppmaze1.mp4')
fgbg = cv2.createBackgroundSubtractorMOG2()   # only works on mac
#fgbg = cv2.BackgroundSubtractorMOG()   # works on linux

while True:
    ret, frame = cap.read()
    fgmask = fgbg.apply(frame)

    cv2.imshow('original', frame)
    cv2.imshow('frame', fgmask)

    k = cv2.waitKey(30) & 0xff
    if k == 27:
        break

cap.release()
cv2.destroyAllWindows()

