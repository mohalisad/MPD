#ifndef RANDOM_H
#define RANDOM_H

#include <string>
#include "sha256.h"


class Random{
private:
  int state;
  std::string hash;
  int getState();
public:
  Random(std::string input);
  int generate();
};


#endif
