#include <Poco/Zip/ZipArchive.h>
#include <Poco/Zip/Decompress.h>
#include <Poco/Path.h>
#include <iostream>
#include <fstream>
#include "scrummer2.hh"
#include "drupalauth.hh"
#include <string>

#ifndef __SCRUMZIP
#define __SCRUMZIP

using namespace std;

class ScrumbleUnzip
{
public:
  bool unzip(string file);
  
private:
  Poco::Path zipfile;
  Poco::Zip::Decompress *dezip;  
};

#endif
