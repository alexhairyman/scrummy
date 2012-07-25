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

#ifndef __SCRUMCOMPS
#define __SCRUMCOMPS

#include <cstdlib>
#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Radio_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Button.H>
#include <FL/Enumerations.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Secret_Input.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Box.H>

#include <boost/filesystem.hpp>
#include <boost/version.hpp>

#include <string>
#include "drupalauth.hh"
#include "scrummer2.hh"


using namespace std;

namespace scrum
{
  
  class Fl_Light_Output : public Fl_Light_Button
  {
  public:
    Fl_Light_Output(int x, int y, int w, int h);
    void toggle();
    int handle(int event);  
   };
  
  class scrumwin : public Fl_Window
  {
  public:
    scrumwin();
    void setdrupalauth(scrum::drupalauth *d);
    void gatherdat();
    void go();
    versel getversel();
    string geturlstring();
    
  private:
    // gettin' down 'n' dirty!
    drupalauth * myd;
    Fl_Box * mainlbl;
    Fl_Button * do_but;
    Fl_Button * unzip_but;
    Fl_Button * run_but;
    Fl_Secret_Input * password;
    Fl_Input * username;
    Fl_Light_Output * login_stat;
    Fl_Box * status;
    Fl_Button * exit_but;
    
    // little menu for selection
    Fl_Group * versionselect;
    Fl_Radio_Button * rlin32;
    Fl_Radio_Button * rwin32;
    Fl_Radio_Button * rsrc;
    Fl_Radio_Button * rlin64;
    
  public:
#ifdef BOOST_VERSION >= 105000
    boost::filesystem::path scrumbledir;
    boost::filesystem::path scrumblebinary;
#define BIO boost::filesystem
#else
#define BIO boost::filesystem3
    boost::filesystem3::path scrumbledir;
    boost::filesystem3::path scrumblebinary;
#endif
    
    // call backs
    static void login_cb(Fl_Widget * w, void * v);
    static void exit_cb(Fl_Widget * w, void * v);
    static void unzip_cb(Fl_Widget * w, void * v);
    static void run_cb(Fl_Widget * w, void * v);
    
    // drupal stuff
    string _u, _p;
    versel vsl;
  };
}
#endif
