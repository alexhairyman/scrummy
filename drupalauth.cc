/*
            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                    Version 2, December 2004

 Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.
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
    dc.setOpt(new curlpp::options::Url("http://dynamic.scrumbleship.com/system/files/ScrumbleShip-0.14-lin32-full_0.zip"));
    dc.setOpt(new curlpp::options::HttpGet(true));
    dc.perform();

  }
  
  drupalauth::~drupalauth()
  {
    out("die man");
    
  }
}
