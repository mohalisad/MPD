#ifndef ENTRY_H
#define ENTRY_H

#include <string>
#include "date.h"
#include "cryptor.h"

enum EntryState{ES_UNDECRYPTED,ES_DECRYPTED,ES_ENCRYPTED,ES_UNENCRYPTED};
typedef int PersonState;
#define PS_AFSORDE   0
#define PS_ASABI     1
#define PS_TAJOB     2
#define PS_KHKHOSHAL 3
#define PS_KHOSHAL   4
#define PS_SADE      5
#define PS_NARAHAT   6
#define PS_KHNARAHAT 7
#define PS_NOMOOD    8

class Entry{
private:
  static Cryptor c;
  static std::string userKey;
  int number;
  Date *date;
  std::string text;
  std::string hash;
  EntryState state;
  PersonState mood;
  void encrypt(std::string key=userKey);
  void decrypt();
public:
  static void setUserKey(std::string input);
  Entry(int num,Date *d,std::string t);
  Entry(int num,Date *d,std::string t,PersonState mood);
  Entry(std::string input);
  void recrypt(std::string newKey);
  std::string getHash();
  std::string getText();
  std::string getDate();
  PersonState getMood();
  int getNumber();
  void setText(std::string input);
  void setDate(std::string input);
  void setNumber(int input);
  void setMood(PersonState mood);
};

std::string get_moodstr(int mood);

#endif
