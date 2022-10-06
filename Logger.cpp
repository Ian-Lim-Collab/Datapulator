#include "Logger.h"

#include <stdio.h>
#include <stdlib.h>

Logger::Logger(char * filePath){
  log_file = fopen(filePath,"w");
  if(log_file == NULL){
    printf("Unexpected Error in Logging\n");
  }else{
    printf("Ready to Log\n");
  }
}

Logger::~Logger(){
  fclose(log_file);
}

int Logger::log(double* DataArray){
  fprintf(log_file,"%i,%f\n",(int)DataArray[0],DataArray[1]);
  return 0;
}

int Logger::motor_log(double* DataArray){
  if (DataArray[1] > 1) {
      DataArray[1] = 1;
    }
  fprintf(log_file,"%i,%f,%f\n",(int)DataArray[0],DataArray[1],-DataArray[1]);
  return 0;
}

void Logger::NamingColumns(){
  fprintf(log_file, "Row, Data\n");
}

void Logger::NamingColumns(char* Col_1,char* Col_2, char* Col_3){
  fprintf(log_file,"%s,%s,%s\n",Col_1,Col_2,Col_3);
}

void Logger::closeFile(){
  fclose(log_file);
}