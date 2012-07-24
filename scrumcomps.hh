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

#include <string>
#include "drupalauth.hh"
#include "scrummer2.hh"
#include "unzip.hh"

using namespace std;

namespace scrum
{
//  typedef const string propstr;
  
//  propstr _win32 = "http://dynamic.scrumbleship.com/system/files/ScrumbleShip-0.14-win-full.zip";
//  propstr _lin32 = "http://dynamic.scrumbleship.com/system/files/ScrumbleShip-0.14-lin32-full.zip";
//  propstr _lin64 = "http://dynamic.scrumbleship.com/system/files/ScrumbleShip-0.14-lin64-full.zip";
//  propstr _src = "http://dynamic.scrumbleship.com/system/files/ScrumbleShip-0.14.1-source.zip";
  
//  propstr _win32_name = "ScrumbleShip-0.14-win-full.zip";
//  propstr _lin32_name = "ScrumbleShip-0.14-lin32-full.zip";
//  propstr _lin64_name = "ScrumbleShip-0.14-lin64-full.zip";
//  propstr _src_name = "ScrumbleShip-0.14.1-source.zip";
  
//  enum versel
//  {
//    WIN32,
//    LIN32,
//    LIN64,
//    SRC
    
//  } _VERSEL;

  
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
    drupalauth* myd;
    Fl_Box* mainlbl;
    Fl_Button* do_but;
    Fl_Button* unzip_but;
    Fl_Secret_Input* password;
    Fl_Input* username;
    Fl_Light_Output* login_stat;
    Fl_Box* status;
    Fl_Button* exit_but;
    
    // little menu for selection
    Fl_Group* versionselect;
    Fl_Radio_Button* rlin32;
    Fl_Radio_Button* rwin32;
    Fl_Radio_Button* rsrc;
    Fl_Radio_Button* rlin64;
    
    // call backs
    static void login_cb(Fl_Widget* w, void* v);
    static void exit_cb(Fl_Widget* w, void* v);
    static void unzip_cb(Fl_Widget* w, void* v);
    
    // drupal stuff
    string _u, _p;
    versel vsl;
  };
}
#endif
