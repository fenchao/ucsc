#!/usr/bin/python

import struct
import numpy as np
import numpy.linalg as LA
from array import array
import matplotlib.pyplot as plt

def load_mnist(dataset="training", selecteddigits=range(10), path=r'/Users/fdu/Dropbox/course/DBDA408/hw3'):

    #Check training/testing specification. Must be "training" (default) or "testing"
    if dataset == "training":
        fname_digits = path + '/' + 'train-images-idx3-ubyte'
        fname_labels = path + '/' + 'train-labels-idx1-ubyte'
    elif dataset == "testing":
        fname_digits = path + '/' + 't10k-images-idx3-ubyte'
        fname_labels = path + '/' + 't10k-labels-idx1-ubyte'
    else:
        raise ValueError("dataset must be 'testing' or 'training'")
        
        
    #Import digits data
    digitsfileobject = open(fname_digits, 'rb')
    magic_nr, size, rows, cols = struct.unpack(">IIII", digitsfileobject.read(16))
    digitsdata = array("B", digitsfileobject.read())
    digitsfileobject.close()

    #Import label data
    labelsfileobject = open(fname_labels, 'rb')
    magic_nr, size = struct.unpack(">II", labelsfileobject.read(8))
    labelsdata=array("B",labelsfileobject.read())
    labelsfileobject.close()
    
    #Find indices of selected digits
    indices=[k for k in range(size) if labelsdata[k] in selecteddigits]
    N=len(indices)
    
    #Create empty arrays for X and T
    X = np.zeros((N, rows*cols), dtype=np.uint8)
    T = np.zeros((N, 1), dtype=np.uint8)
    
    #Fill X from digitsdata
    #Fill T from labelsdata
    for i in range(N):
        X[i] = digitsdata[indices[i]*rows*cols:(indices[i]+1)*rows*cols]
        T[i] = labelsdata[indices[i]]
    
    return X,T

def vectortoimg(v,show=True):
    plt.imshow(v.reshape(28, 28),interpolation='None', cmap='gray')
    plt.axis('off')
    if show:
        plt.show()

np.set_printoptions(precision=10);
np.set_printoptions(suppress=True);
#np.set_printoptions(threshold=np.nan);

POS=8;
NEG=1;
X, T = load_mnist(dataset="training",selecteddigits=[1,8])
#print "X\n",X
#print T

#print("Checking shape of matrix:", X.shape)
#print("Checking min/max values:",(np.amin(X),np.amax(X)))
#print("Checking unique labels in T:",list(np.unique(T)))

#print("Checking one training vector by plotting image:")
#print X[20]
#vectortoimg(X[20])

#print("Checking multiple training vectors by plotting images.\nBe patient:")
#plt.close('all')
#fig = plt.figure()
#nrows=10
#ncols=10
#for row in range(nrows):
#    for col in range(ncols):
#        plt.subplot(nrows, ncols, row*ncols+col + 1)
#        vectortoimg(X[np.random.randint(len(T))],show=False)
#plt.show()

mu=np.mean(X,axis=0);
#print(mu)
#print mu.shape

Z=X-mu;
#print Z[20]

C=np.cov(Z,rowvar=False);
#print "C\n"

[lamb,V]=LA.eigh(C);
#print lamb
#n=-1
#row=V[n,:];col=V[:,n];
#print np.dot(C,row)-(lamb[n]*row)
#print np.dot(C,col)-(lamb[n]*col) # col is eign vector, all 0s here
lamb=np.flipud(lamb);V=np.flipud(V.T);
#n=3
#row=V[n,:];col=V[:,n];
#print np.dot(C,row)-(lamb[n]*row) # row is eign vector, after transpose
#print np.dot(C,col)-(lamb[n]*col)
#print("Checking shape of V matrix:", V.shape)
#print(lamb,"\n\n",V) #### check row and col of V
#row=V[0,:]; #Check once again
#col=V[:,0];
#print np.dot(C,row)-(lamb[0]*row) #If the matrix product C.row is the same as lamb[0]*row, this should evaluate to [0,0,0]
#print np.allclose(np.dot(C,row),lamb[0]*row) # confirm it's row now, True here
#print np.allclose(np.dot(C,col),lamb[0]*col)

#print "verify\n",np.dot(V,V.T)
#print "verfify2\n",np.dot(V.T,V)

