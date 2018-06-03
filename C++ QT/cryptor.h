#ifndef CRYPTOR_H
#define CRYPTOR_H

#include <string>
#include "random.h"

class Cryptor{
private:
  Random r;
  std::string randomString(int length);
  static int* makeDisorderMoves(int length,std::string key);
  static int* makeDisorderArray(int length,int* disorderMoves);
  static int bitSet(int input,int position,bool toWhat);
  static bool bitGet(int input,int position);
  static int getPossition(char input);
public:
  Cryptor();
  std::string encrypt(std::string input,std::string key);
  std::string decrypt(std::string input,std::string key);
};

#endif
