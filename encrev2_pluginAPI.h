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

  /*
   * Generated example code
   */
  // Read/Write property ${PROPERTY.ident}
  std::string get_testString();
  void set_testString(const std::string& val);

  // Read-only property ${PROPERTY.ident}
  std::string get_version();

  // Method echo
  FB::variant echo(const FB::variant& msg);

  // Method test-event
  void testEvent(const FB::variant& s);

  /*
   * Encre actual code
   */
  void                  stream(const std::string &host,
                               const std::string &port);
  void                  play(const std::string &mrl);
  void			set_option(const std::string&,
	    const std::string&,const std::string&);
	void            stop();

 private:
  FB::BrowserHostPtr    m_host;
  encrev2_plugin        &m_plugin;

  std::string           m_testString;
};

#endif // H_encrev2_pluginAPI
