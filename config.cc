#include "config.hh"

#define gj(a,b) getjval(a,b)
#define gt(a,b) getjt(a,b)

using namespace json;
namespace scrum
{
  string getfilestring(char *filename)
  {
    ifstream * infile = new ifstream;
    infile->open(filename);
    
    string * tempdata = new string;
    
    while (infile->good())
      {
        tempdata->push_back(infile->get());
      }
    *tempdata = tempdata->substr(0, tempdata->size()-1);
    
    delete(infile);
    return *tempdata;
    
  }
  
  scrummyconfigure::scrummyconfigure()
  {
    jread = new json::Reader;
    dstream = new stringstream;
    robj = new json::Object;
    dstream->str(getfilestring("config.json"));
    jread->Read(*robj, *dstream);
    theconf = new configuration;
  }
  
  unsigned short scrummyconfigure::populatesub(Array * subarray)
  {
    Array & ar = *subarray;
    unsigned short totalenabled;
    
    map<string, string> mahmap;
    mahmap["herro"] = "goodbye";
    cout << endl;
    cout << mahmap["herro"] << endl;
    
    
    for (int i = 0; i < ar.Size(); i++)
      {
        char * prefix;
        string tkey = gj(String, ar[i]["name"]);
        string cval = gj(String, ar[i][tkey.c_str()]);
        if (gj(Boolean, ar[i]["enabled"]) == true)
          {
            
            mahmap[tkey] = cval;
            prefix = "enabling :";
            totalenabled++;
          }
        else
          {
            prefix = "not enabling :";
          }
        cout << setw(16) << left << prefix << setw(15) << tkey << " : " << mahmap[tkey] << endl;
      }
    cout << "Attempting to write to submap " << endl;
    theconf->subvars = mahmap;
    return totalenabled;
  }
  
  string scrummyconfigure::dosub(string input)
  {
    
  }

  void scrummyconfigure::populatedata(configuration *topop)
  {
    configuration & tconf = *topop;
    Object j = *robj;
    
    // ready.... set.... GO!
    Array sarray = j["subs"];
    populatesub(&sarray);
    // simple stuff, straight forward
    
    tconf.version = gj(Number, j["config"]["version"]);
    tconf.versionlong = gj(String, j["config"]["versionlong"]);
    tconf.versionstr = gj(String, j["config"]["versionstr"]);
    
    // a little more difficult, this is an object for platforms
    for (int i = 0; i < gt(Array, j["config"]["available"]).Size(); i++)
      {
        Object& tobj = j["config"]["available"][i];
        
        cout << "Platform: " << gj(String, tobj["name"]) << setw(20) << setfill('=') << ""
             << setfill(' ') << endl;
        cout << "enabled :" <<  gj(Boolean, tobj["enabled"]) << endl;
        cout << "url :" << dosub((gj(String, tobj["url"])));
      }
    
    
  }
  
  unsigned short scrummyconfigure::populateconf()
  {
    populatedata(theconf);
  }
}
