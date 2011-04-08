/**********************************************************\

  Auto-generated encrev2_pluginAPI.h

\**********************************************************/

#include <string>
#include <sstream>
#include "JSAPIAuto.h"
#include "BrowserHostWrapper.h"
#include "encre.hh"

#ifndef H_encrev2_pluginAPI
#define H_encrev2_pluginAPI

class encrev2_plugin;

class encrev2_pluginAPI : public FB::JSAPIAuto
{
 public:
  encrev2_pluginAPI(FB::BrowserHostPtr host, encrev2_plugin &core);
  virtual ~encrev2_pluginAPI();

  // Read-only property ${PROPERTY.ident}
  std::string get_version();
  // Method test-event
  void testEvent(const FB::variant& s);

  // Encre actual code
  bool                  stream();
  bool                  play(const std::string&);
  bool			stop();
  bool			setOptions(const std::string&, int);

  void			set_hostname(const std::string&);
  const std::string&	get_hostname();
  void			set_port(const short);
  short			get_port();

 private:
  FB::BrowserHostPtr    m_host;
  encrev2_plugin        &m_plugin;
};

#endif // H_encrev2_pluginAPI
