#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "Datapulator.h"


void autoMode();
void manualMode();



int main(int argc , char** argv){
    if (argc >1){
        if(strcmp(argv[1],"-m")==0){
            manualMode();
            return 0;
        }else{
            printf("Error\n");
            return 1;
        }
    }
    autoMode();
    return 0;
}

void autoMode(){
    Datapulator Stream_1;
    Stream_1.getData('1');
}

void manualMode(){

}