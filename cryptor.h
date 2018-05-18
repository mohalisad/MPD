#ifndef CRYPTOR_H
#define CRYPTOR_H

#include <string>
#include "random.h"

class Cryptor{
private:
  Random r;
  std::string randomString(int length);
  int* makeDisorderMoves(int length,std::string key);
  int* makeDisorderArray(int length,int* disorderMoves);
  int bitSet(int input,int position,bool toWhat);
public:
  Cryptor();
  std::string encrypt(std::string input,std::string key);
};

#endif
