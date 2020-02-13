#!/usr/bin/python

import sys
import numpy as np
import numpy.linalg as LA
from sklearn import linear_model

#Settings
nComponents = np.array(sys.argv[1]).astype(int) # nComponents range from 2-784, e.g. 60
classifier = "pinv"

X_train_reduced = np.load('pcaData/X_train_reduced.npy')
X_validate_reduced = np.load('pcaData/X_validate_reduced.npy')
X_test_reduced = np.load('pcaData/X_test_reduced.npy')

Y_train = np.load('readerData/Y_train.npy')
Y_validate = np.load('readerData/Y_validate.npy')
Y_test = np.load('readerData/Y_test.npy')

P_train = X_train_reduced[:,0:nComponents]
P_validate = X_validate_reduced[:,0:nComponents]
P_test = X_test_reduced[:,0:nComponents]

def accuracy(Y,T):
    acc = 0.
    for i,j in zip(Y,T):
        if i == j:
            acc+=1
    return acc/len(Y)

def confusion_matrix(Y,T):
    cfm = np.zeros((4,4))
    for i,j in zip(Y,T):
        cfm[i][j]+=1
    return cfm

#Build classifier
if classifier is "pinv":
    #Build Pinv Classifier
    Xa = np.insert(P_train,0,1,axis=1)
    Xp = LA.pinv(Xa)
    T = -np.ones((len(Y_train), np.amax(Y_train)+1))
    for i in range(len(Y_train)):
        T[i][Y_train[i]] = 1
    W = Xp.dot(T)
    # Classify
    Xa_validate = np.insert(P_validate,0,1,axis=1)
    Xa_test = np.insert(P_test,0,1,axis=1)
    T_train = np.dot(Xa,W).argmax(axis=1)
    T_validate = np.dot(Xa_validate,W).argmax(axis=1)
    T_test = np.dot(Xa_test,W).argmax(axis=1)
    # Analysis
    print "Train Accuracy: ", accuracy(Y_train, T_train)
    print "Train Confusion Matrix\n", confusion_matrix(Y_train, T_train)
    print "Validate Accuracy: ", accuracy(Y_validate, T_validate)
    print "Validate Confusion Matrix\n", confusion_matrix(Y_validate, T_validate)
    print "Test Accuracy: ", accuracy(Y_test, T_test)
    print "Test Confusion Matrix\n", confusion_matrix(Y_test, T_test)
else:
    print "sklearn linear classifier to be used here"
    #clf = linear_model.SGDClassifier(max_iter=1000, tol=1e-3)
    #clf.fit(P_train, Y_train)

np.save('classifier/linear', W)
