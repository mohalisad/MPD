#ifndef ENTRY_H
#define ENTRY_H

#include <string>
#include "date.h"
#include "cryptor.h"

enum EntryState{ES_UNDECRYPTED,ES_DECRYPTED,ES_ENCRYPTED,ES_UNENCRYPTED};

class Entry{
private:
  static Cryptor c;
  static std::string userKey;
  int number;
  Date *date;
  std::string text;
  std::string hash;
  EntryState state;
  void encrypt(std::string key=userKey);
  void decrypt();
public:
  static void setUserKey(std::string input);
  Entry(int num,Date *d,std::string t);
  Entry(std::string input);
  void recrypt(std::string newKey);
  std::string getHash();
  std::string getText();
  std::string getDate();
  int getNumber();
  void setText(std::string input);
  void setDate(std::string input);
  void setNumber(int input);
};

#endif
