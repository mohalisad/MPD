#include "random.h"
#include "strlib.h"
#include "sha256.h"

#define BASE 10
#define LENGTH 8
#define MAX_STATE 100000

Random::Random(std::string input){
    state=0;
    hash=sha256(input);
}
int Random::generate(){
    int ret = 0;
    int arr[LENGTH];
    for (int i=0;i<LENGTH;i++){
        arr[i]=0;
    }
    for (int i=0;i<64;i++){
        arr[i%LENGTH]+=hash[i]%BASE;
    }
    for (int i=0;i<LENGTH;i++){
        ret=ret*BASE+arr[i];
    }
    hash=sha256(hash+intToString(getState())+intToString(ret));
    return ret;
}
int Random::getState(){
    state=(state+1)%MAX_STATE;
    return state;
}
