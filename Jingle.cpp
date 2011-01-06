#include "Jingle.hh"
#include <iostream>

using namespace std;

Jingle::Jingle()
{
  cout << "Initialise libJingle" << endl;
  talk_base::InitializeSSL();
  cout << "LibJingle initialised : ... done" << endl;
}

Jingle::~Jingle()
{
  cout << "Libjingle : destroyed" << endl;
}

void		Jingle::init(std::string username)
{
  //thread la lib
#if WIN32
  talk_base::Win32Thread w32_thread;
  talk_base::ThreadManager::SetCurrent(&w32_thread);
#endif

  talk_base::Thread* main_thread = talk_base::Thread::Current();

  // buzz::Jid				jid;
  // buzz::XmppClientSettings		xcs;
  // talk_base::InsecureCryptStringImpl	pass;
  _username = username;
  _clientJid = buzz::Jid(username);
  if (!_clientJid.IsValid() || _clientJid.node() == "") {
    printf("jid invalid : username=login@doamin\n");
    return ;
  }

  buzz::XmppClientSettings xcs;
  xcs.set_user(_clientJid.node());
  xcs.set_resource("call");
  xcs.set_host(_clientJid.domain());
  xcs.set_use_tls(!true);
  xcs.set_use_tls(false);
  xcs.set_allow_plain(true);

  std::string	host;
  short		port;
  int		pos = _server.find(':');
  if (pos == -1)
    {
      host = _server;
      port = 5222;
    }
  else
    {
      host = _server.substr(0, pos);
      port = atoi(_server.substr(pos + 1).c_str());
    }
  xcs.set_server(talk_base::SocketAddress(host, port));
}
