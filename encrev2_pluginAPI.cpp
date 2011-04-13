/**********************************************************\

  Auto-generated encrev2_pluginAPI.cpp

\**********************************************************/

#include <iostream>
#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"

#include "encrev2_pluginAPI.h"
#include "encrev2_plugin.h"
#include "encre.hh"
#include "Stream.hh"

encrev2_pluginAPI::encrev2_pluginAPI(FB::BrowserHostPtr host, encrev2_plugin &plugin)
  : m_host(host), m_plugin(plugin)
{
  // Callable
  registerMethod("testEvent", make_method(this, &encrev2_pluginAPI::testEvent));
  registerMethod("stream",    make_method(this, &encrev2_pluginAPI::stream));
  registerMethod("play",      make_method(this, &encrev2_pluginAPI::play));
  registerMethod("stop",      make_method(this, &encrev2_pluginAPI::stop));
  registerMethod("setOptions",make_method(this, &encrev2_pluginAPI::setOptions));
  
  // Read-only property
  registerProperty("version",
                   make_property(this,
                                 &encrev2_pluginAPI::get_version));

  // Read-Write property
  registerProperty("hostname", make_property(this,
  			  &encrev2_pluginAPI::get_hostname,
			  &encrev2_pluginAPI::set_hostname));
  registerProperty("port", make_property(this,
  			  &encrev2_pluginAPI::get_port,
			  &encrev2_pluginAPI::set_port));

  // Event
  registerEvent("onfired");
}

encrev2_pluginAPI::~encrev2_pluginAPI() {}

// Read-only property
std::string encrev2_pluginAPI::get_version()
{
	return "CURRENT_VERSION";
}

// Event
void            encrev2_pluginAPI::testEvent(const FB::variant& var)
{
	FireEvent("onfired", FB::variant_list_of(var));
}

// Callable
bool            encrev2_pluginAPI::stream()
{
	encre::Stream* streamer = m_plugin.encre()->getStream(encre::STREAM);
	if (streamer != 0)
	  return streamer->start();
	else
	  return false;
}

bool            encrev2_pluginAPI::setOptions(const std::string& str, int todo)
{
	encre::e_action e = (encre::e_action)todo;
	encre::Stream* stream = m_plugin.encre()->getStream(e);
	return stream->setOptions(str);
}

bool            encrev2_pluginAPI::play(const std::string& str)
{
	encre::Stream* streamer = m_plugin.encre()->getStream(encre::DISPLAY);
	if (streamer != 0)
	  return streamer->start();
	else
	  return false;
}

bool		encrev2_pluginAPI::stop()
{
	return m_plugin.encre()->getStream()->stop();
}

// Read-Write property
void	encrev2_pluginAPI::set_hostname(const std::string& host)
{
	delete m_plugin.encre()->m_host;
	m_plugin.encre()->m_host = new std::string(host);
}

void	encrev2_pluginAPI::set_port(const short port)
{
	m_plugin.encre()->m_port = port;
}

const std::string& encrev2_pluginAPI::get_hostname()
{
	return *(m_plugin.encre()->m_host);
}

short	encrev2_pluginAPI::get_port()
{
	return m_plugin.encre()->m_port;	
}
