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

#ifndef __DRUPALAUTH
#define __DRUPALAUTH

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>
#include <curlpp/Form.hpp>


#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>

#include "config.hh"
#include "scrummer2.hh"

#include <string>
// Just some static stuffs

using namespace std;
using namespace boost;

size_t null_write_callback(char * dat, size_t sizeofo, size_t count, void* f);

namespace scrum
{
  class DrupalAuth
  {
  public:
    DrupalAuth();
    ~DrupalAuth();
    
    void Download();
    void Login(string user, string pass);
    bool is_authed();
    bool has_downloaded();
    void SetUrl(string setto);
    void SetVersion(int V);
    int GetSelectedVersion();
    
    string GetStringOfFile(int plat);
    string GetStringOfUrl(int plat);
    
  private:
    bool has_downloaded_;
    int selected_version_;
    string url_;
    ofstream * download_stream_;
    ofstream * cookie_out_;
    ostream * complaint_box_;
    curlpp::Easy login_cp_, download_cp_;
    bool is_authed_;
    ScrummyConfigure configuration_;
    
// I should move this up top, oh well
#include <boost/version.hpp>
#if BOOST_VERSION >= 105000
    boost::filesystem::path cookiedir;
    boost::filesystem::path cookief;
    boost::filesystem::path of;
#else
    boost::filesystem3::path cookiedir;
    boost::filesystem3::path cookief;
    boost::filesystem3::path of;
#endif
    
    curlpp::Forms posts;
    
  };
}
#endif
