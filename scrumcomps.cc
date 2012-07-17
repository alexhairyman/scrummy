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

#include "scrumcomps.hh"
#include "unzip.hh"

namespace scrum
{
  // Fl light output stuff
  // 
  Fl_Light_Output::Fl_Light_Output(int x, int y, int w, int h) : Fl_Light_Button(x,y,w,h,"logged in?")
  {
    
  }
  
  int Fl_Light_Output::handle(int event)
  {
    if (event == FL_PUSH || event == FL_RELEASE)
      {
        return 0;
      }
    else
      return Fl_Light_Button::handle(event);
  }
  
  void Fl_Light_Output::toggle()
  {
    if (value() == 0)
      value(1);
    else
      value(0);
  }
  
  // scrumwin stuff
  
  scrumwin::scrumwin() : Fl_Window(240,410, "scrummer")
  {
    begin();
    
    
    mainlbl = new Fl_Box(10, 10, 220, 25, "scrummer");
    mainlbl->box(FL_OVAL_BOX);
    
    do_but = new Fl_Button(10, 305, 220, 25, "&login");
    do_but->callback(login_cb, this);
    
    unzip_but = new Fl_Button(10, 335, 220, 25, "&unzip");
    unzip_but->callback(unzip_cb, this);
    unzip_but->deactivate();
    
    login_stat = new Fl_Light_Output(10, 270, 220, 25);
    
    exit_but = new Fl_Button(10, 365, 50, 25, "&exit");
    exit_but->callback(exit_cb, this);
    
    username = new Fl_Input(10,40,220,25);
    password = new Fl_Secret_Input(10,70,220,25);
    
    versionselect = new Fl_Group(10, 100, 220, 200);
    versionselect->begin();
    
    rwin32 = new Fl_Radio_Button(20,100,200,20,"windows 32 bit version");
    rsrc = new Fl_Radio_Button(20,130,200,20,"Source Code!");
    rlin64 = new Fl_Radio_Button(20,160,200,20,"Linux 64 bit version");
    rlin32 = new Fl_Radio_Button(20,190,200,20,"Linux 32 bit version");
    
    rlin32->deactivate();
    
    versionselect->end();
    end();
    show();
  }
  
  void scrumwin::exit_cb(Fl_Widget *w, void *v)
  {
    scrumwin* vv = (scrumwin *) v;
    exit(0);
  }
    
  void scrumwin::gatherdat()
  {
    _u = username->value();
    _p = password->value();
    
  }
  
  void scrumwin::setdrupalauth(drupalauth *d)
  {
    myd = d;
  }
  
  void scrumwin::unzip_cb( Fl_Widget *w, void *v)
  {
    scrumwin * vv= (scrumwin *) v;
    ScrumbleUnzip *suck = new ScrumbleUnzip;
    suck->unzip(vv->myd->getstringoffile(vv->myd->getversel()));
  }

  void scrumwin::login_cb(Fl_Widget *w, void *v)
  {
    scrumwin* vv = (scrumwin*) v;
    vv->gatherdat();
    vv->myd->login(vv->_u,vv->_p);
    
    try{
      if(vv->myd->isauthed() == true)
        {
          vv->login_stat->toggle();
          vv->label("downloading");
          
          if(vv->rlin32->value() == 1) {
              vv->myd->setv(scrum::LIN32);
              cout << "lin32" << endl;
            }
          else if (vv->rwin32->value() == 1) {
              vv->myd->setv(scrum::WIN32);
              cout << "win32" << endl;
            }
          else if (vv->rlin64->value() == 1) {
              vv->myd->setv(scrum::LIN64);
              cout << "lin64" << endl;
            }
          else if (vv->rsrc->value() == 1) {
              vv->myd->setv(scrum::SRC);
              cout << "src" << endl;
            }
          else { 
              throw 8;
            }
          vv->myd->download();
          if (vv->myd->hasdownloaded == true)
            {
              vv->unzip_but->activate();
            }
          
        }
      else
        {
          throw 9;
        }
    }
    catch (int e)
    {
      switch (e)
        {
        case 8:
//          cout << "nothing selected" << endl;
//          terminate();
//          exit(99);
          FLalertbox("Nothing selected");
          break;
        case 9:
          FLalertbox("Not Authed - could mean invalid login information");
//          cout << "not authed" << endl;
//          terminate();
//          exit (99);
          break;
        }
    }
  }
  
  void scrumwin::go()
  {
    Fl::run();
    
  }
}
