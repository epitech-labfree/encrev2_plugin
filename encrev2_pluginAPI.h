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
  bool                  stream();
  bool                  play(const std::string&);
  bool			connect(const std::string&, const std::string&);
  bool			disconnect();
  bool			stop();
  bool			start_plugin();
  bool			setOptions(const std::string& str);

  std::string*		get_runtime_option();
  std::string*		get_startup_option();
  void			set_runtime_option(const std::string& s1);
  void			set_startup_option(const std::string& s1);

 private:
  FB::BrowserHostPtr    m_host;
  encrev2_plugin        &m_plugin;
};

#endif // H_encrev2_pluginAPI
