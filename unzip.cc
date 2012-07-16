#include "unzip.hh"

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

#ifdef S_TEST
int main()
#endif
