#include <iostream>
#include "entry.h"
#include "cryptor.h"

using namespace std;

int main()
{
  Cryptor c;
  Entry e(5,new Date(1397,2,1),"salam man emrooz movafagh shodam in proje ra be saranjam jalebi bersanam va mitavanam begooyam");
  std::cout << c.encrypt(e.toString(),"12345") << '\n';
}
//GOCKtiPWFo4Ypk9MtGa8c7usChTD4BgLNLGVUoQzDVa3TSBzKnUOS0iP8gbuXATRgWr0YTGAdvlVZ2MTMiomEeXSmdpDMg10Z4uGNY6QU0dslLlUfL7gJAWTijVCMB8SxrhgzSXiynCB0gikIaH1qckPggjacCC?yc5GClEvZnXnC2biSL7ZUn46JSvqiDqMbnYJKedDixXgz00F40Tvvm4joMj!1mmnMTom2oJ!rhixjoNNC47kTNDyMOOzkopciCC?!sw8c8K?ugRPNwxCoownoP8kBkEFwJ!pole9EdG4RX4!U0gpbK4BgD0Btgu2CmNivxWmPg14wpYo8Ztnx!oIkBHTlBfJFKY?QW0cYA2a?czcyi!ckqPb7WaIAYfQEDrwFmlmz1y5l4tLTT1kr9mRl6EnnLlwYDYAP5W7cMQEOoS9Is4pJFfGGtSq5YF2V4pbI0E?5VGnWCa8n7RcE3jIoPXIRY6lKQ!PbfFRk3dpKLEgmFZY0ZYEe1gy6W?okGiLWYcoPGeWKek
