#include "unzip.hh"
#include <boost/version.hpp>

#ifdef OLD_USE_POCO
bool ScrumbleUnzip::unzip(string file)
{
  ifstream *infile = new ifstream();
//  infile->open(scrum::drupalauth::getstringoffile(scrum::drupalauth::getversel()));
  cout << file.c_str() << endl;
  infile->open(file.c_str());
  
  dezip = new Poco::Zip::Decompress (*infile, *(new Poco::Path("Scrumble")));
  dezip->decompressAllFiles();
  
  return true;
}
#endif
#define MSBG

#ifdef MSBG
#define IDBG(XxX) XxX 
#else
#define IDBG(XxX)
#endif

#if BOOST_VERSION >= 105000
#define BFS boost::filesystem
#else
#define BFS boost::filesystem3
#endif

#define BIO boost::iostreams

bool ScrumbleUnzip::unzip(string file)
{
  return this->Unzip(file);
  
}
bool ScrumbleUnzip::Unzip(string file)
{
  bool rbool = false;
  try
    {
      this->archive_ = archive_read_new();
      archive_read_support_format_zip(this->archive_);
      if(BFS::exists(file))
        {
          archive_read_open_filename(this->archive_, file.c_str(), 8);
          
          while(archive_read_next_header(this->archive_, &this->archive_entry_) == ARCHIVE_OK)
            {
              BFS::path p = file;
              BFS::path pe = archive_entry_pathname(this->archive_entry_);

              IDBG(cout << pe.string() << endl;);
              IDBG(cout << pe.parent_path().string() << endl;);
              IDBG(cout << BFS::exists(pe.parent_path()) << endl;);

              if(BFS::exists(pe.parent_path()) == false)
                 BFS::create_directories(pe.parent_path());
              BIO::stream<BIO::file_sink> ofil (archive_entry_pathname(this->archive_entry_));

              long numread;
              do
                {
                  char* buf = new char[(8 * 1024 * 1024)];
                  numread = archive_read_data(this->archive_, buf, (8 * 1024 * 1024));
                  if(numread != 0) // we still have more to go!
                    {
                      ofil << buf; 
                      ofil.flush();
                    }
                  delete[] buf;
                }
              while(numread != 0); // what to do about the if ^ there
                  
            }
        }
      else
        std::cout << "archive does not exist" << std::endl;
    }
  catch(int e)
    {
      archive_read_free(this->archive_);
    }
  return rbool;
}

#ifdef S_TEST
int main()
#endif
