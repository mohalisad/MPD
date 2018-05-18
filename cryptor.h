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
int* makeDisorderMoves(int length,std::string key){
  int loopCount=DISORDER_RATE*length*2;
  int *arr=new int[loopCount];
  Random r(key);
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
int bitSet(int input,int position,bool toWhat){
  int pow2=1;
  for(int i=0;i<position;i++)pow2*=2;
  if((input&pow2)==toWhat)return input;
  if(toWhat){
    return  input|pow2;
  }else{
    return input&(63-pow2);
  }
}
std::string encrypt(std::string input,std::string key){
  std::string retu;
  int length=MULTIPLY*input.size()*8;
  length=length+6-length%6;
  int *disorderArray,*disorderMoves,*chars;
  std::string salt=randomString(SALT_LENGTH);
  disorderMoves=makeDisorderMoves(length,key+salt);
  disorderArray=makeDisorderArray(length,disorderMoves);
  chars=new int[length/6];
  for(int i=0;i<length/6;i++){
    chars[i]=0;
  }
  int pointer=0;
  for(unsigned i=0;i<input.size();i++){
    for(int j=1;j<256;j=j*2){
      chars[disorderArray[pointer]/6]=bitSet(chars[disorderArray[pointer]/6],disorderArray[pointer]%6,input[i]&j);
      pointer++;
    }
  }
  Random r(Date::now());
  for(;pointer<length;pointer++){
    chars[disorderArray[pointer]/6]=bitSet(chars[disorderArray[pointer]/6],disorderArray[pointer]%6,r.generate()%2);
  }
  for(int i=0;i<length/6;i++){
    retu+=_KEY[chars[i]];
  }
  delete disorderArray;
  delete disorderMoves;
  return retu+salt;
}
#endif
