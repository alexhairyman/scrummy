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
#include "exception"

#define out(a) cout << #a << ": " << a << '\n'; cout.flush()
namespace scrum
{
  
  void drupalauth::setv(int V)
  {
    cout << V << endl;
    _V = V;
  }
  
  int drupalauth::getversel()
  {
    return _V;
  }

  string drupalauth::getstringoffile(int plat)
  {
    try
    {
      if (plat == WIN32)
        return _win32_name;
      else if (plat == LIN32)
        return _lin32_name;
      else if (plat == LIN64)
        return _lin64_name;
      else if (plat == SRC)
        return _src_name;
      else
        throw 7;
    }
    catch(int e)
    {
      switch(e)
        {
        case 7:
          cout << "no platform selected" << endl;
          terminate();
          exit(99);
          break;
        }
    }
  }
  
  string drupalauth::getstringofurl(int plat)
  {
    try
    {
      if(plat == WIN32)
        return _win32;
      else if(plat == LIN32)
        return _lin32;
      else if(plat == LIN64)
        return _lin64;
      else if(plat == SRC)
        return _src;
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
    
  drupalauth::drupalauth() : ofs(&ofsb), ckout(&cookieout), complaintbox(&devinnull)
  {
#if BOOST_VERSION >= 105000
    cookiedir = boost::filesystem::path("_drupalauth");
#else
    cookiedir = boost::filesystem3::path("_drupalauth");
#endif
    boost::filesystem::create_directory(cookiedir);
    cookief /= cookiedir;
    cookief /= "drupalcookie.txt";

    cookieout.open(cookief.native());
    devinnull.open(boost::iostreams::null_sink());

//    ckout.open(cookief.native());
//    complaintbox.open(boost::iostreams::null_sink());
    
//    ofs->rdbuf(&ofsb);
//    ckout->rdbuf(&cookieout);
  }
  
  void drupalauth::login(string user, string password)
  {
    ofs.rdbuf(&ofsb);
    ckout.rdbuf(&cookieout);
  
    ec.setOpt(new curlpp::options::Url("http://dynamic.scrumbleship.com/user/login"));
    // ec.setOpt(new curlpp::options::Url("127.0.1.1/drupal7/?q=user/login"));
    ec.setOpt(new curlpp::options::Post(true));
    ec.setOpt(new curlpp::options::FollowLocation(true));
    ec.setOpt(new curlpp::options::CookieJar(cookief.native()));
//    ec.setOpt(new curlpp::options::CookieJar("cookie.txt"));
    ec.setOpt(new curlpp::options::CookieFile(cookief.native()));
//    ec.setOpt(new curlpp::options::CookieFile("cookie.txt"));
    ec.setOpt(new curlpp::options::WriteStream(&complaintbox));
    posts.push_back(new curlpp::FormParts::Content("name",user));
    posts.push_back(new curlpp::FormParts::Content("pass",password));
    posts.push_back(new curlpp::FormParts::Content("form_id","user_login"));
    ec.setOpt(new curlpp::options::HttpPost(posts));
    
    list<string> mahcookies;
    
    ec.perform();
    cout << "poop\n";
    cout.flush();
    list<string> cooks = curlpp::infos::CookieList::get(ec);
    if (cooks.size() != 0)
    {
      for(list<string>::iterator it = cooks.begin(); it != cooks.end(); it++)
      {
        ckout << *it;
        ckout.flush();
      }
      _authed = true;
    }
    else
      _authed = false;
   
  }
  
  void drupalauth::seturl(string setto)
  {
    _URL = setto;
  }
  
  bool drupalauth::isauthed()
  {
    return _authed;
  }
  
  void drupalauth::download()
  {
//    ofsb.open(of.native());
#if BOOST_VERSION >= 105000
    cout << boost::filesystem::current_path() << endl;
#else
    cout << boost::filesystem3::current_path() << endl;
#endif
    
    cout << getstringoffile(getversel()) << endl;
    cout << getstringofurl(getversel()) << endl;
    
#if BOOST_VERSION >= 105000
    of = boost::filesystem::path(getstringoffile(getversel()));
#else
    of = boost::filesystem3::path(getstringoffile(getversel()));
#endif
    
    ofsb.open(of.native());
    seturl(getstringofurl(getversel()));
//    ec.reset();
//    dc.setOpt(new curlpp::options::CookieJar("cookie.txt"));
    dc.setOpt(new curlpp::options::CookieFile(cookief.native()));
    dc.setOpt(new curlpp::options::WriteStream(&ofs));
    dc.setOpt(new curlpp::options::Url(_URL));
    dc.setOpt(new curlpp::options::HttpGet(true));
//    ofs << "hello world" << endl;
    cout << "hrmmm, doesn't appear to be flushing correctly" << endl;
    dc.perform();
    ofs.flush();
//    ofs->close();
  }
  
  drupalauth::~drupalauth()
  {
    out("die man");
    
  }
}
