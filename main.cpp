#include <iostream>
#include "entry.h"
#include "cryptor.h"

using namespace std;

int main()
{
  Cryptor c;
  Entry e(4,new Date(1397,4,4),"salam in asdl sajl  asdj  aslk asdjlsaj s ajl js al asjlk ajl sjla sjl aksj lkasj l ajlkd jaklsdj lajdklasjdlk jsldakj lkaj lkasjd lkaj \n sadsdasda");
  std::cout << c.encrypt(e.toString(),"12345") << '\n';
}
