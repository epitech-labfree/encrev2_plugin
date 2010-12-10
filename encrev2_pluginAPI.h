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
  // Read-only property ${PROPERTY.ident}
  std::string get_version();

  // Method echo
  FB::variant echo(const FB::variant& msg);

  // Method test-event
  void testEvent(const FB::variant& s);

  /*
   * Encre actual code
   */
  bool                  stream(const std::string &host,
                               const std::string &port);
  bool                  play(const std::string &mrl);
  void			start();
  void			stop();
  void			set_option(const std::string&,
      const std::string&, const std::string&);
  std::string*		get_option();
  void		        reset_option();

 private:
  FB::BrowserHostPtr    m_host;
  encrev2_plugin        &m_plugin;
};

#endif // H_encrev2_pluginAPI
