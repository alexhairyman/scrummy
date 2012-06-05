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

//~ Just some static stuffs

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
    
  //~ protected:
  
  private:
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
