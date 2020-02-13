#!/usr/bin/python

import numpy as np
import numpy.linalg as LA

X_train = np.load('readerData/X_train.npy')
X_validate = np.load('readerData/X_validate.npy')
X_test = np.load('readerData/X_test.npy')

#PCA
mu = np.mean(X_train,axis=0)

Z_train = X_train - mu
Z_validate = X_validate - mu
Z_test = X_test - mu

C = np.cov(Z_train, rowvar=False)
[lamb,V] = LA.eigh(C)
lamb = np.flipud(lamb)
V = np.flipud(V.T)

X_train_reduced = np.dot(Z_train, V.T)
X_validate_reduced = np.dot(Z_validate, V.T)
X_test_reduced = np.dot(Z_test, V.T)

np.save('pcaData/X_train_reduced',X_train_reduced)
np.save('pcaData/X_validate_reduced',X_validate_reduced)
np.save('pcaData/X_test_reduced',X_test_reduced)

#np.save('pcaData/mu',mu)
#np.save('pcaData/V',V)

