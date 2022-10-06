# Datapulator

Code for EE10170 Mechtronics and Robotics CW1
Created By Lim Ian il356 Student ID:219046099
Last modified:10th April 2022
main function could take argments of 
  -m
  -m dataFile
  -m dataFiles Log files
  -g gainValues offsetValues
  -mg dataFiles LogFiles gainValues offsetValues

all the input arguement when running in the CLI must be in the order of Sensor 1 -> Sensor 2 -> Sensor 3





The Datapulator is created to take input data stream from 3 different sources, processing ,fusing and outputing two opposing digital signal to control motors.

The Fusion Algo is Simply the ratio of the difference between data stream 1 and 3 and the stream 2
(Stream 1 - Stream 3)/Stream 2

