# code to detect ball for ping pong maze

import cv2
import numpy as np
import argparse

vidcap = cv2.VideoCapture(0)
success,image = vidcap.read()
success = True
last = image
while success:
	success,image = vidcap.read()

	boundaries = [
		([0, 30, 190], [120, 175, 255]) #orange for ping pong ball
	]
	output = [] #0 is ball, 1 is maze
	for (lower, upper) in boundaries:

		lower = np.array(lower, dtype = "uint8")
		upper = np.array(upper, dtype = "uint8")

		mask = cv2.inRange(image, lower, upper)
		outputty = cv2.bitwise_and(image, image, mask = mask)
		output.append(outputty)

		output_original = output[0].copy()
		original = output[0].copy()
		gray = cv2.cvtColor(output_original, cv2.COLOR_BGR2GRAY)
		blur = cv2.GaussianBlur(gray, (55, 55), 1, 1 )

		output_blur = blur.copy()
		circlefound = False
		circles = cv2.HoughCircles(blur, cv2.HOUGH_GRADIENT, 2.6, 10000000) #use blur. 2 for mazecolor.png & circles. 1.5 for pictureofmaze. 1 for others
		if circles is not None and len(circles) == 1 and not circlefound:
			print ('Resolution:')
			circles = np.round(circles[0, :]).astype("int")
			circlefound = True
			for (x, y, r) in circles: #draw the circ it found
				cv2.circle(image, (x, y), r, (50, 50, 50), 4)
				# cv2.circle(output_blur, (x, y), r, (255, 255, 255), 4)
				# ssL = 3 #square side length
				# cv2.rectangle(image, (x - ssL, y - ssL), (x + ssL, y + ssL), (255, 0, 200), -1) #open cv is B,G,R
				# cv2.rectangle(output_blur, (x - ssL, y - ssL), (x + ssL, y + ssL), (255, 0, 200), -1)
	cv2.imshow('img', image)
	# cv2.imshow('gray', gray)
	k = cv2.waitKey(30) & 0xff
	if k == 27:
		break

vidcap.release()
cv2.destroyAllWindows()

