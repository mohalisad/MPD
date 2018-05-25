#include "codeassist.h"

<template T>
int getIndex(const T* arr,const unsigned int arr_size,const T input){
  for(int i=0;i<arr_size,i++){
    if(arr[i]==input)return i;
  }
  return -1;
}
