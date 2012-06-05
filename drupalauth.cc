/*
Copyright (c) 2011 Henrik Cooke, henrik@cooke.se

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
#include <drupalauth.hh>

#define out(a) cout << #a << ": " << a << '\n'; cout.flush()
namespace scrum
{
  drupalauth::drupalauth() : ofs(&ofsb), ckout(&cookieout), complaintbox(&devinnull)
  {    
    of = "of.txt";
    cookiedir = boost::filesystem3::path("_drupalauth");
    boost::filesystem3::create_directory(cookiedir);
    cookief /= cookiedir;
    cookief /= "drupalcookie.txt";
    
    ofsb.open(of.native());
    cookieout.open(cookief.native());
    devinnull.open(boost::iostreams::null_sink());
    
//    ofs->rdbuf(&ofsb);
//    ckout->rdbuf(&cookieout);
  }
  
  void drupalauth::login(string user, string password)
  {
    
    
//    ofs->rdbuf(&ofsb);
//    ckout->rdbuf(&cookieout);
  
    ec.setOpt(new curlpp::options::Url("http://dynamic.scrumbleship.com/user/login"));
    //~ ec.setOpt(new curlpp::options::Url("127.0.1.1/drupal7/?q=user/login"));
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
    cout << "poop";
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
    
    //ec.reset();
//    dc.setOpt(new curlpp::options::CookieJar("cookie.txt"));
    dc.setOpt(new curlpp::options::CookieFile(cookief.native()));
    dc.setOpt(new curlpp::options::WriteStream(&ofs));
    dc.setOpt(new curlpp::options::Url(_URL));
    dc.setOpt(new curlpp::options::HttpGet(true));
    dc.perform();

  }
  
  drupalauth::~drupalauth()
  {
    out("die man");
    
  }
}
