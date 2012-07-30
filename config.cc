#include "config.hh"

#define gj(a,b) getjval(a,b)
#define gt(a,b) getjt(a,b)

using namespace json;
namespace scrum
{
  string ReadFileToString(const char *filename)
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
  
  //
  // conf::Configuration stuffs
  //

  conf::Sub conf::Configuration::SubFromJsonObj(Object from)
  {
    conf::Sub temp_sub;
    temp_sub.enabled = gj(Boolean, from["enabled"]);
    temp_sub.name = gj(String, from["name"]);
    temp_sub.value = gj(String, from["value"]);
    return temp_sub;
  }
  
  conf::Platform conf::Configuration::PlatformFromJsonObj(Object from)
  {
    conf::Platform temp_platform;
    temp_platform.name = gj(String, from["name"]);
    temp_platform.filename = gj(String, from["file"]);
    temp_platform.available = gj(Boolean, from["eanbled"]);
    return temp_platform;
  }

  void conf::Configuration::PopulateSubs()
  {
    for (int i = 0; i < gt(Array, json_object_["subs"]).Size(); i++)
      {
        Object tempobj = gt(Object, json_object_["subs"][i]);
        subs_.push_back(SubFromJsonObj(tempobj));
      }
  }
  
  void conf::Configuration::PopulatePlatforms()
  {
    for (int i = 0; i < gt(Array,json_object_["config"]["scrumble"]["available"]).Size(); i++ )
      {
        Object tempobj = gt(Object, json_object_["config"]["scrumble"]["available"][i]);
        platforms_.push_back(PlatformFromJsonObj(tempobj));
      }
  }

  void conf::Configuration::ConfigureViaJson(Object rootobj)
  {
    json_object_ = rootobj;
    PopulateSubs();
    PopulatePlatforms();
  }
  
  conf::Platform conf::Configuration::GetPlat(const int index)
  {
    return this->platforms_.at(index);
  }
  

  ScrummyConfigure::ScrummyConfigure()
  {
    json_reader_ = new Reader;
    read_stream_ = new stringstream;
    root_obj_ = new Object;
    read_stream_->str(ReadFileToString("config.json"));
    json_reader_->Read(*root_obj_, *read_stream_);
  }
  
  void ScrummyConfigure::PopulateConf()
  {
    conf_->ConfigureViaJson(*root_obj_);
  }

}
