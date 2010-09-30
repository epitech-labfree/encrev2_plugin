/**********************************************************\

  Auto-generated encrev2_pluginAPI.cpp

\**********************************************************/

#include "BrowserObjectAPI.h"
#include "variant_list.h"
#include "DOM/JSAPI_DOMDocument.h"

#include "encrev2_pluginAPI.h"

encrev2_pluginAPI::encrev2_pluginAPI(FB::BrowserHost host) : m_host(host)
{
    registerMethod("echo",      make_method(this, &encrev2_pluginAPI::echo));
    registerMethod("testEvent", make_method(this, &encrev2_pluginAPI::testEvent));

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

void encrev2_pluginAPI::testEvent(const FB::variant& var)
{
    FireEvent("onfired", FB::variant_list_of(var));
}

