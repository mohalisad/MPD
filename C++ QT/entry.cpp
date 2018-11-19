#include "entry.h"
#include "strlib.h"
#include "strtoken.h"
#include "exception.h"

#define KEY "entry_key1234"

Cryptor Entry::c;
std::string Entry::userKey;

void Entry::setUserKey(std::string input){
    userKey=input;
}

Entry::Entry(int num,Date *d,std::string t){
    number = num;
    date=d;
    text=t;
    this->mood = PS_NOMOOD;
    state=ES_UNENCRYPTED;
}

Entry::Entry(int num,Date *d,std::string t,PersonState _mood){
    number = num;
    date=d;
    text=t;
    this->mood = _mood;
    state=ES_UNENCRYPTED;
}

Entry::Entry(std::string input){
    state=ES_UNDECRYPTED;
    hash=input;
}

void Entry::encrypt(std::string key){
    hash= c.encrypt(c.encrypt(text,KEY)+" "+date->toString()+" "+intToString(number)+" "+intToString(mood),key);
    state=ES_ENCRYPTED;
}
void Entry::decrypt(){
    StringTokenizer tokens(c.decrypt(hash,userKey)," ");
    if(tokens.size()!=3 && tokens.size()!=4)throw Exception ("Decryption cannot be done");
    text=c.decrypt(tokens[0],KEY);
    date=new Date(tokens[1]);
    number=parseInt(tokens[2]);
    if(tokens.size()==4)
        mood=parseInt(tokens[3]);
    else
        mood=PS_NOMOOD;
    state=ES_DECRYPTED;
}
void Entry::recrypt(std::string newKey) {
    if(state==ES_UNDECRYPTED)decrypt();
    encrypt(newKey);
}
std::string Entry::getHash(){
    if(state==ES_UNENCRYPTED)encrypt();
    return hash;
}
std::string Entry::getText(){
    if(state==ES_UNDECRYPTED)decrypt();
    return text;
}
std::string Entry::getDate(){
    if(state==ES_UNDECRYPTED)decrypt();
    return date->toString();
}
int Entry::getNumber(){
    if(state==ES_UNDECRYPTED)decrypt();
    return number;
}
PersonState Entry::getMood(){
    return mood;
}
void Entry::setText(std::string input){
    text=input;
    state=ES_UNENCRYPTED;
}
void Entry::setDate(std::string input){
    date=new Date(input);
    state=ES_UNENCRYPTED;
}
void Entry::setNumber(int input){
    number=input;
    state=ES_UNENCRYPTED;
}
void Entry::setMood(PersonState _mood){
    this->mood = _mood;
    state=ES_UNENCRYPTED;
}

std::string get_moodstr(int mood){
    switch (mood) {
    case PS_AFSORDE:
        return "افسرده";
    case PS_ASABI:
        return "عصبانی";
    case PS_TAJOB:
        return "متعجب";
    case PS_KHKHOSHAL:
        return "خیلی خوشحال";
    case PS_KHOSHAL:
        return "خوشحال";
    case PS_SADE:
        return "معمولی";
    case PS_NARAHAT:
        return "ناراحت";
    case PS_KHNARAHAT:
        return "خیلی ناراحت";
    }
    return "_";
}
