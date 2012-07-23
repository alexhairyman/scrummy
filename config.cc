#include "config.hh"

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
  }

  unsigned char scrummyconfigure::populatesub()
  {
    json::Object jref = *robj;
    for (int i = 0; i < getjt(Array,jref["substitutions"]).Size(); i++)
      {
        cout << "name :" << getjval(String, jref["substitutions"][i]["name"]) << endl;
        cout << "enabled :" << getjval(Boolean, jref["substitutions"][i]["enabled"]) << endl;
      }
  }
}
