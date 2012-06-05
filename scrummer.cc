/*
            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                    Version 2, December 2004

 Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.
*/
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
