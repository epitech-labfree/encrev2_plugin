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
  registerMethod("start",     make_method(this, &encrev2_pluginAPI::start_plugin));
  registerMethod("stream",    make_method(this, &encrev2_pluginAPI::stream));
  registerMethod("play",      make_method(this, &encrev2_pluginAPI::play));
  registerMethod("stop",      make_method(this, &encrev2_pluginAPI::stop));
  registerMethod("connect",   make_method(this, &encrev2_pluginAPI::connect));
  registerMethod("disconnect",make_method(this, &encrev2_pluginAPI::disconnect));
  
  // Read-only property
  registerProperty("version",
                   make_property(this,
                                 &encrev2_pluginAPI::get_version));

  // Read-Write property
  registerProperty("startUpOption", make_property(this,
			  &encrev2_pluginAPI::get_startup_option,
			  &encrev2_pluginAPI::set_startup_option));
  registerProperty("runtimeOption", make_property(this,
			  &encrev2_pluginAPI::get_runtime_option,
			  &encrev2_pluginAPI::set_runtime_option));

  // Event
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

bool            encrev2_pluginAPI::start_plugin()
{
	return m_plugin.encre().start();
}

bool            encrev2_pluginAPI::stream()
{
	//return m_plugin.encre().getStream()->stream();
	return (false);
}

bool            encrev2_pluginAPI::play(const std::string& str)
{
	//return m_plugin.encre().getStream()->play(str);
	return (false);
}

bool		encrev2_pluginAPI::stop()
{
	return m_plugin.encre().getStream()->stop();
}

void    encrev2_pluginAPI::set_runtime_option(const std::string& s1)
{
	//if (m_plugin.encre().good())
	m_plugin.encre().getStream()->setOptions(s1.c_str());
}

void    encrev2_pluginAPI::set_startup_option(const std::string& s1)
{
	m_plugin.encre().getStream()->setOptions(s1.c_str());
}

// These two getters are provide for Firebreath. Don't use them.
std::string*
encrev2_pluginAPI::get_runtime_option()
{
	return 0;
}

std::string*
encrev2_pluginAPI::get_startup_option()
{
	return 0;
}

bool
encrev2_pluginAPI::connect(const std::string& host, const std::string& port)
{
	// return m_plugin.encre().getStream().connect();
}

bool
encrev2_pluginAPI::disconnect() {
	// return m_plugin.encre().getStream().disconnect();
}

