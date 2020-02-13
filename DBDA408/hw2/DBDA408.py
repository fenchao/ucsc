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
def writeExcelData(x,excelfile,sheetname,startrow,startcol):
    from pandas import DataFrame, ExcelWriter
    from openpyxl import load_workbook
    df=DataFrame(x)
    book = load_workbook(excelfile)
    writer = ExcelWriter(excelfile, engine='openpyxl') 
    writer.book = book
    writer.sheets = dict((ws.title, ws) for ws in book.worksheets)
    df.to_excel(writer, sheet_name=sheetname,startrow=startrow-1, startcol=startcol-1, header=False, index=False)
    writer.save()
    writer.close()
def getSheetNames(excelfile):
    from pandas import ExcelFile
    return (ExcelFile(excelfile)).sheet_names
def Build2DHistogramClassifier(X,A,amin,amax,B,bmin,bmax,binSize):
    HF=np.zeros((binSize,binSize)).astype('int32');
    HM=np.zeros((binSize,binSize)).astype('int32');
    aBound=(np.round(((binSize-1)*(A-amin)/(amax-amin)))).astype('int32');
    bBound=(np.round(((binSize-1)*(B-bmin)/(bmax-bmin)))).astype('int32');
    for i in range(X.size):
        if X[i]=='Female':
            HF[aBound[i]][bBound[i]]+=1; #[height][handSpan] height is vertical
        else:
            HM[aBound[i]][bBound[i]]+=1;
    return [HF, HM]
def Analyze(X,A,B):
    femaleSize,maleSize,femaleHeight,maleHeight,femaleHandSpan,maleHandSpan = 0,0,0,0,0,0;
    for sex,a,b in zip(X,A,B) :
        if sex=='Female':
            femaleHeight+=a;
            femaleHandSpan+=b;
            femaleSize+=1;
        else:
            maleHeight+=a;
            maleHandSpan+=b;
            maleSize+=1;
    femaleHeight = femaleHeight/femaleSize;
    maleHeight = maleHeight/maleSize;
    femaleHandSpan = femaleHandSpan/femaleSize;
    maleHandSpan = maleHandSpan/maleSize;

    CMF=np.zeros((2,2));
    CMM=np.zeros((2,2));
    for sex,a,b in zip(X,A,B) :
        if sex=='Female':
            CMF[0][0]+=(a-femaleHeight)**2
            CMF[0][1]+=(a-femaleHeight)*(b-femaleHandSpan)
            CMF[1][0]+=(a-femaleHeight)*(b-femaleHandSpan)
            CMF[1][1]+=(b-femaleHandSpan)**2
        else:
            CMM[0][0]+=(a-maleHeight)**2
            CMM[0][1]+=(a-maleHeight)*(b-maleHandSpan)
            CMM[1][0]+=(a-maleHeight)*(b-maleHandSpan)
            CMM[1][1]+=(b-maleHandSpan)**2
    CMF/=femaleSize-1;
    CMM/=maleSize-1;
    return [femaleSize,maleSize,femaleHeight,maleHeight,femaleHandSpan,maleHandSpan,CMF,CMM]
def Apply2DHistogramClassifier(queries,HF,HM,amin,amax,bmin,bmax):
    binSize=np.alen(HF);
    queries=queries.T;
    aBound=np.clip((np.round(((binSize-1)*(queries[0]-amin)/(amax-amin)))).astype('int32'),0,binSize-1);
    bBound=np.clip((np.round(((binSize-1)*(queries[1]-bmin)/(bmax-bmin)))).astype('int32'),0,binSize-1);
    B=queries[0].size;
    countF=np.zeros(B).astype(float);
    countM=np.zeros(B).astype(float);
    for i in range(B):
        countF[i]=HF[aBound[i]][bBound[i]];
        countM[i]=HM[aBound[i]][bBound[i]];
    resultlabel=np.full(B,"Indeterminate",dtype=object);
    resultprob=np.full(B,np.nan,dtype=object);
    indicesF=countF>countM;
    indicesM=countM>countF;
    resultlabel[indicesF]="Female";
    resultlabel[indicesM]="Male";
    probF=countF/(countF+countM);
    probM=countM/(countF+countM);
    resultprob[indicesF]=probF[indicesF];
    resultprob[indicesM]=probM[indicesM];
    return resultlabel, resultprob
