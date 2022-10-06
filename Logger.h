#ifndef Logger_h_
#define Logger_h_

#include <stdio.h>

class Logger{
  private:
    FILE*log_file;
  public:
    Logger(char* filePath);
    ~Logger();
    int log(double* DataArray);//insert data in the file
    int motor_log(double* DataArray);//insert formatted data(into the format of motor)into file
    void closeFile();
    void NamingColumns();//insert "row ,data" in the file typically call at the start before writing data
    void NamingColumns(char* Col_1,char* Col_2,char* Col_3);//insert args in the file typically call at the start before writing data
     
};

#endif