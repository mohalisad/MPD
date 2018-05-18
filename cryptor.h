#ifndef CRYPTOR_H
#define CRYPTOR_H

#include <iostream>

#include <string>
#include "random.h"
#include "date.h"
#include "strlib.h"

#define _KEY "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!?"
#define SALT_LENGTH 16
#define MULTIPLY 1.5
#define DISORDER_RATE 5

std::string randomString(int length){
  std::string retu;
  Random r(Date::now());
  for(int i=0;i<length;i++){
    retu+=charToString(_KEY[r.generate()%64]);
  }
  return retu;
}
int* makeDisorderMoves(int length){
  int loopCount=DISORDER_RATE*length*2;
  int *arr=new int[loopCount];
  Random r(Date::now());
  for(int i=0;i<loopCount;i++){
    arr[i]=r.generate()%length;
  }
  return arr;
}
int* makeDisorderArray(int length,int* disorderMoves){
  int c;
  int loopCount=DISORDER_RATE*length*2;
  int* ret=new int[length];
  for(int i=0;i<length;i++){
    ret[i]=i;
  }
  for(int i=0;i<loopCount;i+=2){
    c=ret[disorderMoves[i]];
    ret[disorderMoves[i]]=ret[disorderMoves[i+1]];
    ret[disorderMoves[i+1]]=c;
  }
  return ret;
}
std::string encrypt(std::string input,std::string key){
  int length=MULTIPLY*input.size()*8;
  int *disorderArray;
  disorderArray=makeDisorderArray(length,makeDisorderMoves(length));
  return "";
}
#endif
