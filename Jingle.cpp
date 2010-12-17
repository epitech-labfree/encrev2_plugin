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
