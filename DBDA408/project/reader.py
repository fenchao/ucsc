#!/usr/bin/python

import numpy as np
from sklearn.model_selection import train_test_split

def loadData(one_hot=False):
	appleData = np.load('rawData/apple.npy')
	cowData = np.load('rawData/cow.npy')
	dogData = np.load('rawData/dog.npy')
	bedData = np.load('rawData/bed.npy')

	rawDataArrs = (appleData, cowData, dogData, bedData)

	X_full = np.concatenate(rawDataArrs)

	Y_full = np.zeros((len(X_full), len(rawDataArrs)))
	currNum = 0
	for i, dataArr in enumerate(rawDataArrs):
		for _ in dataArr:
			Y_full[currNum,i] = 1
			currNum += 1

	X_train, TempX_test, Y_train, TempY_test = train_test_split(X_full, Y_full, test_size=0.40, random_state=42)
	X_validate, X_test, Y_validate, Y_test = train_test_split(TempX_test, TempY_test, test_size=0.50, random_state=42)

	if not one_hot:
		Y_train = np.asarray([np.where(r==1)[0][0] for r in Y_train])
		Y_validate = np.asarray([np.where(r==1)[0][0] for r in Y_validate])
		Y_test = np.asarray([np.where(r==1)[0][0] for r in Y_test])

	return (X_train, Y_train, X_validate, Y_validate, X_test, Y_test)

X_train, Y_train, X_validate, Y_validate, X_test, Y_test = loadData()

np.save('readerData/X_train',X_train)
np.save('readerData/Y_train',Y_train)
np.save('readerData/X_validate',X_validate)
np.save('readerData/Y_validate',Y_validate)
np.save('readerData/X_test',X_test)
np.save('readerData/Y_test',Y_test)

