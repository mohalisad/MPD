#include "entry.h"
#include "cryptor.h"
#include "strlib.h"
#include "strtoken.h"

#define KEY "entry_key1234"

Entry::Entry(int num,Date *d,std::string t){
  number = num;
  date=d;
  text=t;
}

Entry::Entry(std::string input){
  Cryptor c;
  StringTokenizer tokens(input," ");
  number=parseInt(tokens[0]);
  date=new Date(tokens[1]);
  text=c.decrypt(tokens[2],KEY);
}

std::string Entry::toString(){
  Cryptor c;
  return intToString(number)+" "+date->toString()+" "+c.encrypt(text,KEY);
}
