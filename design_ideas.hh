/*
** design_ideas.hh
** Login : <elthariel@rincevent>
** Started on  Wed Feb 16 06:40:53 2011 elthariel
** $Id$
**
** Author(s):
**  - elthariel <elthariel@gmail.com>
**
** Copyright (C) 2011 elthariel
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#ifndef   	DESIGN_IDEAS_HH_
# define   	DESIGN_IDEAS_HH_

# include <stdint.h>

# include <string>
# include <vector>

# include <boost/utility.hpp>
# include <boost/shared_pointer.hpp>
# include <boost/signals2.hpp>

namespace vlc
{
  class media_player;

  class instance : public boost::noncopyable
  {
  public:
    instance();
    instance(std::vector<std::string> vlc_instance_opts); // e.g. "-vv"
    ~instance();

    boost::shared_ptr<stream>           create();
  protected:
    libvlc_instance_t                   *m_vlc;
  };

  class stream : public boost::noncopyable
  {
  public:
    enum state
      {
        ACTIVE,         // not configurable anymore
                        // you should stop it before changing options
        INACTIVE        // configurable
      };
    virtual ~stream();

    virtual state                       state();
    // This method returns a bool because some parameters may not
    // fulfill security policies.
    virtual bool                        set_options(std::vector<std::string>);
    virtual bool                        play();
    virtual bool                        stop();


  protected:
    stream() {}
    stream(libvlc_media_player_t *mp);

    libvlc_media_player_t               *m_mp;
    libvlc_media_t                      *m_media;

    friend                              class instance;
  };

  /*
   * The following classes only show the basic idea behind them, i let
   * you the implementation details.  One of the main idea is to use
   * boost::signals2 mechanism to implement callback when data is
   * available/needed. Boost documentation features a nice tutorial on
   * signals2. You shouldn't direcly provide functors to these signals
   * but instead use boost::bind (see boost docs as well).
   */
  class input_stream : public stream
  {
    // ...
    // imem             m_imem;

    // Here the streambuf (or a similar name) class of boost::asio
    // could replace this c-style stuff.
    boost::signals2::signal<uin32_t (const char *, uin32_t)> &on_data_needed();
  protected:
    boost::signals2::signal<uin32_t (const char *, uin32_t)> m_signal;
  };
  class output_stream : public stream
  {
    // ...
    // smem             m_smem;
    boost::signals2::signal<uin32_t (const char *, uin32_t)> &on_data_available();
  protected:
    boost::signals2::signal<uin32_t (const char *, uin32_t)> m_signal;
  };

  /*
   * Maybe the 2 following class could share a common ancestor/interface
   * providing genericity for managing specific vlc modules.
   */
  class imem //... boost::noncopyable, ...
  {
    // should contain imem dirty details.
  };
  class smem //... boost::noncopyable, ...
  {
    // should contain smem dirty details.
  };

}

/*****************************************************************************************
 * Network/Protocol related stuff below
 *
 * This part is mostly trash, just some random design ideas regarding
 * this part of the code. If you find simpler yet as (more?)
 * extensible and loosely coupled. Don't hesitate to implement your
 * own idea if you're pretty sure about it.
 *
 */

// ? Could std::string handle binary data, i.e. does it relies on the
// "\0" at the end ?
typedef magic_data_structure binary_data;

class network : boost::noncopyable
{
public:
  enum state //network level state
    {
      ERROR,
      CONNECTED,
      NOT_CONNECTED
    };

  network(std::string host, uint16_t port);
  uin32_t                               send_data;

  boost::signals2::signal<void (binary_data &)> on_data_received();
  // ... other usefull features
protected:
  network();

  boost::signals2::signal<void (binary_data &)> m_data_received;
  // ... other implementation related members
};

class protocol;
class client : boost::noncopyable
{
public:
  enum state // client/application-logic level state
    {
      ERROR,
      NOT_CONNECTED,
      CONNECTED,
      AUTHENTICATED,
      PUBLISHING,
      RECEIVING
    };

  void                          on_data_received(binary_data &); // This calls the protocol class.
  state                         &state();
  std::map<std::string, std::string> &options();

  // ...
protected:
  protocol                      m_protocol;
  std::map<std::string, std::string> m_options;
};

class protocol
{
public:
  protocol();

  void                          parse_incoming_data(binary_data &buf, client &da_client);
protected:
  bool                          is_header_complete(); // Is there a "\n\n" at the end of the buffer ?
  bool                          update_client_state();
  bool                          update_client_options();

  binary_data                   m_header_buffer;
}

#endif	    /* !DESIGN_IDEAS_HH_ */
