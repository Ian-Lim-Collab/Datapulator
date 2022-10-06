#include "DataPulator.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DataPulator::DataPulator(char *file_path) {
  previous_data = 0;
  openFile(file_path);
  for (int i = 0; i < 80; i++) {
    filePath[i] = file_path[i];
  }
}

DataPulator::~DataPulator() { printf("Class Deconstructed\n"); }

void DataPulator::updateLine() {
  if (fscanf(file, "%s\n", stream) != EOF) {
  };
};

void DataPulator::setGain(double gain_input) { gain = gain_input; }

void DataPulator::setOffset(double offset_input) { offset = offset_input; }

void DataPulator::reformat() {
  //converts the data in to double for further processing
  char *intermediate;
  char *pEnd;
  intermediate = strtok(stream, ",");
  processed_stream[0] = strtod(intermediate, &pEnd);
  intermediate = strtok(NULL, ",");
  processed_stream[1] = strtod(intermediate, &pEnd);
}

void DataPulator::correction() {
  //adjust for bias and scale
  processed_stream[1] = (processed_stream[1] - offset) * gain;
}

void DataPulator::getMaxRow() {
  lastRow = 0;
  char rowNum[80];
  for (; fscanf(file, "%s", rowNum) != EOF;) {
    lastRow++;
  }
  reopen();//this must be call as the for loop above goes to the bottom of the file
}

void DataPulator::openFile(char *file_path) {
  file = fopen(file_path, "r");
  if (file == NULL) {
    printf("File path Error");
  } else {
    printf("Open File \n");
  }
}
void DataPulator::closeFile() { fclose(file); }

void DataPulator::reopen() {
  closeFile();
  openFile(filePath);
}

void DataPulator1::preProcess() {
  processed_stream[1] = 2. * sqrt(processed_stream[1]) / 3.;
}

void DataPulator2::preProcess() {
  current_data = processed_stream[1];
  processed_stream[1] = processed_stream[1] - previous_data;
  previous_data = current_data;
}

DataPulator1::DataPulator1(char *file_path)
    : DataPulator::DataPulator(file_path) {}
DataPulator1::~DataPulator1() { fclose(file); }

DataPulator2::DataPulator2(char *file_path)
    : DataPulator::DataPulator(file_path) {}
DataPulator2::~DataPulator2() { fclose(file); }