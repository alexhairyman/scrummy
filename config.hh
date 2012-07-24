#include <json/reader.h>
#include <json/elements.h>
#include <json/writer.h>

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <scrummer2.hh>

using namespace std;

#define glue(a,b) a##b
#define getjt(type, toget) ((json::type) toget)
#define getjval(type, toget) ((json::type) toget).Value()

namespace scrum {

  struct configuration
  {
    // vars that map to values in json
    map<string, string> subvars; // [subs]
    map<string, bool> available_plats; // [config][scrumble][available]
    map<string, string> urls; // [config][scrumble][urls]
    string versionstr; // [config][versionstr]
    string versionlong; // [config][versionlong]
    int version; // [config][version]
    
    json::Object getconf(); // get the root object for saving
  };

  string getfilestring(char * filename);
  class scrummyconfigure
  {
  public:
    scrummyconfigure();
    
    /* will be something like 0x00150200 0xAABBCCDD
      where AA = major eg "0".15.2 BB = release 0."15".2
      CC = minor 0.15."02" and DD means squat... yup */
    int get_versionnum();
    string get_versionstring(bool retlong = false); // "0.15" or "0.15.2"
    bool get_lin32_available();
    bool get_lin64_available();
    bool get_win_available();
    bool get_mac_available();
    bool get_src_available();
    unsigned short populateconf(); // populates the configuration

  private:
    void populatedata(configuration * topop);
    string dosub(string input); // actually substitutes the strings
    unsigned short populatesub(json::Array *subarray);
    configuration * theconf;
    
    json::Reader * jread;
    json::Object * robj;
    stringstream * dstream;
    
  };
}
