#include "entry.h"
#include "cryptor.h"
#include "strlib.h"

#define KEY "entry_key"

Entry::Entry(int num,Date *d,std::string t){
  number = num;
  date=d;
  text=t;
}

Entry::Entry(std::string input){
  Cryptor c;
  date=new Date(getTag(input,"date"));
  number=parseInt(getTag(input,"count"));
  text=c.decrypt(getTag(input,"text"),KEY);
}

std::string Entry::toString(){
  Cryptor c;
  return "<count>"+intToString(number)+"</count><date>"+date->toString()+"</date><text>"+c.encrypt(text,KEY)+"</text>";
}