def Apply2DBayesianClassifier(queries,CMF,CMM,femaleSize,maleSize,femaleHeight,maleHeight,femaleHandSpan,maleHandSpan):
    B=np.alen(queries);
    pdfF=np.zeros(B).astype(float);
    pdfM=np.zeros(B).astype(float);
    for i in range(B):
        pdfF[i] = (np.exp(-0.5*(np.dot(np.dot((queries[i]-[femaleHeight,femaleHandSpan]),np.linalg.inv(CMF)),(queries[i]-[femaleHeight,femaleHandSpan]).T))))/(2*np.pi*(np.linalg.det(CMF)**.5));
        pdfM[i] = (np.exp(-0.5*(np.dot(np.dot((queries[i]-[maleHeight,maleHandSpan]),np.linalg.inv(CMM)),(queries[i]-[maleHeight,maleHandSpan]).T))))/(2*np.pi*(np.linalg.det(CMM)**.5));
    resultlabel=np.full(np.alen(queries),"Indeterminate",dtype=object);
    resultprob=np.full(np.alen(queries),np.nan,dtype=object);
    countF=pdfF*femaleSize;
    countM=pdfM*maleSize;
    indicesF=countF>countM;
    indicesM=countM>countF;
    resultlabel[indicesF]="Female";
    resultlabel[indicesM]="Male";
    probF=countF/(countF+countM);
    probM=countM/(countF+countM);
    resultprob[indicesF]=probF[indicesF];
    resultprob[indicesM]=probM[indicesM];
    return resultlabel, resultprob
def Reconstruct(amin,amax,bmin,bmax,binSize,CMF,CMM,femaleSize,maleSize,femaleHeight,maleHeight,femaleHandSpan,maleHandSpan):
    astep=(amax-amin)/binSize;
    bstep=(bmax-bmin)/binSize;
    A=np.arange(amin,amax,astep)+astep/2;
    B=np.arange(bmin,bmax,bstep)+bstep/2;
    pdfF=np.zeros((binSize,binSize)).astype(float);
    pdfM=np.zeros((binSize,binSize)).astype(float);
    area=astep*bstep;
    for i in range(binSize):
        for j in range(binSize):
            q=np.array([A[i],B[j]]);
            pdfF[i][j] = (np.exp(-0.5*(np.dot(np.dot((q-[femaleHeight,femaleHandSpan]),np.linalg.inv(CMF)),(q-[femaleHeight,femaleHandSpan]).T))))/(2*np.pi*(np.linalg.det(CMF)**.5));
            pdfM[i][j] = (np.exp(-0.5*(np.dot(np.dot((q-[maleHeight,maleHandSpan]),np.linalg.inv(CMM)),(q-[maleHeight,maleHandSpan]).T))))/(2*np.pi*(np.linalg.det(CMM)**.5));
    RHF=pdfF*area*femaleSize;
    RHM=pdfM*area*maleSize;
    return [RHF, RHM]

excelfile=r"/Users/fdu/Dropbox/course/DBDA408/hw2/Assignment_2_Data_and_Template.xlsx";
sheets=getSheetNames(excelfile);
data=readExcel(excelfile);
queries=(readExcel(excelfile,
                  sheetname='Queries',
                  startrow=3,
                  endrow=6,
                  startcol=1,
                  endcol=2)).astype(float).reshape(4,2);

sex=np.array([str(g) for g in data[:,0]])
height=np.array(data[:,1],dtype=float)
handSpan=np.array(data[:,2],dtype=float)

binSize=10;
minHeight=np.amin(height);
maxHeight=np.amax(height);
minHandSpan=np.amin(handSpan);
maxHandSpan=np.amax(handSpan);
print "minHeight:",minHeight,"maxHeight:",maxHeight,"minHandSpan:",minHandSpan,"maxHandSpan:",maxHandSpan
print "No. of bins",binSize,"*",binSize
[HF,HM]=Build2DHistogramClassifier(sex,height,minHeight,maxHeight,handSpan,minHandSpan,maxHandSpan,binSize);
print "Female Historgram"
print HF
print "Male Historgram"
print HM
[femaleSize,maleSize,femaleHeight,maleHeight,femaleHandSpan,maleHandSpan,CMF,CMM]=Analyze(sex,height,handSpan)
print "Female Height:",femaleHeight,"Female HandSpan:",femaleHandSpan
print "Male Height:",maleHeight,"Male HandSpan:",maleHandSpan
print "Female Covariance Matrix:\n",CMF
print "Male Covariance Matrix:\n",CMM
print "Female Size:",femaleSize,"Male Size:",maleSize

[resultHlabel, resultHprob]=Apply2DHistogramClassifier(queries,HF,HM,minHeight,maxHeight,minHandSpan,maxHandSpan);
print(DataFrame([resultHlabel, resultHprob]).T)
[resultHlabel, resultHprob]=Apply2DBayesianClassifier(queries,CMF,CMM,femaleSize,maleSize,femaleHeight,maleHeight,femaleHandSpan,maleHandSpan);
print(DataFrame([resultHlabel, resultHprob]).T)
[RHF,RHM]=Reconstruct(minHeight,maxHeight,minHandSpan,maxHandSpan,binSize,CMF,CMM,femaleSize,maleSize,femaleHeight,maleHeight,femaleHandSpan,maleHandSpan);
np.set_printoptions(suppress=True);
print "Re Female Historgram"
print RHF
print "Re Male Historgram"
print RHM
