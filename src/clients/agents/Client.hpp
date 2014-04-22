#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <cstdlib>
# include <cstring>
# include <iostream>
# include <cstring>

# include <boost/asio.hpp>

# include "Player.hpp"

using boost::asio::ip::udp;

enum {max_length = 1024};

using namespace Servers;

namespace Clients
{
  typedef unsigned char uchar;
  typedef std::vector<std::vector<std::tuple<uchar, uchar> > > FOV;

  class Client
  {
  protected:
    // std::string username;
    // std::string password;
    Player p;

  protected:
    char* host;
    char* port;
    boost::asio::io_service io_service;
    udp::socket s;
    udp::resolver resolver;
    udp::endpoint endpoint;
    udp::endpoint sender_endpoint;

  protected:
    char reply[max_length];

  protected:
    FOV fov;

  public:
    Client(std::string u, std::string ps, char* h, char* p, boost::asio::io_service& io);
    virtual ~Client(void);

  protected:
    bool is_connected(void);

  public:
    virtual void run(void);
  };
}

#endif
