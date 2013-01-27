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
    
    
    main_label_ = new Fl_Box(10, 10, 220, 25, "scrummer");
    main_label_->box(FL_OVAL_BOX);
    
    do_but_ = new Fl_Button(10, 305, 220, 25, "&login");
    do_but_->callback(Login_CB, this);
    
    unzip_but_ = new Fl_Button(10, 335, 220, 25, "&unzip");
    unzip_but_->callback(Unzip_CB, this);
    
    login_stat_ = new Fl_Light_Output(10, 270, 220, 25);
    
    exit_but_ = new Fl_Button(10, 365, 50, 25, "&exit");
    exit_but_->callback(Exit_CB, this);
    
    run_but_ = new Fl_Button(70, 365, 50, 25, "&run!");
    run_but_->callback(Run_CB, this);
    
    username_input_ = new Fl_Input(10,40,220,25);
    password_input_ = new Fl_Secret_Input(10,70,220,25);
    
    version_group_ = new Fl_Group(10, 100, 220, 200);
    version_group_->begin();
    
    win_radio_ = new Fl_Radio_Button(20,100,200,20,"windows 32 bit version");
    src_radio_ = new Fl_Radio_Button(20,130,200,20,"Source Code!");
    lin64_radio_ = new Fl_Radio_Button(20,160,200,20,"Linux 64 bit version");
    lin32_radio_ = new Fl_Radio_Button(20,190,200,20,"Linux 32 bit version");

    
    version_group_->end();
    end();
    show();
  }
  
  void scrumwin::Exit_CB(Fl_Widget *w, void *v)
  {
    scrumwin* vv = (scrumwin *) v;
    vv->hide();
    exit(0);
  }
    
  void scrumwin::gatherdat()
  {
    username_ = username_input_->value();
    password_ = password_input_->value();
    
  }
  
  void scrumwin::setdrupalauth(DrupalAuth *d)
  {
    this_drupalauth_ = d;
  }
 
  void scrumwin::Run_CB(Fl_Widget *w, void *v)
  {
    scrumwin * vv = (scrumwin *) v;
#warning nothing here yet boys!
  }
  
  void scrumwin::Unzip_CB( Fl_Widget *w, void *v)
  {
    scrumwin * vv= (scrumwin *) v;
    ScrumbleUnzip *suck = new ScrumbleUnzip;
    suck->unzip(vv->this_drupalauth_->GetStringOfFile(vv->this_drupalauth_->GetSelectedVersion()));
  }

  void scrumwin::Login_CB(Fl_Widget *w, void *v)
  {
    scrumwin* vv = (scrumwin*) v;
    vv->gatherdat();
    vv->this_drupalauth_->Login(vv->username_,vv->password_);
    
    try
      {
      if(vv->this_drupalauth_->is_authed() == true)
        {
          vv->login_stat_->toggle();
          vv->label("downloading");
          
          if(vv->lin32_radio_->value() == 1) {
              vv->this_drupalauth_->SetVersion(scrum::LIN32);
              cout << "lin32" << endl;
            }
          else if (vv->win_radio_->value() == 1) {
              vv->this_drupalauth_->SetVersion(scrum::WIN32);
              cout << "win32" << endl;
            }
          else if (vv->lin64_radio_->value() == 1) {
              vv->this_drupalauth_->SetVersion(scrum::LIN64);
              cout << "lin64" << endl;
            }
          else if (vv->src_radio_->value() == 1) {
              vv->this_drupalauth_->SetVersion(scrum::SRC);
              cout << "src" << endl;
            }
          else { 
              throw 8;
            }
          vv->this_drupalauth_->Download();
          if (vv->this_drupalauth_->has_downloaded() == true)
            {
              vv->unzip_but_->activate();
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
          FLalertbox("Nothing selected");
          break;
        case 9:
          FLalertbox("Not Authed - could mean invalid login information");
          break;
        }
    }
  }
  
  void scrumwin::go()
  {
    Fl::run();
    
  }
}
