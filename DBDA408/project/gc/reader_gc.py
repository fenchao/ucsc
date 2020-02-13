import gc
import numpy as np
from sklearn.model_selection import train_test_split

appleData = np.load('apple.npy')
cowData = np.load('cow.npy')
dogData = np.load('dog.npy')
bedData = np.load('bed.npy')

rawDataArrs = (appleData, cowData, dogData, bedData)

appleData = None
cowData = None
dogData = None
bedData = None
gc.collect()

X_full = np.concatenate(rawDataArrs)
Y_full = np.zeros((len(X_full), len(rawDataArrs)))

currNum = 0
for i, dataArr in enumerate(rawDataArrs):
	for _ in dataArr:
		Y_full[currNum,i] = 1
		currNum += 1

rawDataArrs = None
gc.collect()

X_train, TempX_test, Y_train, TempY_test = train_test_split(X_full, Y_full, test_size=0.40, random_state=42)

X_full = None
Y_full = None
gc.collect()

X_validate, X_test, Y_validate, Y_test = train_test_split(TempX_test, TempY_test, test_size=0.50, random_state=42)

TempX_test = None
TempY_test = None
gc.collect()

Y_train = np.asarray([np.where(r==1)[0][0] for r in Y_train])
Y_validate = np.asarray([np.where(r==1)[0][0] for r in Y_validate])
Y_test = np.asarray([np.where(r==1)[0][0] for r in Y_test])

print Y_test.shape

#np.save('readerData/X_train',X_train)
#np.save('readerData/Y_train',Y_train)
#np.save('readerData/X_validate',X_validate)
#np.save('readerData/Y_validate',Y_validate)
#np.save('readerData/X_test',X_test)
#np.save('readerData/Y_test',Y_test)

