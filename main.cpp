#include <iostream>
#include "cryptor.h"

using namespace std;

int main()
{
  Cryptor c;
  std::string t;
  t=c.encrypt("salam","MrTux:159357");
  std::cout << t << '\n';
  std::cout << c.decrypt(t,"MrTux:15935")<<endl;
}
