/**********************************************************\

  Auto-generated encrev2_pluginAPI.cpp

\**********************************************************/

#include "iostream"
#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"

#include "encrev2_pluginAPI.h"
#include "encrev2_plugin.h"

encrev2_pluginAPI::encrev2_pluginAPI(FB::BrowserHostPtr host, encrev2_plugin &plugin)
  : m_host(host), m_plugin(plugin)
{
  registerMethod("testEvent", make_method(this, &encrev2_pluginAPI::testEvent));
  registerMethod("stream",    make_method(this, &encrev2_pluginAPI::stream));
  registerMethod("play",      make_method(this, &encrev2_pluginAPI::play));
  registerMethod("stop",      make_method(this, &encrev2_pluginAPI::stop));
  registerMethod("connect",      make_method(this, &encrev2_pluginAPI::connect));
  registerMethod("disconnect",      make_method(this, &encrev2_pluginAPI::disconnect));
  registerMethod("set_option",      make_method(this, &encrev2_pluginAPI::set_option));
  // registerMethod("get_option",      make_method(this, &encrev2_pluginAPI::get_option));

  // Read-only property
  registerProperty("version",
                   make_property(this,
                                 &encrev2_pluginAPI::get_version));


  registerEvent("onfired");
}

encrev2_pluginAPI::~encrev2_pluginAPI()
{
}

// Read-only property version
std::string encrev2_pluginAPI::get_version()
{
  return "CURRENT_VERSION";
}

void            encrev2_pluginAPI::testEvent(const FB::variant& var)
{
  FireEvent("onfired", FB::variant_list_of(var));
}

bool            encrev2_pluginAPI::stream(const std::string &host,
                                          const std::string &port)
{
	return m_plugin.vlc().stream(host, port);
}

bool            encrev2_pluginAPI::play()
{
	return m_plugin.vlc().play();
}

void            encrev2_pluginAPI::stop()
{
  m_plugin.vlc().stop();
}

void
encrev2_pluginAPI::set_option(const char* s1)
{
	m_plugin.vlc().addOption(s1);
}

#include <iostream>
void
encrev2_pluginAPI::connect(const std::string& host, const std::string& port) {
	m_plugin.vlc().connect(host, port);
}

void
encrev2_pluginAPI::disconnect() {
	m_plugin.vlc().disconnect();
}

//std::string*
//encrev2_pluginAPI::get_option() {
//	m_plugin.vlc().get_option();
//}

