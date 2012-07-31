/*
Copyright (c) 2012 Alex Herrmann alexhairyman@gmail.com

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "drupalauth.hh"

#define out(a) cout << #a << ": " << a << '\n'; cout.flush()
namespace scrum
{
//  int nullsink::overflow(int c)
//  {
//    return c;
//    sbumpc();
//  }
  
  size_t null_write_callback(char * dat, size_t sizeofo, size_t count, void* f)
  {
    return count;
  }
  
  void DrupalAuth::SetVersion(int V)
  {
    cout << V << endl;
    selected_version_ = V;
  }
  
  int DrupalAuth::GetSelectedVersion()
  {
    return selected_version_;
  }

  string DrupalAuth::GetStringOfFile(int plat)
  {
    try
    {
      string tempstring;
      conf::Platform tempplat;
      if (plat == WIN32)
        tempplat = this->configuration_.GetPlat(WIN32);
      else if (plat == LIN32)
        tempplat = this->configuration_.GetPlat(LIN32);
      else if (plat == LIN64)
        tempplat = this->configuration_.GetPlat(LIN64);
      else if (plat == SRC)
        tempplat = this->configuration_.GetPlat(SRC);
      else
        throw 7;
      
      tempstring = tempplat.filename;
      cout << tempstring.size() << endl;
      return tempstring;
    }
    catch(int e)
    {
      switch(e)
        {
        case 7:
          FLalertbox("No platform selected");
//          cout << "no platform selected" << endl;
//          terminate();
//          exit(99);
          break;
        }
    }
  }
  
  string DrupalAuth::GetStringOfUrl(int plat)
  {
    try
    {
      if(plat == WIN32)
        return configuration_.GetPlat(WIN32).url;
      else if(plat == LIN32)
        return configuration_.GetPlat(LIN32).url;
      else if(plat == LIN64)
        return configuration_.GetPlat(LIN64).url;
      else if(plat == SRC)
        return configuration_.GetPlat(SRC).url;
      else
        throw 7;
    }
    catch (int e)
    {
      cout << "something went wrong" << endl;
      terminate();
      exit(99);
    }
  }
    
  DrupalAuth::DrupalAuth()
  {
    configuration_.PopulateConf();
    
#if BOOST_VERSION >= 105000
    cookiedir = boost::filesystem::path("_drupalauth");
#else
    cookiedir = boost::filesystem3::path("_drupalauth");
#endif
    boost::filesystem::create_directory(cookiedir);
    cookief /= cookiedir;
    cookief /= "drupalcookie.txt";

    cookie_out_ = new ofstream;
    cookie_out_->open(cookief.native().c_str());
  }
  
  void DrupalAuth::Login(string user, string password)
  {
    login_cp_.setOpt(new curlpp::options::Url("http://dynamic.scrumbleship.com/user/login"));
    login_cp_.setOpt(new curlpp::options::Post(true));
    login_cp_.setOpt(new curlpp::options::FollowLocation(true));
    login_cp_.setOpt(new curlpp::options::CookieJar(cookief.native()));
    login_cp_.setOpt(new curlpp::options::CookieFile(cookief.native()));
//    ec.setOpt(new curlpp::options::WriteStream(complaintbox));
    login_cp_.setOpt(new curlpp::OptionTrait<void*, CURLOPT_WRITEDATA>(0));
    login_cp_.setOpt(new curlpp::options::WriteFunctionCurlFunction(null_write_callback));
    posts.push_back(new curlpp::FormParts::Content("name",user));
    posts.push_back(new curlpp::FormParts::Content("pass",password));
    posts.push_back(new curlpp::FormParts::Content("form_id","user_login"));
    login_cp_.setOpt(new curlpp::options::HttpPost(posts));
    login_cp_.perform();
    cout << "poop\n";
    cout.flush();
    list<string> cooks = curlpp::infos::CookieList::get(login_cp_);
    if (cooks.size() != 0)
    {
      for(list<string>::iterator it = cooks.begin(); it != cooks.end(); it++)
      {
        cout << *it << endl;
        *cookie_out_ << *it;
        cookie_out_->flush();
      }
      is_authed_ = true;
    }
    else
      is_authed_ = false;
   
  }
  
  void DrupalAuth::SetUrl(string setto)
  {
    url_ = setto;
  }
  
  bool DrupalAuth::is_authed()
  {
    return is_authed_;
  }
  
  bool DrupalAuth::has_downloaded()
  {
    return has_downloaded_;
  }
  
  void DrupalAuth::Download()
  {
//    ofsb.open(of.native());
    download_stream_ = new ofstream;
#if BOOST_VERSION >= 105000
    cout << boost::filesystem::current_path() << endl;
#else
    cout << boost::filesystem3::current_path() << endl;
#endif
    
    cout << GetStringOfFile(GetSelectedVersion()) << endl;
    cout << GetStringOfUrl(GetSelectedVersion()) << endl;
    
#if BOOST_VERSION >= 105000
    of = boost::filesystem::path(GetStringOfFile(GetSelectedVersion()));
#else
    of = boost::filesystem3::path(getstringoffile(getversel()));
#endif
    download_stream_->open(of.native().c_str());
    SetUrl(GetStringOfUrl(GetSelectedVersion()));
    download_cp_.setOpt(new curlpp::options::CookieFile(cookief.native().c_str()));
    download_cp_.setOpt(new curlpp::options::WriteStream(download_stream_));
    download_cp_.setOpt(new curlpp::options::Url(url_));
    download_cp_.setOpt(new curlpp::options::HttpGet(true));
    download_cp_.perform();
    download_stream_->flush();
    has_downloaded_=true;
//    ofs->close();
  }
  
  DrupalAuth::~DrupalAuth()
  {
    out("die man");
    
  }
}
