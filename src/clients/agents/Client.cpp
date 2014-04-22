# include "Client.hpp"

using namespace Clients;

Client::Client(std::string u, std::string ps, char* h, char* p, boost::asio::io_service& io)
  : username (u), password (ps), host (h), port (p),
    s(io_service, udp::endpoint(udp::v4(), 0)), resolver(io)
{
  fov.resize(16);
  for (int i = 0; i < fov.size(); i++)
    fov[i].resize(16);

  endpoint = *resolver.resolve({udp::v4(), host, port});
}

Client::~Client(void)
{
}

bool Client::is_connected(void)
{
  std::string request = std::string("co{\"") + username +
    std::string("\";\"") + password + std::string("\"}");

  s.send_to(boost::asio::buffer(request.c_str(), request.size()), endpoint);
  size_t reply_length = s.receive_from(
    boost::asio::buffer(reply, max_length), sender_endpoint);

  std::string rep = std::string(boost::asio::buffer_cast<char*>(boost::asio::buffer(reply, reply_length)));
  rep = rep.substr(0, reply_length);

  if (rep.compare("ok") == 0)
    return true;
  else
    return false;
}

void Client::run(void)
{
  if (is_connected())
  {
    while (true)
    {
      /* A changer */
      std::cout << "Enter message: ";
      std::string req;
      std::cin >> req;
      /* Fin changement */

      s.send_to(boost::asio::buffer(req, req.size()), endpoint);

      size_t reply_length = s.receive_from(
	boost::asio::buffer(reply, max_length), sender_endpoint);

    /* A changer */
      std::cout << "Reply is: ";
      std::cout.write(reply, reply_length);
      std::cout << "\n";
      /* Fin changement */
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
