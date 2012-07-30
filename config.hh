#include <json/reader.h>
#include <json/elements.h>
#include <json/writer.h>

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
    };
    
    struct Platform
    {
      string name;
      string filename;
      bool available;
      int platformint;
      
//      string CompleteUrl(string base); // Do I need this
    };
    
    class Configuration
    {
    public:
//      Platform& operator[] (const int platformint);
//      Platform& operator[] (const char* index);
      string ConfigureString(string input);
      Platform GetPlat(const int index);
      void ConfigureViaJson(json::Object rootobj);
      
    private:
      void PopulateSubs();
      void PopulatePlatforms();
      Sub SubFromJsonObj(json::Object from);
      Platform PlatformFromJsonObj(json::Object from);

      
      json::Object json_object_;
      vector<Platform> platforms_;
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
    
    bool Linux64Available();
    string Linux64Url();
    
    bool WindowsAvailable();
    string WindowsUrl();
    
    bool MacAvailable();
    string MacUrl;
    
    bool SourceAvailable();
    string SourceUrl();
    
    void PopulateConf(); // populates the configuration

  private:
    json::Reader * json_reader_;
    json::Object * root_obj_;
    stringstream * read_stream_;
    conf::Configuration * conf_;
    
  };
}
