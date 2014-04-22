#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <cstdlib>
# include <cstring>
# include <iostream>
# include <cstring>

# include <boost/asio.hpp>

# include "../../servers/parsers/Parser.hpp"
# include "Player.hpp"

using boost::asio::ip::udp;

enum {max_length = 1024};

using namespace Servers;

namespace Clients
{
  typedef unsigned char uchar;

  using boost::spirit::ascii::space;
  typedef std::string::const_iterator iterator_type;

  typedef Parser::request_message<iterator_type> SRequest_parser;
  typedef Parser::request_toclientboolreply<iterator_type> BRRequest_parser;
  typedef Parser::request_fov<iterator_type> FOVRequest_parser;

  class Client
  {
  private:
    SRequest_parser sg;
    BRRequest_parser brg;
    //FOVRequest_parser fovg;

  private:
    Parser::Message send;
    Parser::ToClientBoolReply reply;
    //Parser::FieldOfView fov;

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
    char rep[max_length];

  public:
    Client(std::string u, std::string ps, char* h, char* p, boost::asio::io_service& io);
    virtual ~Client(void);

  protected:
    bool is_connected(void);
    int parse(std::string line);

  public:
    virtual void run(void);
  };
}

#endif
