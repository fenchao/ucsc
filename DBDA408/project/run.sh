#!/bin/bash

#clear window
clear

#welcome message
echo -e "Welcome to TEAM1 Machine Learning Predictor!\r\n"

#run predictor
path=""
while [[ $path != "q" ]] ; do
    echo -e "Which image did you just draw? (q to quit)"
    read path
    if [ $path != "q" ]; then
        ./predict.py linear 60 /Users/fdu/Desktop/$path
    fi
    echo -e
done

#exit
echo Thanks for using TEAM1 Machine Learning Predictor!
