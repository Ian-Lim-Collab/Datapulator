#ifndef Datapulator_h
#define Datapulator_h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

class Datapulator
{
private:
    FILE *file;
public:
    Datapulator(/* args */);
    ~Datapulator();
    void getData(char StreamNum);
};
#endif