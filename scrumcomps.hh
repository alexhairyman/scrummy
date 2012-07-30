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
#include <Poco/Foundation.h>

#include <string>
#include "drupalauth.hh"
#include "scrummer2.hh"
#include "unzip.hh"

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
    drupalauth * this_drupalauth_;
    Fl_Box * main_label_;
    Fl_Button * do_but_;
    Fl_Button * unzip_but_;
    Fl_Button * run_but_;
    Fl_Secret_Input * password_input_;
    Fl_Input * username_input_;
    Fl_Light_Output * login_stat_;
    Fl_Box * status_;
    Fl_Button * exit_but_;
    
    // little menu for selection
    Fl_Group * version_group_;
    Fl_Radio_Button * lin32_radio_;
    Fl_Radio_Button * win_radio_;
    Fl_Radio_Button * src_radio_;
    Fl_Radio_Button * lin64_radio_;
    
  public:
#if BOOST_VERSION >= 105000
    boost::filesystem::path scrumbledir;
    boost::filesystem::path scrumblebinary;
#define BIO boost::filesystem
#else
#define BIO boost::filesystem3
    boost::filesystem3::path scrumbledir;
    boost::filesystem3::path scrumblebinary;
#endif
    
    // call backs
    static void Login_CB(Fl_Widget * w, void * v);
    static void Exit_CB(Fl_Widget * w, void * v);
    static void Unzip_CB(Fl_Widget * w, void * v);
    static void Run_CB(Fl_Widget * w, void * v);
    
    // drupal stuff
    string username_, password_;
    versel vsl;
  };
}
#endif
