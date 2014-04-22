# include "Client.hpp"

using namespace Clients;

Client::Client(std::string u, std::string ps, char* h, char* p, boost::asio::io_service& io)
  : p(u, ps)/*username (u), password (ps)*/, host (h), port (p),
    s(io_service, udp::endpoint(udp::v4(), 0)), resolver(io)
{

  endpoint = *resolver.resolve({udp::v4(), host, port});

  std::cout << h << " "  << p << std::endl;
}

Client::~Client(void)
{
}

bool Client::is_connected(void)
{
  std::string request = std::string("co{\"") + p.user_name +
    std::string("\";\"") + p.pwd + std::string("\"}");

  s.send_to(boost::asio::buffer(request.c_str(), request.size()), endpoint);
  size_t reply_length = s.receive_from(
    boost::asio::buffer(rep, max_length), sender_endpoint);

  std::string repp = std::string(boost::asio::buffer_cast<char*>(boost::asio::buffer(rep, reply_length)));

  if (parse(repp) == 0)
    return true;
  else
    return false;
}

int Client::parse(std::string line)
{
  std::string::const_iterator iter = line.begin();
  std::string::const_iterator end = line.end();

  std::cout << "> Input: '" << line << "'" << std::endl;
  if (phrase_parse(iter, end, brg, space, reply) && iter == end)
  {
    return reply.r;
  }
  else if (phrase_parse(iter, end, sg, space, send) && iter == end)
    {
      p.rcv_message(send.sender, send.msg);
      // std::cout << send.msg << std::endl;
      // send.msg = "";
      // send.sender = "";
      return 0;
    }
  /*  else if (phrase_parse(iter, end, fovg, space, fov) && iter == end)
      return 0;*/
  else
    return 1;
}

void Client::run(void)
{
  if (is_connected())
  {
    while (true)
    {
      memset(rep, 0, max_length);

      // std::pair<int, int> m = p.get_move();
      // std::string req("move{");
      // req += std::to_string(m.first) + ";" + std::to_string(m.second) + "}";

      std::string req(p.get_action());

      //      std::string req = "mb{\"Je fais un test\"}";
      // std::string req = "rfov{400;400}";

      s.send_to(boost::asio::buffer(req, req.size()), endpoint);

      s.receive_from(boost::asio::buffer(rep, max_length), sender_endpoint);

      std::string reply_str(rep);

      // parse reply_str here and call proper player methode
      parse(reply_str);
      // p.action_result(reply_str);
      char c;
      std::cin >> c;

      // if (reply_str.compare("ok") == 0)
      // {
      //   p.action_result(true);
        // p.pos_x += m.first;
        // p.pos_y += m.second;
        // std::cout << "New pos: x: " << p.pos_x << " y: " << p.pos_y << std::endl;
      // }
      // else
      //   std::cout << "Pos is still: x: " << p.pos_x << " y: " << p.pos_y << std::endl;
    }
  }
  else
  {
    std::cerr << "> Connection failed - Bad username/password";
    std::cerr << std::endl;
    return;
  }
}

int main(int argc, char** argv)
{
  if (argc != 5)
  {
    std::cerr << "Bad usage - ./exe host port" << std::endl;
    return -1;
  }

  boost::asio::io_service io;
  Client* client = new Client(argv[3], argv[4], argv[1], argv[2], io);

  client->run();

  delete client;
  return 0;
}
