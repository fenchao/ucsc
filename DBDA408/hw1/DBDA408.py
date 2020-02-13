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
def Build1DHistogramClassifier(X,T,B,xmin,xmax):
    HF=np.zeros(B).astype('int32');
    HM=np.zeros(B).astype('int32');
    binindices=(np.round(((B-1)*(X-xmin)/(xmax-xmin)))).astype('int32');
    for i,b in enumerate(binindices):
        if T[i]=='Female':
            HF[b]+=1;
        else:
            HM[b]+=1;
    return [HF, HM]
def Analyze(X,T):
    MF,MM,SDF,SDM,SF,SM = 0,0,0,0,0,0;
    for h,s in zip(X,T) :
        if s=='Female':
            MF+=h;
            SF+=1;
        else:
            MM+=h;
            SM+=1;
    MF = MF/SF;
    MM = MM/SM;
    for h,s in zip(X,T) :
        if s=='Female':
            SDF+=(MF-h)**2
        else:
            SDM+=(MM-h)**2
    SDF = (SDF/SF)**.5;
    SDM = (SDM/SM)**.5;
    return [MF,MM,SDF,SDM,SF,SM]
def Apply1DHistogramClassifier(queries,HF,HM,xmin,xmax):
    B=np.alen(HF);
    binindices=np.clip((np.round(((B-1)*(queries-xmin)/(xmax-xmin)))).astype('int32'),0,B-1);
    countF=HF[binindices].astype(float);
    countM=HM[binindices].astype(float);
    resultlabel=np.full(np.alen(binindices),"Indeterminate",dtype=object);
    resultprob=np.full(np.alen(binindices),np.nan,dtype=object);
    indicesF=countF>countM;
    indicesM=countM>countF;
    resultlabel[indicesF]="Female";
    resultlabel[indicesM]="Male";
    probF=countF/(countF+countM);
    probM=countM/(countF+countM);
    resultprob[indicesF]=probF[indicesF];
    resultprob[indicesM]=probM[indicesM];
    return resultlabel, resultprob
def Apply1DBayesianClassifier(queries,MF,MM,SDF,SDM,SF,SM):
    pdfF = (np.exp(-0.5*((queries-MF)/SDF)**2))/(np.sqrt(2*np.pi)*SDF);
    pdfM = (np.exp(-0.5*((queries-MM)/SDM)**2))/(np.sqrt(2*np.pi)*SDM);
    resultlabel=np.full(np.alen(queries),"Indeterminate",dtype=object);
    resultprob=np.full(np.alen(queries),np.nan,dtype=object);
    countF=pdfF*SF;
    countM=pdfM*SM;
    indicesF=countF>countM;
    indicesM=countM>countF;
    resultlabel[indicesF]="Female";
    resultlabel[indicesM]="Male";
    probF=countF/(countF+countM);
    probM=countM/(countF+countM);
    resultprob[indicesF]=probF[indicesF];
    resultprob[indicesM]=probM[indicesM];
    return resultlabel, resultprob

excelfile=r"/Users/fdu/Dropbox/course/DBDA408/hw1/Assignment_1_Data_and_Template.xlsx";
sheets=getSheetNames(excelfile);
data=readExcel(excelfile);
queries=(readExcel(excelfile,
                  sheetname='Queries',
                  startrow=3,
                  endrow=8,
                  startcol=1,
                  endcol=1)).astype(float).reshape(6);
print queries

print "\nClassifiers - Full Data"
X=np.array(data[:,0]*12+data[:,1],dtype=float)
T=np.array([str(g) for g in data[:,2]])
B=32;
xmin=np.amin(X);
xmax=np.amax(X);
[HF,HM]=Build1DHistogramClassifier(X,T,B,xmin,xmax);
[MF,MM,SDF,SDM,SF,SM]=Analyze(X,T);
print "xmin:",xmin,"xmax:",xmax,"\nHF:",HF,"\nHM:",HM,"\nMeans F:",MF,"Means M:", MM,"STD F:",SDF,"STD M:",SDM,"Sample F:",SF,"Sample M:",SM
[resultHlabel, resultHprob]=Apply1DHistogramClassifier(queries,HF,HM,xmin,xmax)
print(DataFrame([resultHlabel, resultHprob]).T)
[resultHlabel, resultHprob]=Apply1DBayesianClassifier(queries,MF,MM,SDF,SDM,SF,SM);
print(DataFrame([resultHlabel, resultHprob]).T)
#Plot Start
plt.figure(figsize=(10,5));
opacity = 0.5
[bincenters,binwidth]=np.linspace(xmin, xmax, num=B, retstep=True);
rects1 = plt.bar(bincenters-(binwidth/2), HF, binwidth,
                 alpha=opacity,
                 color='pink',
                 edgecolor='black',
                 label='Female')
rects2 = plt.bar(bincenters+(binwidth/2), HM, binwidth,
                 alpha=opacity,
                 color='b',
                 edgecolor='black',
                 label='Male')
plt.xlabel('Height')
plt.ylabel('Count')
plt.xticks(bincenters, bincenters.astype('int32'), fontsize=10)
plt.legend()
plt.show()
#Plot End

print "\nClassifiers - Partial Data"
partialSize = 50;
X=np.array(data[:partialSize,0]*12+data[:partialSize,1],dtype=float)
T=np.array([str(g) for g in data[:partialSize,2]])
B=32;
#xmin=np.amin(X); # use same value
#xmax=np.amax(X);
[HF,HM]=Build1DHistogramClassifier(X,T,B,xmin,xmax);
[MF,MM,SDF,SDM,SF,SM]=Analyze(X,T);
print "xmin:",xmin,"xmax:",xmax,"\nHF:",HF,"\nHM:",HM,"\nMeans F:",MF,"Means M:", MM,"STD F:",SDF,"STD M:",SDM,"Sample F:",SF,"Sample M:",SM
[resultHlabel, resultHprob]=Apply1DHistogramClassifier(queries,HF,HM,xmin,xmax)
print(DataFrame([resultHlabel, resultHprob]).T)
[resultHlabel, resultHprob]=Apply1DBayesianClassifier(queries,MF,MM,SDF,SDM,SF,SM);
print(DataFrame([resultHlabel, resultHprob]).T)
#Plot Start
plt.figure(figsize=(10,5));
opacity = 0.5
[bincenters,binwidth]=np.linspace(xmin, xmax, num=B, retstep=True);
rects1 = plt.bar(bincenters-(binwidth/2), HF, binwidth,
                 alpha=opacity,
                 color='pink',
                 edgecolor='black',
                 label='Female')
rects2 = plt.bar(bincenters+(binwidth/2), HM, binwidth,
                 alpha=opacity,
                 color='b',
                 edgecolor='black',
                 label='Male')
plt.xlabel('Height')
plt.ylabel('Count')
plt.xticks(bincenters, bincenters.astype('int32'), fontsize=10)
plt.legend()
plt.show()
#Plot End

