#!/usr/bin/python

import numpy as np
import numpy.linalg as LA
import matplotlib.pyplot as plt

def plot_confusion_matrix(cm, classes,
                          normalize=False,
                          title='Confusion matrix',
                          cmap=plt.cm.Blues):
    """
    This function prints and plots the confusion matrix.
    Normalization can be applied by setting `normalize=True`.
    """
    if normalize:
        cm = cm.astype('float') / cm.sum(axis=1)[:, np.newaxis]
        print("Normalized confusion matrix")
    else:
        print('Confusion matrix, without normalization')

    print(cm)

    plt.imshow(cm, interpolation='nearest', cmap=cmap)
    plt.title(title)
    plt.colorbar()
    tick_marks = np.arange(len(classes))
    plt.xticks(tick_marks, classes, rotation=45)
    plt.yticks(tick_marks, classes)

    fmt = '.2f' if normalize else 'd'
    thresh = cm.max() / 2.
    for i in range(4):
        for j in range(4):
            plt.text(j, i, format(cm[i, j], fmt),
                     horizontalalignment="center",
                     color="white" if cm[i, j] > thresh else "black")

    plt.ylabel('True label')
    plt.xlabel('Predicted label')

class_names = ['apple', 'cow', 'dog', 'bed']
cm_test = [[27702, 150, 555, 444],
           [249, 15627, 7130, 1646],
           [1284, 6910, 17901, 4245],
           [822, 1532, 1807, 18762]]
cm = np.array(cm_test)

#plot_confusion_matrix(cm, class_names, title='Confusion Matrix - Linear Classifier')
#plt.show()

def accuracy(cm):
    size = cm.sum()
    acc = np.zeros(4)
    for i in range(4):
        for j in range(4):
            for k in range(4):
                if (i==k and j==k) or (i!=k and j!=k):
                    acc[k]+=cm[i][j]
    acc/=size
    return acc
print accuracy(cm)
