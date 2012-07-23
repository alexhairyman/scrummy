#include <json/reader.h>
#include <json/elements.h>
#include <json/writer.h>

#include <string>
#include <strstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>

using namespace std;

#define glue(a,b) a##b

//#define _getjval(type, prefix, toget)

#define getjt(type, toget) ((json::type) toget)
#define getjval(type, toget) ((json::type) toget).Value()

namespace scrum {
  string getfilestring(char * filename);
  
  class scrummyconfigure
  {
  public:
    scrummyconfigure();
    
    // just assume a get_ prefix to all of these XD
    // all sorts of get_s up the Wazubaba
    
    /* will be something like 0x00150200 0xAABBCCDD
      where AA = major eg "0".15.2 BB = release 0."15".2
      CC = minor 0.15."02" and DD means squat... yup */
    int versionnum();
    string versionstring(bool retlong = false); // "0.15" or "0.15.2"
    bool lin32_available();
    bool lin64_available();
    bool win_available();
    bool mac_available();
    bool src_available();

//  private:
    string dosub(string input); // actually substitutes the strings
    unsigned char populatesub(); // returns number of substitutions
    map<string, string> subrules; // replace with <char*, char*> ?
    json::Reader * jread;
    json::Object * robj;
    stringstream * dstream;
    string *data;
    
  };
}
