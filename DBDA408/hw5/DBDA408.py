#!/usr/bin/python
import numpy as np
import matplotlib.pyplot as plt
from pandas import DataFrame
from sklearn import mixture

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

excelfile=r"/Users/fdu/Dropbox/course/DBDA408/hw5/Assignment_5_Fenchao_Du_Data_and_Template.xlsx";
data=readExcel(excelfile);

np.set_printoptions(suppress=True)

clf = mixture.GaussianMixture(n_components=3, covariance_type='full');

clf.fit(data)
CL=clf.predict(data)
CF=clf.predict_proba(data)

unique, counts = np.unique(CL, return_counts=True)

# 0-F, 1-M, 2-C
for i in range(len(CL)):
    if CL[i]==0:
        plt.scatter(data[i][0], data[i][1], color='r');
    elif CL[i]==1:
        plt.scatter(data[i][0], data[i][1], color='b');
    else:
        plt.scatter(data[i][0], data[i][1], color='y');
plt.xlabel('Height_in')
plt.ylabel('Handspan_cm')

print "Class Label\n",CL
print "Confidence"
print np.amax(CF,axis=1)*100

print "Red    Blue  Yellow"
print counts
plt.show()

