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
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>
#include <curlpp/Form.hpp>


#include <boost/filesystem.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/device/null.hpp>

#include <string>
// Just some static stuffs

using namespace std;
//using namespace boost;

namespace scrum
{
  class drupalauth
  {
  public:
    drupalauth();
    ~drupalauth();
    
    void download();
    void login(string user, string pass);
    bool isauthed();
    void seturl(string setto);
    
  // protected:
  
  private:
    string _URL;
    curlpp::Forms sdd;
    boost::iostreams::stream_buffer<boost::iostreams::file_sink> ofsb;
    boost::iostreams::stream_buffer<boost::iostreams::file_sink> cookieout;
    boost::iostreams::stream_buffer<boost::iostreams::null_sink> devinnull;
    
    ofstream mofs;
    
    iostream ofs;
    iostream ckout;
    iostream complaintbox;
    
    curlpp::Easy ec, dc;
    string s;
    bool _authed;
    boost::filesystem3::path cookiedir;
    boost::filesystem3::path cookief;
    boost::filesystem3::path of;
    curlpp::Forms posts;
    
  };
}
