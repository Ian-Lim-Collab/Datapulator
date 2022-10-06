#ifndef DataPulator_h_
#define DataPulator_h_
//protective clause from overwriting definition

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

class DataPulator
{
protected:
    char stream[80];
    char filePath[80];
    double previous_data,current_data;
    double offset;
    double gain;
    FILE *file;
    
public:
    double processed_stream[2];
    int lastRow;
    DataPulator(char * file_path);
    //when initailes the file is open
    ~DataPulator();
    //when destroyed print class deconstucted
    void updateLine();
    //fetches new line from the file
    void reformat();
    //convert the string data and row into double and place it in the public domain under the name processed_stream
    void correction();
    //apply the bias and scalling correction
    void setGain(double gain_input);
    void setOffset(double offset_input);

    void getMaxRow();
    // get the max number of row in the file

    void openFile(char *file_path);
    void closeFile();
    void reopen();
      
};

class DataPulator1: public DataPulator
{
public:
    DataPulator1(char * file_path);
    ~DataPulator1();
    void preProcess();//process the raw sensor data for fusion    
};

class DataPulator2: public DataPulator
{
public:
    DataPulator2(char * file_path);
    ~DataPulator2();
    void preProcess();//process the raw sensor data for fusion
};

#endif
