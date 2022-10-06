#include "test.h"
#include<iostream>

using namespace std;

test::test(int a){
  cout<< a<< endl;
}

test1::test1(int a): test::test(int a){};