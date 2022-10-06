/* 
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

all function writen uses C library for compatibility with C

 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DataPulator.h"
#include "Logger.h"

#define filePath1 "./_StreamData/sensor_1.csv"
#define filePath2 "./_StreamData/sensor_2.csv"
#define filePath3 "./_StreamData/sensor_3.csv"

#define lpAPath "./lp_a.csv"
#define lpBPath "./lp_b.csv"
#define lpCPath "./lp_c.csv"
#define lpDPath "./lp_d.csv"
#define lpEPath "./lp_e.csv"
#define lpFPath "./lp_f.csv"
#define lpMotorPath "./lp_motor.csv"

#define Gain1 2.7
#define offset1 1.
#define Gain2 0.7
#define offset2 -0.5
#define Gain3 1
#define offset3 0.2

// start of function prototying
int autoMode();
int autoModeGainChange(double gainInput1, double gainInput2, double gainInput3,
                       double offsetInput1, double offsetInput2,
                       double offsetInput3);

int manualMode();
int manualMode(char *file_path1, char *file_path2, char *file_path3);
int manualMode(char *file_path1, char *file_path2, char *file_path3,
               char *log_fileA, char *log_fileB, char *log_fileC,
               char *log_fileD, char *log_fileE, char *log_fileF,char *log_fileMotor);
int manualMode(char *file_path1, char *file_path2, char *file_path3,
               char *log_fileA, char *log_fileB, char *log_fileC,
               char *log_fileD, char *log_fileE, char *log_fileF, char *log_fileMotor,
               double gainInput1, double gainInput2, double gainInput3,
               double offsetInput1, double offsetInput2, double offsetInput3);

void Processing(DataPulator1 *Stream_1, DataPulator2 *Stream_2,
                DataPulator *Stream_3, Logger *LogA, Logger *LogB, Logger *LogC,
                Logger *LogD, Logger *LogE, Logger *LogF,Logger *LogMotor);

void Processing(DataPulator1 *Stream_1, DataPulator2 *Stream_2,
                DataPulator *Stream_3, Logger *LogA, Logger *LogB, Logger *LogC,
                Logger *LogD, Logger *LogE, Logger *LogF,Logger *LogMotor, double gainInput1,
                double gainInput2, double gainInput3, double offsetInput1,
                double offsetInput2, double offsetInput3);

void dataFusion(double *stream_1, double *stream_2, double *stream_3,
                double *output_stream);
int max(int a, int b);
int max(int a, int b, int c);
// end of function prototyping

int main(int argc, char **argv) {

  if (argc > 1) { // check if there is other arguement than ./
    if (strcmp("-m", argv[1]) ==
        0) { // checks whether the argment is -m for manual mode{
      printf("Manual mode toggled\n");
      if (argc == 5) {
        printf("File path received\n");
        if (manualMode(argv[2], argv[3], argv[4]) == 0) {
          return 0;
        } else {
          return 1;
        }
      } else if (argc == 11) {
        printf("File path received\n Write path received\n");
        if (manualMode(argv[2], argv[3], argv[4], argv[5], argv[6], argv[7],
                       argv[8], argv[9], argv[10],argv[11]) == 0) {
          return 0;
        } else {
          return 1;
        }
      } else {
        if (manualMode() == 0) {
          return 0;
        } else {
          return 1;
        }
      }
    } else if (strcmp("-g", argv[1]) == 0) {
      char *pEnd;
      printf("gain mode\n");
      if (autoModeGainChange(strtod(argv[2], &pEnd), strtod(argv[3], &pEnd),
                             strtod(argv[4], &pEnd), strtod(argv[5], &pEnd),
                             strtod(argv[6], &pEnd),
                             strtod(argv[7], &pEnd)) == 0) {
        return 0;
      } else {
        return 1;
      }
    } else if (strcmp("-mg", argv[1]) == 0 || strcmp("-gm", argv[1]) == 0) {
      char *pEnd;
      printf("manual gain mode\n");
      if (manualMode(argv[2], argv[3], argv[4], argv[5], argv[6], argv[7],
                     argv[8], argv[9], argv[10], argv[11],strtod(argv[12], &pEnd),
                     strtod(argv[13], &pEnd), strtod(argv[14], &pEnd),
                     strtod(argv[15], &pEnd), strtod(argv[16], &pEnd),
                     strtod(argv[17], &pEnd)) == 0) {
        return 0;
      } else {
        return 1;
      }
    } else {
      printf("Invalid Argument\nOnly Accept (-g gains offsets),(-mg path "
             "logPath gains offsets) , (-m) , (-m dataPath),(-m dataPath "
             "logPath ) \n");
      return 128;
    }
  } else {
    if (autoMode() == 0) {
      return 0;
    } else {
      return 1;
    }
  }
}

// Function just in case the user wish to enter the data path manually
int manualMode() {
  char tempPath[80];
  printf("Please enter the sensor 1 data path\n");
  scanf("%s", tempPath);
  DataPulator1 Stream_1(tempPath);
  printf("Please enter the sensor 2 data path\n");
  scanf("%s", tempPath);
  DataPulator2 Stream_2(tempPath);
  printf("Please enter the sensor 3 data path\n");
  scanf("%s", tempPath);
  DataPulator Stream_3(tempPath);

  printf("Please enter the log point A path\n");
  scanf("%s", tempPath);
  Logger LogA(tempPath);
  printf("Please enter the log point B path\n");
  scanf("%s", tempPath);
  Logger LogB(tempPath);
  printf("Please enter the log point C path\n");
  scanf("%s", tempPath);
  Logger LogC(tempPath);
  printf("Please enter the log point D path\n");
  scanf("%s", tempPath);
  Logger LogD(tempPath);
  printf("Please enter the log point E path\n");
  scanf("%s", tempPath);
  Logger LogE(tempPath);
  printf("Please enter the log point F path\n");
  scanf("%s", tempPath);
  Logger LogF(tempPath);
  printf("Please enter the log point Motor path\n");
  scanf("%s", tempPath);
  Logger LogMotor(tempPath);

  Processing(&Stream_1, &Stream_2, &Stream_3, &LogA, &LogB, &LogC, &LogD, &LogE,
             &LogF,&LogMotor);
  return 0;
}
// Overloading the function to take some arg from command line's argv
int manualMode(char *file_path1, char *file_path2, char *file_path3) {
  DataPulator1 Stream_1(file_path1);
  DataPulator2 Stream_2(file_path2);
  DataPulator Stream_3(file_path3);
  char tempPath[80];
  printf("Please enter the log point A path\n");
  scanf("%s", tempPath);
  Logger LogA(tempPath);
  printf("Please enter the log point B path\n");
  scanf("%s", tempPath);
  Logger LogB(tempPath);
  printf("Please enter the log point C path\n");
  scanf("%s", tempPath);
  Logger LogC(tempPath);
  printf("Please enter the log point D path\n");
  scanf("%s", tempPath);
  Logger LogD(tempPath);
  printf("Please enter the log point E path\n");
  scanf("%s", tempPath);
  Logger LogE(tempPath);
  printf("Please enter the log point F path\n");
  scanf("%s", tempPath);
  Logger LogF(tempPath);
  printf("Please enter the log point Motor path\n");
  scanf("%s", tempPath);
  Logger LogMotor(tempPath);

  Processing(&Stream_1, &Stream_2, &Stream_3, &LogA, &LogB, &LogC, &LogD, &LogE,
             &LogF,&LogMotor);
  return 0;
}
// Overloading the function to take all arg from CLI argv
int manualMode(char *file_path1, char *file_path2, char *file_path3,
               char *log_fileA, char *log_fileB, char *log_fileC,
               char *log_fileD, char *log_fileE, char *log_fileF,char *log_fileMotor) {
  DataPulator1 Stream_1(file_path1);
  DataPulator2 Stream_2(file_path2);
  DataPulator Stream_3(file_path3);
  Logger LogA(log_fileA);
  Logger LogB(log_fileB);
  Logger LogC(log_fileC);
  Logger LogD(log_fileD);
  Logger LogE(log_fileE);
  Logger LogF(log_fileF);
  Logger LogMotor(log_fileMotor);

  Processing(&Stream_1, &Stream_2, &Stream_3, &LogA, &LogB, &LogC, &LogD, &LogE,
             &LogF,&LogMotor);

  return 0;
}
int manualMode(char *file_path1, char *file_path2, char *file_path3,
               char *log_fileA, char *log_fileB, char *log_fileC,
               char *log_fileD, char *log_fileE, char *log_fileF,char* log_fileMotor,
               double gainInput1, double gainInput2, double gainInput3,
               double offsetInput1, double offsetInput2, double offsetInput3) {
  DataPulator1 Stream_1(file_path1);
  DataPulator2 Stream_2(file_path2);
  DataPulator Stream_3(file_path3);
  Logger LogA(log_fileA);
  Logger LogB(log_fileB);
  Logger LogC(log_fileC);
  Logger LogD(log_fileD);
  Logger LogE(log_fileE);
  Logger LogF(log_fileF);
  Logger LogMotor(log_fileMotor);

  Processing(&Stream_1, &Stream_2, &Stream_3, &LogA, &LogB, &LogC, &LogD, &LogE,
             &LogF, &LogMotor ,gainInput1, gainInput2, gainInput3, offsetInput1,
             offsetInput2, offsetInput3);
  return 0;
}

// The default function if no arg is pass in CLI
int autoMode() {
  DataPulator1 Stream_1(filePath1);
  DataPulator2 Stream_2(filePath2);
  DataPulator Stream_3(filePath3);
  Logger LogA(lpAPath);
  Logger LogB(lpBPath);
  Logger LogC(lpCPath);
  Logger LogD(lpDPath);
  Logger LogE(lpEPath);
  Logger LogF(lpFPath);
  Logger LogMotor(lpMotorPath);

  Processing(&Stream_1, &Stream_2, &Stream_3, &LogA, &LogB, &LogC, &LogD, &LogE,
             &LogF,&LogMotor);
  return 0;
}
int autoModeGainChange(double gainInput1, double gainInput2, double gainInput3,
                       double offsetInput1, double offsetInput2,
                       double offsetInput3) {
  DataPulator1 Stream_1(filePath1);
  DataPulator2 Stream_2(filePath2);
  DataPulator Stream_3(filePath3);
  Logger LogA(lpAPath);
  Logger LogB(lpBPath);
  Logger LogC(lpCPath);
  Logger LogD(lpDPath);
  Logger LogE(lpEPath);
  Logger LogF(lpFPath);
  Logger LogMotor(lpMotorPath);

  Processing(&Stream_1, &Stream_2, &Stream_3, &LogA, &LogB, &LogC, &LogD, &LogE,
             &LogF,&LogMotor, gainInput1, gainInput2, gainInput3, offsetInput1,
             offsetInput2, offsetInput3);
  return 0;
}

// due to multiple occurence the manipulation is done in this function such that
// other function could call it
void Processing(DataPulator1 *Stream_1, DataPulator2 *Stream_2,
                DataPulator *Stream_3, Logger *LogA, Logger *LogB, Logger *LogC,
                Logger *LogD, Logger *LogE, Logger *LogF,Logger *LogMotor) {
  double outputStream[2];
  int maxRow;

  LogA->NamingColumns();
  LogB->NamingColumns();
  LogC->NamingColumns();
  LogD->NamingColumns();
  LogE->NamingColumns();
  LogF->NamingColumns();
  LogMotor->NamingColumns("Row", "Motor A", "Motor B");
  Stream_1->getMaxRow();
  Stream_2->getMaxRow();
  Stream_3->getMaxRow();

  Stream_1->setGain(Gain1);
  Stream_2->setGain(Gain2);
  Stream_3->setGain(Gain3);

  Stream_1->setOffset(offset1);
  Stream_2->setOffset(offset2);
  Stream_3->setOffset(offset3);

  maxRow = max(Stream_1->lastRow, Stream_2->lastRow, Stream_3->lastRow);

  printf("\nProcessing... \n\n");
  for (int i = 0; i < maxRow; i++) {
    Stream_1->updateLine();
    Stream_1->reformat();
    Stream_1->preProcess();
    LogA->log(Stream_1->processed_stream);
    Stream_1->correction();
    LogC->log(Stream_1->processed_stream);

    Stream_2->updateLine();
    Stream_2->reformat();
    Stream_2->preProcess();
    LogB->log(Stream_2->processed_stream);
    Stream_2->correction();
    LogD->log(Stream_2->processed_stream);

    Stream_3->updateLine();
    Stream_3->reformat();
    Stream_3->correction();
    LogE->log(Stream_3->processed_stream);
    dataFusion(Stream_1->processed_stream, Stream_2->processed_stream,
               Stream_3->processed_stream, outputStream);
    LogF->log(outputStream);
    LogMotor->motor_log(outputStream);
  }
  printf("Process completed\n\n");
}

void Processing(DataPulator1 *Stream_1, DataPulator2 *Stream_2,
                DataPulator *Stream_3, Logger *LogA, Logger *LogB, Logger *LogC,
                Logger *LogD, Logger *LogE, Logger *LogF, Logger *LogMotor,double gainInput1,
                double gainInput2, double gainInput3, double offsetInput1,
                double offsetInput2, double offsetInput3) {
  double outputStream[2];
  int maxRow;

  LogA->NamingColumns();
  LogB->NamingColumns();
  LogC->NamingColumns();
  LogD->NamingColumns();
  LogE->NamingColumns();
  LogF->NamingColumns();
  LogMotor->NamingColumns("Row", "Motor A", "Motor B");
  Stream_1->getMaxRow();
  Stream_2->getMaxRow();
  Stream_3->getMaxRow();

  Stream_1->setGain(gainInput1);
  Stream_2->setGain(gainInput2);
  Stream_3->setGain(gainInput3);

  Stream_1->setOffset(offsetInput1);
  Stream_2->setOffset(offsetInput2);
  Stream_3->setOffset(offsetInput3);

  maxRow = max(Stream_1->lastRow, Stream_2->lastRow, Stream_3->lastRow);

  printf("\nProcessing... \n\n");
  for (int i = 0; i < maxRow; i++) {
    Stream_1->updateLine();
    Stream_1->reformat();
    Stream_1->preProcess();
    LogA->log(Stream_1->processed_stream);
    Stream_1->correction();
    LogC->log(Stream_1->processed_stream);

    Stream_2->updateLine();
    Stream_2->reformat();
    Stream_2->preProcess();
    LogB->log(Stream_2->processed_stream);
    Stream_2->correction();
    LogD->log(Stream_2->processed_stream);

    Stream_3->updateLine();
    Stream_3->reformat();
    Stream_3->correction();
    LogE->log(Stream_3->processed_stream);
    dataFusion(Stream_1->processed_stream, Stream_2->processed_stream,
               Stream_3->processed_stream, outputStream);
    LogF->log(outputStream);
    LogMotor->motor_log(outputStream);
  }
  printf("Process completed\n\n");
}

void dataFusion(double *stream_1, double *stream_2, double *stream_3,
                double *output_stream) {
  if (stream_1[0] == stream_2[0] && stream_1[0] == stream_3[0]) {
    output_stream[0] = stream_1[0];
    output_stream[1] = 3 * (stream_1[1] - stream_3[1]) / stream_2[1] - 3.;
  }
}

int max(int a, int b) {
  if (a > b) {
    return a;
  } else {
    return b;
  }
}

int max(int a, int b, int c) {
  if (a > b && a > c) {
    return a;
  } else if (b > a && b > c) {
    return b;
  } else {
    return c;
  }
}
