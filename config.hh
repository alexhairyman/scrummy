#ifndef __CONFIG
#define __CONFIG

#include "cajun/reader.h"
#include "cajun/elements.h"
#include "cajun/writer.h"

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <scrummer2.hh>

using namespace std;

#define glue(a,b) a##b
#define getjt(type, toget) ((json::type) toget)
#define getjval(type, toget) ((json::type) toget).Value()

namespace scrum 
{

  namespace conf
  {
    struct Sub // damnit it's too hard to write substitutions out all the time!
    {
      string name;
      string value;
      bool enabled;
      bool empty;
    };
    
    struct Platform
    {
      string name;
      string filename;
      bool available;
      int platformint;
      string url; //hrmmmm I shoud probably figure this out 
      void CopyFrom(Platform from);
    };
    
    class Configuration
    {
    public:
      conf::Configuration& operator()(int plat_enum);
      string ConfigureString(string input);
      Platform GetPlat(const int plat_enum);
      Sub GetSubFromKey(string key);
      void ConfigureViaJson(json::Object rootobj);
      
    private:
      
      friend class Platform;
      void PopulateSubs();
      void PopulatePlatforms();
      Sub SubFromJsonObj(json::Object from);
      Platform PlatformFromJsonObj(json::Object from);
      
      json::Object json_object_;
      vector<Platform> platforms_;
      string base_url_;
      vector<Sub> subs_;
      int version_;
      string version_string_;
    };
  }


  string ReadFileToString(const char *filename);
  class ScrummyConfigure
  {
  public:
    ScrummyConfigure();
    
    /* will be something like 0x00150200 0xAABBCCDD
      where AA = major eg "0".15.2 BB = release 0."15".2
      CC = minor 0.15."02" and DD means squat... yup */
    int GetVersion();
    string get_versionstring(bool retlong = false); // "0.15" or "0.15.2"
    
    bool Linux32Available();
    string Linux32Url();
    string Linux32FileName();
    
    bool Linux64Available();
    string Linux64Url();
    string Linux64FileName();
    
    bool WindowsAvailable();
    string WindowsUrl();
    string WindowsFileName();
    
    bool MacAvailable();
    string MacUrl();
    string MacFileName();
    
    bool SourceAvailable();
    string SourceUrl();
    string SourceFileName();

    bool GetStorePassword(); // if the user wants their password stored or not
    string GetUser();
    string GetPassword(); // will return an empty string if store_password is no good
    
    void PopulateConf(); // populates the configuration
    
    conf::Platform GetPlat(int plat_enum);

  private:
    json::Reader json_reader_;
    json::Object root_obj_;
    stringstream read_stream_;
    conf::Configuration * conf_;
    
  };
}
#endif
