#ifndef CRYPTOR_H
#define CRYPTOR_H

#include <string>
#include "random.h"

class Cryptor{
private:
  Random r;
  std::string randomString(const int& length);
  static int* makeDisorderMoves(const int& length,const std::string& key);
  static int* makeDisorderArray(const int& length,const int* disorderMoves);
  static int bitSet(const char& input,const int& position,const bool& toWhat);
  static bool bitGet(const char& input,const int& position);
  static int getPossition(const char& input);
public:
  Cryptor();
  std::string encrypt(std::string input,std::string key);
  std::string decrypt(std::string input,std::string key);
};

#endif
