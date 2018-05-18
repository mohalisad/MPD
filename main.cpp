#include <iostream>
#include "random.h"

using namespace std;

int main(int argc, char *argv[])
{
    string input;
    cin>>input;
    Random r(input);
    int t[6];
    for(int i=0;i<6;i++){
      t[i]=0;
    }
    for(int i=0;i<10000;i++){
      t[r.generate()%6]++;
    }
    for(int i=0;i<6;i++){
      cout<<t[i]<<endl;
    }
}
