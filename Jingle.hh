#ifndef   	JINGLE_HH_
# define   	JINGLE_HH_

#include <time.h>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <vector>
#include "talk/base/ssladapter.h"
#include "talk/base/logging.h"
#include "talk/base/flags.h"
#include "talk/base/pathutils.h"
#include "talk/base/stream.h"
#include "talk/base/win32socketserver.h"
#include "talk/p2p/base/constants.h"
#include "talk/xmpp/xmppclientsettings.h"
#include "talk/p2p/base/constants.h"
#include "talk/xmpp/xmppclientsettings.h"
#include "talk/examples/login/xmppthread.h"
#include "talk/examples/login/xmppauth.h"
#include "talk/examples/login/xmpppump.h"

class Jingle
{
public :
  Jingle();
  ~Jingle();
  void		init(std::string);

  void WakeTasks() {};
  int64 CurrentTime() {};
  void OnMessage(talk_base::Message *pmsg) {};

private :
  std::string		_username;
  std::string		_server;
  std::string		_jid;
  buzz::Jid		_clientJid;
};

#endif	    /* !JINGLE_HH_ */
