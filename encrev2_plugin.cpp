/**********************************************************\

  Auto-generated encrev2_plugin.cpp

  This file contains the auto-generated main plugin object
  implementation for the encrev2_plugin project

\**********************************************************/

#include <iostream>

#include "NpapiTypes.h"
#include "encrev2_pluginAPI.h"
#include "encrev2_plugin.h"
#include "PluginWindow.h"
#include "EncreLog.hpp"

using namespace std;

void            encrev2_plugin::StaticInitialize()
{
  EncreLog() << "encrev2_plugin::StaticInitialize()";
  // Place one-time initialization stuff here; note that there isn't an absolute guarantee that
  // this will only execute once per process, just a guarantee that it won't execute again until
  // after StaticDeinitialize is called
}

void            encrev2_plugin::StaticDeinitialize()
{
  EncreLog() << "encrev2_plugin::StaticDeinitialize()";
  // Place one-time deinitialization stuff here
}


encrev2_plugin::encrev2_plugin()
{
}

encrev2_plugin::~encrev2_plugin()
{
}

FB::JSAPIPtr    encrev2_plugin::createJSAPI()
{
  // m_host is the BrowserHostWrapper
  return FB::JSAPIPtr(new encrev2_pluginAPI(m_host, *this));
}

bool            encrev2_plugin::onMouseDown(FB::MouseDownEvent *evt,
                                            FB::PluginWindow *)
{
  //printf("Mouse down at: %d, %d\n", evt->m_x, evt->m_y);
  return false;
}

bool            encrev2_plugin::onMouseUp(FB::MouseUpEvent *evt,
                                          FB::PluginWindow *)
{
  //printf("Mouse up at: %d, %d\n", evt->m_x, evt->m_y);
  return false;
}

bool            encrev2_plugin::onMouseMove(FB::MouseMoveEvent *evt,
                                            FB::PluginWindow *)
{
  //printf("Mouse move at: %d, %d\n", evt->m_x, evt->m_y);
  return false;
}
bool            encrev2_plugin::onWindowAttached(FB::AttachedEvent *evt,
                                                 FB::PluginWindow *w)
{
  m_encre.set_window(w);
  return false;
}

bool            encrev2_plugin::onWindowDetached(FB::DetachedEvent *evt,
                                                 FB::PluginWindow *w)
{
  m_encre.set_window(0);
  return false;
}

encre::Encre<libvlc_instance_t>*		encrev2_plugin::encre()
{
  return &m_encre;
}
