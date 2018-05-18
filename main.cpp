#include <iostream>
#include "date.h"

using namespace std;

int main()
{
  int y;
  cin>>y;
  Date d(y,1,1);
  std::cout << d.dayOfWeek << '\n';
}
