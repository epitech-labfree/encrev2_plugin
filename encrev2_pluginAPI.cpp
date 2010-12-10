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
  registerMethod("echo",      make_method(this, &encrev2_pluginAPI::echo));
  registerMethod("testEvent", make_method(this, &encrev2_pluginAPI::testEvent));
  registerMethod("stream",    make_method(this, &encrev2_pluginAPI::stream));
  registerMethod("play",      make_method(this, &encrev2_pluginAPI::play));
  registerMethod("stop",      make_method(this, &encrev2_pluginAPI::stop));
  registerMethod("start",      make_method(this, &encrev2_pluginAPI::start));
  registerMethod("set_option",      make_method(this, &encrev2_pluginAPI::set_option));
  registerMethod("get_option",      make_method(this, &encrev2_pluginAPI::get_option));

  // Read-write property
  registerProperty("testString",
                   make_property(this,
                                 &encrev2_pluginAPI::get_testString,
                                 &encrev2_pluginAPI::set_testString));

  // Read-only property
  registerProperty("version",
                   make_property(this,
                                 &encrev2_pluginAPI::get_version));


  registerEvent("onfired");
}

encrev2_pluginAPI::~encrev2_pluginAPI()
{
}

// Read/Write property testString
std::string encrev2_pluginAPI::get_testString()
{
  return m_testString;
}
void encrev2_pluginAPI::set_testString(const std::string& val)
{
  m_testString = val;
}

// Read-only property version
std::string encrev2_pluginAPI::get_version()
{
  return "CURRENT_VERSION";
}

// Method echo
FB::variant encrev2_pluginAPI::echo(const FB::variant& msg)
{
  return msg;
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

bool            encrev2_pluginAPI::play(const std::string &mrl)
{
	return m_plugin.vlc().play(mrl);
}

void            encrev2_pluginAPI::stop()
{
  m_plugin.vlc().stop();
}

void            encrev2_pluginAPI::start()
{
  m_plugin.vlc().start();
}

void
encrev2_pluginAPI::set_option(const std::string& s1,
    const std::string&s2, const std::string&s3)
{
	m_plugin.vlc().set_option(s1,s2,s3);
}

std::string*
encrev2_pluginAPI::get_option() {
	m_plugin.vlc().get_option();
}
