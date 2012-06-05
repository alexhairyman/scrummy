#include "scrummer.hh"

using namespace std;

#define out(a) std::cout << #a << ": " << a << std::endl;

//~ Everything scrummer
//~ classes,etc

int main(int argc, char* argv[])
{

  scrum::scrumwin s (240,360);
  scrum::drupalauth *d = new scrum::drupalauth();
  s.setdrupalauth(d);
  s.go();
  Fl::run();
  delete(d);
  out("SDF");
  return 0;

}
