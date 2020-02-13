#!/usr/bin/python

import numpy as np
from sklearn.decomposition import PCA

X_train = np.load('readerData/X_train.npy')
X_validate = np.load('readerData/X_validate.npy')
X_test = np.load('readerData/X_test.npy')

#PCA
number_of_components = 22
pca = PCA(n_components=number_of_components)
pca.fit(X_train)
X_train_reduced = pca.transform(X_train)
X_validate_reduced = pca.transform(X_validate)
X_test_reduced = pca.transform(X_test)

np.save('pcaData/X_train_reduced',X_train_reduced)
np.save('pcaData/X_validate_reduced',X_validate_reduced)
np.save('pcaData/X_test_reduced',X_test_reduced)
