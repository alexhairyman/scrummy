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
#pragma once
#ifndef __SCRUMMER2
#define __SCRUMMER2

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_ask.H>
#include "string"
using namespace std;

namespace scrum
{
  void FLalertbox(const char *alert);
  
  enum versel
  {
    WIN32=0,
    LIN32=1,
    LIN64=2,
    SRC=3
    
  };
  typedef const string propstr;
  
  propstr _win32 = "http://dynamic.scrumbleship.com/system/files/ScrumbleShip-0.15-win-full.zip";
//  propstr _lin32 = "http://dynamic.scrumbleship.com/system/files/ScrumbleShip-0.15-lin32-full.zip";
  propstr _lin32 = "http://127.0.0.1/ScrumbleShip-0.15.2-lin32-full.zip";
  propstr _lin64 = "http://dynamic.scrumbleship.com/system/files/ScrumbleShip-0.15-lin64-full.zip";
  propstr _src = "http://dynamic.scrumbleship.com/system/files/ScrumbleShip-0.15.0-source.zip";
  
  propstr _win32_name = "ScrumbleShip-0.15-win-full.zip";
  propstr _lin32_name = "ScrumbleShip-0.15.2-lin32-full.zip";
  propstr _lin64_name = "ScrumbleShip-0.15-lin64-full.zip";
  propstr _src_name = "ScrumbleShip-0.15.0-source.zip";
}

#endif
