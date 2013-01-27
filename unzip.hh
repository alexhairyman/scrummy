
#warning "POCO BEING PHASED OUT, switching to libarchive"
#ifdef OLD_USE_POCO
#include <Poco/Zip/ZipArchive.h>
#include <Poco/Zip/Decompress.h>
#include <Poco/Path.h>
#endif

// new libarchive includes

#include <archive.h>
#include <archive_entry.h>

#include <boost/filesystem.hpp> 
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/file.hpp>

#include <iostream>
#include <fstream>

#include <string>


#ifndef __SCRUMZIP
#define __SCRUMZIP

using namespace std;

#ifdef OLD_USE_POCO
class ScrumbleUnzip
{
public:
  bool unzip(string file);
  
private:
  Poco::Path zipfile;
  Poco::Zip::Decompress *dezip;  
};
#endif

class ScrumbleUnzip
{
public:
  bool Unzip(string file);
  bool unzip(string file); // provided for compatibity

private:
  struct archive* archive_;
  struct archive_entry* archive_entry_;

};

#endif
