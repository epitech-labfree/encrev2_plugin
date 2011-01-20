/**********************************************************\

  Auto-generated encrev2_pluginAPI.h

\**********************************************************/

#include <string>
#include <sstream>
#include "JSAPIAuto.h"
#include "BrowserHostWrapper.h"

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
  bool                  stream(const std::string &host,
                               const std::string &port);
  bool                  play();
  void			connect();
  void			stop();
  void			set_option(const char*);
  //std::string*		get_option();

 private:
  FB::BrowserHostPtr    m_host;
  encrev2_plugin        &m_plugin;
};

#endif // H_encrev2_pluginAPI
