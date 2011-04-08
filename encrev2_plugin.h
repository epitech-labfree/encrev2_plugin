/**********************************************************\

  Auto-generated encrev2_plugin.cpp

  This file contains the auto-generated main plugin object
  implementation for the encrev2_plugin project

\**********************************************************/
#ifndef H_encrev2_pluginPLUGIN
#define H_encrev2_pluginPLUGIN

#include "PluginWindow.h"
#include "PluginEvents/MouseEvents.h"
#include "PluginEvents/AttachedEvent.h"

#include "PluginCore.h"

#include "encre.hh"
#include "Stream.hh"

class encrev2_plugin : public FB::PluginCore
{
 public:
  static void				StaticInitialize();
  static void				StaticDeinitialize();
  encre::Encre<libvlc_instance_t>*	encre();

 public:
  encrev2_plugin();
  virtual ~encrev2_plugin();

 public:
  virtual FB::JSAPIPtr createJSAPI();
  virtual bool IsWindowless() { return false; }

  BEGIN_PLUGIN_EVENT_MAP()
    EVENTTYPE_CASE(FB::MouseDownEvent, onMouseDown, FB::PluginWindow)
    EVENTTYPE_CASE(FB::MouseUpEvent, onMouseUp, FB::PluginWindow)
    EVENTTYPE_CASE(FB::MouseMoveEvent, onMouseMove, FB::PluginWindow)
    EVENTTYPE_CASE(FB::MouseMoveEvent, onMouseMove, FB::PluginWindow)
    EVENTTYPE_CASE(FB::AttachedEvent, onWindowAttached, FB::PluginWindow)
    EVENTTYPE_CASE(FB::DetachedEvent, onWindowDetached, FB::PluginWindow)
  END_PLUGIN_EVENT_MAP()

  /** BEGIN EVENTDEF -- DON'T CHANGE THIS LINE **/
  virtual bool onMouseDown(FB::MouseDownEvent *evt, FB::PluginWindow *);
  virtual bool onMouseUp(FB::MouseUpEvent *evt, FB::PluginWindow *);
  virtual bool onMouseMove(FB::MouseMoveEvent *evt, FB::PluginWindow *);
  virtual bool onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindow *);
  virtual bool onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindow *);
  /** END EVENTDEF -- DON'T CHANGE THIS LINE **/

 protected:
  encre::Encre<libvlc_instance_t>		m_encre;
};

#endif
