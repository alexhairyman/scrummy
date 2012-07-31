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
  
  void conf::Platform::CopyFrom(Platform from)
  {
    this->available = from.available;
    this->filename = from.filename;
    this->name = from.name;
    this->available = from.available;
    this->platformint = from.platformint;
    this->url = from.url;
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
    temp_sub.empty = false;
    return temp_sub;
  }
  
  conf::Platform conf::Configuration::PlatformFromJsonObj(Object from)
  {
    conf::Platform temp_platform;
    temp_platform.name = gj(String, from["name"]);
    temp_platform.filename = ConfigureString(gj(String, from["file"]));
    temp_platform.available = gj(Boolean, from["enabled"]);
    temp_platform.platformint = gj(Number, from["platformint"]);
    string tempurl;
    tempurl.append(base_url_);
    tempurl.append(temp_platform.filename);
    temp_platform.url = tempurl;
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

  void conf::Configuration::ConfigureViaJson(json::Object rootobj)
  {
    json_object_ = gt(Object, rootobj);
    base_url_ = gj(String, json_object_["config"]["scrumble"]["base"]);
    PopulateSubs();
    PopulatePlatforms();
  }
  
  conf::Sub conf::Configuration::GetSubFromKey(string key)
  {
    
    for (int i = 0; i < subs_.size(); i++)
      {
        if (subs_[i].name == key)
          return subs_.at(i);
      }
    conf::Sub emptysub;
    emptysub.empty = true;
    return emptysub;
  }

  conf::Platform conf::Configuration::GetPlat(const int plat_enum)
  {
    for (int i = 0; i < platforms_.size(); i++)
      {
        conf::Platform tempplat = platforms_.at(i);
        if (tempplat.platformint == plat_enum)
          return tempplat;
      }
  }
  
  string conf::Configuration::ConfigureString(string input)
  {
    unsigned int current_pos = 0;
    unsigned int end_pos = 0;
    unsigned int begin_pos = 0;
    string input_copy = input;
    string tempstring;
    while (input.find('$',current_pos) != input_copy.npos)
      {
        unsigned int offset = 0;
        begin_pos = input_copy.find('$', current_pos);
        end_pos = input_copy.find('}', begin_pos+1);
        offset = end_pos - begin_pos - 2;
        tempstring = input_copy.substr(begin_pos+2,offset);
        if (GetSubFromKey(tempstring).empty != true)
          {
            input_copy.erase(begin_pos, offset+3);
            input_copy.insert(begin_pos, GetSubFromKey(tempstring).value);
          }
        current_pos = end_pos;
      }
    cout << input_copy << endl;
    return input_copy;
  }
  

  //
  // ScrummyConfigure stuff
  //
  
  ScrummyConfigure::ScrummyConfigure()
  {
    read_stream_.str(ReadFileToString("config.json"));
    json_reader_.Read(root_obj_, read_stream_);
  }
  
  conf::Platform ScrummyConfigure::GetPlat(int plat_enum)
  {
    return conf_->GetPlat(plat_enum);
  }
  
  void ScrummyConfigure::PopulateConf()
  {
    Object l = root_obj_;
    conf_ = new conf::Configuration;
    conf_->ConfigureViaJson(l);
  }

}
