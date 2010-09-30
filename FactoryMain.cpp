/**********************************************************\

  Auto-generated FactoryMain.cpp

  This file contains the auto-generated factory methods
  for the encrev2_plugin project

\**********************************************************/

#include "FactoryDefinitions.h"
#include "encrev2_plugin.h"

FB::PluginCore *_getMainPlugin()
{
    return new encrev2_plugin();
}

void GlobalPluginInitialize()
{
    encrev2_plugin::StaticInitialize();
}

void GlobalPluginDeinitialize()
{
    encrev2_plugin::StaticDeinitialize();
}