P=np.dot(Z,V.T);
#print(P)

R=np.dot(P,V);
#print np.allclose(R,Z); #verified, if no reduction, True
#print(R-Z)

Xrec=R+mu;
#print np.allclose(Xrec,X); # True, restored here
#print(Xrec-X)

Xrec1=(np.dot(P[:,0:1],V[0:1,:]))+mu;
#print(Xrec1[20])
#vectortoimg(Xrec1[20])
Xrec2=(np.dot(P[:,0:2],V[0:2,:]))+mu;
#print("Checking shape of P-2d matrix:", P[:,0:2].shape)
#print(Xrec2)
#vectortoimg(Xrec2[20])
Xrec3=(np.dot(P[:,0:3],V[0:3,:]))+mu;
#print(Xrec3)
#vectortoimg(Xrec3[20])
#vectortoimg(((np.dot(P[:,0:20],V[0:20,:]))+mu)[20])
#vectortoimg(X[20])

##### REAL HW BEGIN #####
#print "lambda 0 & 1: ",lamb[0],lamb[1]
#print "mean vector:\n",mu
#print "row0:\n",V[0,:]
#print "row1:\n",V[1,:]

P2=P[:,0:2];
#NPOS=NNEG=0;
NPOS=np.zeros(1).astype('float');
NNEG=np.zeros(1).astype('float');
MUP=np.zeros(2).astype('float');
MUN=np.zeros(2).astype('float');
print P[0][0],P[0][1]
for i in range(len(T)):
    if T[i] == POS:
#        plt.scatter(P[i][0], P[i][1], color='r');
        NPOS+=1;
        MUP+=P[i,0:2]
    else:
#        plt.scatter(P[i][0], P[i][1], color='b');
        NNEG+=1;
        MUN+=P[i,0:2]
#plt.xlabel('pc1')
#plt.ylabel('pc2')
#plt.show();
#print NPOS,NNEG
MUP/=NPOS;
MUN/=NNEG;
print "Mean Vectors: ",MUP,MUN

#calc covariance matrix
CMP=np.zeros((2,2)).astype('float');
CMN=np.zeros((2,2)).astype('float');
for i in range(len(T)):
    if T[i] == POS:
        CMP[0][0]+=(P[i,0]-MUP[0])**2;
        CMP[0][1]+=(P[i,0]-MUP[0])*(P[i,1]-MUP[1]);
        CMP[1][0]+=(P[i,0]-MUP[0])*(P[i,1]-MUP[1]);
        CMP[1][1]+=(P[i,1]-MUP[1])**2;
    else:
        CMN[0][0]+=(P[i,0]-MUN[0])**2;
        CMN[0][1]+=(P[i,0]-MUN[0])*(P[i,1]-MUN[1]);
        CMN[1][0]+=(P[i,0]-MUN[0])*(P[i,1]-MUN[1]);
        CMN[1][1]+=(P[i,1]-MUN[1])**2;
CMP/=NPOS-1;
CMN/=NNEG-1;
print "covariance matrix CP\n", CMP
print "covariance matrix CN\n", CMN

P0=[np.amin(P[:,0]),np.amax(P[:,0])];
print "P0 MIN,MAX: ", P0[0],P0[1]
P1=[np.amin(P[:,1]),np.amax(P[:,1])];
print "P1 MIN,MAX: ", P1[0],P1[1]

P2MIN=np.array([P0[0],P1[0]])
P2MAX=np.array([P0[1],P1[1]])
#print "P2 MIN,MAX: ",P2MIN,P2MAX

#Build Histogram
B=32;
HP=np.zeros((32,32)).astype('float');
HN=np.zeros((32,32)).astype('float');
binindices=(np.round(((B-1)*(P2-P2MIN)/(P2MAX-P2MIN)))).astype('int32');
for i in range(len(T)):
    p0 = binindices[i][0];
    p1 = binindices[i][1];
#    print p0,p1
    if T[i] == POS:
        HP[p0][p1]+=1;
    else:
        HN[p0][p1]+=1;
np.set_printoptions(threshold=np.nan)
#print "Historgram of Positive\n", HP
#print "Historgram of Negative\n", HN

## Testing
#X
Xt, Tt = load_mnist(dataset="testing",selecteddigits=[1,8])
#print Tt[45]
xp=Xt[45]
#vectortoimg(xp)
#print Tt[15]
xn=Xt[15]
#vectortoimg(xn)
#print "xp: ",xp
#print "xn: ",xn

