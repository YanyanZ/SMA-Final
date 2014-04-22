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
  typedef std::vector<std::vector<std::tuple<uchar, uchar> > > FOV;

  using boost::spirit::ascii::space;
  typedef std::string::const_iterator iterator_type;
  typedef Parser::request_toclientboolreply<iterator_type> BRequest_parser;
  typedef Parser::request_toclientgetreply<iterator_type> GRequest_parser;
  typedef Parser::request_toclientmsg<iterator_type> MRequest_parser;

  class Client
  {
  private:
    BRequest_parser bg; /*!< Grammar for Boolean Reply*/
    GRequest_parser gg; /*!< Grammar for Get Reply */
    MRequest_parser mg; /*!< Grammar for Message */

  private:
    Parser::ToClientBoolReply br; /*!< ToClientBoolReply structure */
    Parser::ToClientGetReply gr; /*!< ToClientBoolReply structure */
    Parser::ToClientMSG mr; /*!< ToClientBoolReply structure */

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
    void parse(std::string line);

  public:
    virtual void run(void);
  };
}

#endif
