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
namespace scrum
{
  //~ Fl light output stuff
  //~ 
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
  
  scrumwin::scrumwin(int w=240, int h=360) : Fl_Window(w,h, "scrummer")
  {
    begin();
    
    mainlbl = new Fl_Box(10, 10, 220, 25, "scrummer");
    mainlbl->box(FL_OVAL_BOX);
    
    login_but = new Fl_Button(10, 305, 220, 25, "&login");
    login_but->callback(login_cb, this);
    
    login_stat = new Fl_Light_Output(10, 270, 220, 25);
    username = new Fl_Input(10,40,220,25);
    password = new Fl_Secret_Input(10,70,220,25);
    
    versionselect = new Fl_Group(10, 100, 220, 200);
    versionselect->begin();
    
    rwin32 = new Fl_Radio_Button(10,100,200,20,"windows 32 bit version");
    rsrc = new Fl_Radio_Button(10,130,200,20,"Source Code!");
    rlin64 = new Fl_Radio_Button(10,160,200,20,"Linux 64 bit version");
    rlin32 = new Fl_Radio_Button(10,190,200,20,"Linux 32 bit version");
    
    versionselect->end();
    end();
    show();
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
  
  void scrumwin::login_cb(Fl_Widget *w, void *v)
  {
    scrumwin* vv = (scrumwin*) v;
    vv->gatherdat();
    vv->myd->login(vv->_u,vv->_p);
    if(vv->myd->isauthed() == true)
    {
      vv->login_stat->toggle();
      vv->label("downloading");
      
      if(vv->rlin32->value() == 1)
      {
        vv->myd->seturl(_lin32);
      }
      else if (vv->rwin32->value() == 1)
      {
        vv->myd->seturl(_win32);
      }
      else if (vv->rlin64->value() == 1)
      {
        vv->myd->seturl(_lin64);
      }
      else if (vv->rsrc->value() == 1)
      {
        vv->myd->seturl(_src);
      }
      vv->myd->download();
      
    }
    
  }
  
  void scrumwin::go()
  {
    Fl::run();
    
  }
}
