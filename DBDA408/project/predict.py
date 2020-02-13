#!/usr/bin/python

import sys
import numpy as np
import cv2
import matplotlib.pyplot as plt

def imgProcess(rawImg,size=28):
    #To Right Ratio
    rowRatio = rawImg.shape[0]/size;
    colRatio = rawImg.shape[1]/size;
    fineImg=np.zeros((size,size)).astype('int');
    for row in range(size):
        for col in range(size):
            for i in range(rowRatio):
                for j in range(colRatio):
                    fineImg[row][col] += rawImg[row*rowRatio+i][col*colRatio+j]
    #Change number to max of 255
    maxRatio = np.amax(fineImg+254)/255;
    fineImg /= maxRatio;
    #Change color to opposite
    fineImg = 255-fineImg;
    return fineImg.reshape(size**2)

def vectortoimg(title,v,show=True):
    plt.imshow(v.reshape(28, 28),interpolation='nearest', cmap='gray')
    plt.title(title, fontsize=30)
    plt.axis('off')
    if show:
        plt.show()

# Settings
nComponents = np.array(sys.argv[2]).astype(int)
#rawImg = cv2.imread(sys.argv[3],0)
rawImg = cv2.imread(sys.argv[3],0)
if rawImg is None:
    print "Wrong path!"
    quit()
img = imgProcess(rawImg)

# PCA conversion
mu = np.load('pcaData/mu.npy')
V = np.load('pcaData/V.npy')
Z = img-mu
P = np.dot(Z, V.T[:,0:nComponents])
R = np.dot(P, V[0:nComponents,:])

# Prediction begins
classLabel = ['Apple','Cow','Dog','Bed']

if sys.argv[1] == 'linear':
    W = np.load('classifier/linear.npy')
    Xa = np.insert(P,0,1)
    T = np.dot(Xa,W).argmax(axis=0)
#elif other classifiers

#Display nicely
plt.figure(figsize=(18,10), facecolor='white')
#orig
plt.subplot(1,3,1)
plt.title("Original "+classLabel[T], fontsize=30)
plt.imshow(rawImg, cmap = 'gray', interpolation = 'bicubic')
plt.xticks([]), plt.yticks([])
#img processed
plt.subplot(1,3,2)
vectortoimg("Image Processed "+classLabel[T], img, False)
#recoverd
plt.subplot(1,3,3)
vectortoimg("Reduced "+classLabel[T], R, False)
#main title
plt.suptitle("\nYou Have Drawn "+classLabel[T]+"!", fontsize=50)
plt.show()
