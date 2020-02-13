#!/usr/bin/python
import numpy as np
import matplotlib.pyplot as plt
from pandas import DataFrame

def readExcelSheet1(excelfile):
    from pandas import read_excel
    return (read_excel(excelfile)).values
def readExcelRange(excelfile,sheetname="Sheet1",startrow=1,endrow=1,startcol=1,endcol=1):
    from pandas import read_excel
    values=(read_excel(excelfile, sheetname,header=None)).values;
    return values[startrow-1:endrow,startcol-1:endcol]
def readExcel(excelfile,**args):
    if args:
        data=readExcelRange(excelfile,**args)
    else:
        data=readExcelSheet1(excelfile)
    if data.shape==(1,1):
        return data[0,0]
    elif (data.shape)[0]==1:
        return data[0]
    else:
        return data

#HW4 Function
def calcAccuracy(X,w,T):
    acct=np.zeros(1);
    for x,t in zip(X,T):
        xa = np.append(1,x);
        xaw = xa.dot(w);
        if (xaw * t > 0):
            acct+=1;
    return acct/len(T);
def getBinaryClassifier(X,T):
    newX=np.insert(X,0,1,axis=1);
    Xp = np.linalg.pinv(newX);
    return Xp.dot(T)
def oldGetBinaryClassifier(X,T):
    accuracy=0;
    rate=1;
    blind_training=500000;
    active_training=200;
    size=len(T);
    w=np.append(0,np.ones(15));
    #while (accuracy < 0.82 or active_training > 0):
    while (active_training > 0):
        i=np.random.randint(size);
        xa = np.append(1,X[i]);
        xaw = xa.dot(w);
        if (T[i] == 1 and xaw < 0):
            w+=rate*xa;
        elif (T[i] == -1 and xaw > 0):
            w-=rate*xa;
        if blind_training < 0:
            new_accuracy = calcAccuracy(X,w,T);
            if (new_accuracy > accuracy):
                W = w;
                accuracy = new_accuracy;
            active_training -= 1;
        else:
            blind_training -= 1;
    W/=np.linalg.norm(W);
    return [accuracy,W]


excelfile=r"/Users/fdu/Dropbox/course/DBDA408/hw4/Assignment_4_Fenchao_Du.xlsx";
data=readExcel(excelfile);
queries=(readExcel(excelfile,
                  sheetname='To be classified',
                  startrow=5,
                  endrow=54,
                  startcol=1,
                  endcol=15)).astype(float);

np.set_printoptions(suppress=True)

X=np.array(data[:,0:15],dtype=float);
T=np.array(data[:,15],dtype=int);
Type=np.array(data[:,16],dtype=int);

size=len(T);
Ty=-np.ones((size,6));
for i in range(size):
    Ty[i][Type[i]]=1;
#print Ty
#print Ty.shape

#Classfier
weight=getBinaryClassifier(X,T);
print "w: ", weight.T;

W=getBinaryClassifier(X,Ty);
#for i,t in enumerate(Ty.T):
#    [A[i],W[i]]=getBinaryClassifier(X,t);
#    print "\nAccuracy",i,": ",A[i];
#    print "W",i,": ",W[i];
print W

#To be classfied
Q=np.insert(queries,0,1,axis=1);
cT=Q.dot(weight);
print cT/np.absolute(cT)
cType=Q.dot(W);
#print W.T[0]
#print cType
print cType.argmax(axis=1)

#Extra
WB = (W.dot(W.T));
Xb = np.append([1],X[0]);
print WB.dot(Xb)
print np.linalg.norm(Xb, WB.dot(Xb))
Xb = np.append([1],X[1]);
print WB.dot(Xb)
print np.linalg.norm(Xb, WB.dot(Xb))
Xb = np.append([1],X[2]);
print WB.dot(Xb)
print np.linalg.norm(Xb, WB.dot(Xb))
Xb = np.append([1],X[3]);
print WB.dot(Xb)
print np.linalg.norm(Xb, WB.dot(Xb))
Xb = np.append([1],X[5]);
print WB.dot(Xb)
print np.linalg.norm(Xb, WB.dot(Xb))
Xb = np.append([1],X[6]);
print WB.dot(Xb)
print np.linalg.norm(Xb, WB.dot(Xb))

#Performance
FF=0;
FP=0;
PF=0;
PP=0;
for i in range(size):
    xa = np.append(1,X[i]);
    xaw = xa.dot(weight);
    if (T[i] == 1 and xaw > 0):
        FF+=1;
    elif (T[i] == 1 and xaw < 0):
        FP+=1;
    elif (T[i] == -1 and xaw > 0):
        PF+=1;
    elif (T[i] == -1 and xaw < 0):
        PP+=1;
print FF,FP
print PF,PP

MAT=np.zeros((6,6));
newX=np.insert(X,0,1,axis=1);
classLabel=(newX.dot(W)).argmax(axis=1);
#classLabel=(X.dot(W.T[1:])/np.absolute(W.T[0])).argmax(axis=1);
#print classLabel;
#print classLabel.shape;
for i in range(size):
    MAT[Type[i]][classLabel[i]]+=1;
print "Confusion Matrix:\n",MAT;
