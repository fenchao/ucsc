#!/usr/bin/python

import gc
import numpy as np
import numpy.linalg as LA

# Load training
X_train = np.load('readerData/X_train.npy')
mu = np.mean(X_train,axis=0)

# Z
Z_train = X_train - mu
X_train = None
gc.collect()

# C & V
C = np.cov(Z_train, rowvar=False)
[lamb,V] = LA.eigh(C)
lamb = np.flipud(lamb)
V = np.flipud(V.T)
np.save('pcaData/mu',mu)
np.save('pcaData/V',V)

# R_train
X_train_reduced = np.dot(Z_train, V.T)
np.save('pcaData/X_train_reduced',X_train_reduced)
Z_train = None
X_train_reduced = None
gc.collect()

# R_validate
X_validate = np.load('readerData/X_validate.npy')
Z_validate = X_validate - mu
X_validate_reduced = np.dot(Z_validate, V.T)
np.save('pcaData/X_validate_reduced',X_validate_reduced)
X_validate = None
Z_validate = None
X_validate_reduced = None
gc.collect()

# R_test
X_test = np.load('readerData/X_test.npy')
Z_test = X_test - mu
X_test_reduced = np.dot(Z_test, V.T)
np.save('pcaData/X_test_reduced',X_test_reduced)
