Steps to run:
0. Create your base folder and go into base folder
1. Download all .py file and create empty folders
2. Download apple.npy cow.npy dog.npy bed.npy to folder "rawData"
3. run python in following order:
        ./reader.py                                     - convert rawData to readerData
        ./PCA.py (xzcvpr) or ./PCA1.py (sklearn)        - convert X in readerData to P in pcaData
        ./linear.py 60                                  - run to get trained classifier, accuracy, confusion matrix
        ./predict.py linear 60 img/dog.png              - select classifier and see prediction