#Z
zp=xp-mu;
zn=xn-mu;
#print "zp: ",zp
#print "zn: ",zn

#P
pp=np.dot(zp,V.T[:,0:2]);
pn=np.dot(zn,V.T[:,0:2]);
print "pp: ",pp
print "pn: ",pn

#R
rp=np.dot(pp,V[0:2,:]);
rn=np.dot(pn,V[0:2,:]);
#print "rp: ",rp
#print "rn: ",rn

#Xrec
xrecp=rp+mu;
xrecn=rn+mu;
#print "xrecp: ",xrecp
#print "xrecn: ",xrecn
#vectortoimg(xp)
#vectortoimg(xrecp)
#vectortoimg(xn)
#vectortoimg(xrecn)

#Histogram Prediction
B=32;
bp=(np.round(((B-1)*(pp-P2MIN)/(P2MAX-P2MIN)))).astype('int32');
bn=(np.round(((B-1)*(pn-P2MIN)/(P2MAX-P2MIN)))).astype('int32');
#print "bp: ",bp
#print "bn: ",bn
#print "HPvsHN on bp",HP[bp[0]][bp[1]],HN[bp[0]][bp[1]]
#print "HPvsHN on bn",HP[bn[0]][bn[1]],HN[bn[0]][bn[1]]
probp=(HP[bp[0]][bp[1]])/(HP[bp[0]][bp[1]]+HN[bp[0]][bp[1]]);
probn=(HN[bn[0]][bn[1]])/(HP[bn[0]][bn[1]]+HN[bn[0]][bn[1]]);
print "probp: ",probp
print "probn: ",probn

#Bayesian Prediction
#print CMP,CMN
#print MUP,MUN
Q1p=(NPOS/(LA.det(CMP))**.5)*np.exp(-0.5*(pp-MUP).dot(LA.inv(CMP)).dot((pp-MUP).T));
Q2p=(NNEG/(LA.det(CMN))**.5)*np.exp(-0.5*(pp-MUN).dot(LA.inv(CMN)).dot((pp-MUN).T));
print "Bay on pos: ",Q1p/(Q1p+Q2p)
Q1n=(NPOS/(LA.det(CMP))**.5)*np.exp(-0.5*(pn-MUP).dot(LA.inv(CMP)).dot((pn-MUP).T));
Q2n=(NNEG/(LA.det(CMN))**.5)*np.exp(-0.5*(pn-MUN).dot(LA.inv(CMN)).dot((pn-MUN).T));
print "Bay on neg: ",Q2n/(Q1n+Q2n)

# Get training date
Xt, Tt = load_mnist(dataset="testing",selecteddigits=[1,8]);
Zt = Xt-mu;
Pt = np.dot(Zt,V.T[:,0:2]);
#print Pt.shape
#print Tt.shape

#Histogram Accuracy
ACCH=np.zeros(1).astype('float');
for i in range(len(Tt)):
    bt=(np.round(((B-1)*(Pt[i]-P2MIN)/(P2MAX-P2MIN)))).astype('int32');
    row=bt[0];
    col=bt[1];
    if (HP[row][col] > HN[row][col] and Tt[i]==POS) or (HP[row][col] < HN[row][col] and Tt[i]==NEG):
        ACCH+=1;
ACCH/=len(Tt);
print "Histogram Accuracy: ",ACCH

#Bayesian Accuracy
ACCB=np.zeros(1).astype('float');
for i in range(len(Tt)):
    Q1=(NPOS/(LA.det(CMP))**.5)*np.exp(-0.5*(Pt[i]-MUP).dot(LA.inv(CMP)).dot((Pt[i]-MUP).T));
    Q2=(NNEG/(LA.det(CMN))**.5)*np.exp(-0.5*(Pt[i]-MUN).dot(LA.inv(CMN)).dot((Pt[i]-MUN).T));
    if (Q1 > Q2 and Tt[i]==POS) or (Q1 < Q2 and Tt[i]==NEG):
        ACCB+=1;
#    else:
#        vectortoimg(Xt[i]);
ACCB/=len(Tt);
print "Bay Accuracy: ",ACCB

#print MUP,MUN
#print CMP,CMN
