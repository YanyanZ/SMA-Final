/*!
 * \file Game.cpp
 * \brief Game Server Functions
 * \author Florian Thomassin
 * \version 1.0
 */
# include "Game.hpp"

using namespace Servers;

Game::Game(unsigned short p, const int mnplan, const int mnplay)
  : max_nb_planets (mnplan), max_nb_players (mnplay), port (p)
{
}

Game::~Game(void)
{
}

void Game::load_planets(void)
{
  for (int nb_p = 0; nb_p < 1; ++nb_p)
  {
    Matrix tmp_mx;

    for (int i = 0; i < 800; ++i)
    {
      std::vector<std::pair<uchar, Player*> > tmp_i;

      for (int j = 0; j < 800; ++j)
        tmp_i.push_back(std::make_pair<uchar, Player*>(0, nullptr));

      tmp_mx.push_back(tmp_i);
    }

    univers.push_back(tmp_mx);
  }
}

void Game::load_accounts(std::string file)
{
}

void Game::run(void)
{
  udp::socket sock(io_service, udp::endpoint(udp::v4(), port));
  for (;;)
  {
    char data[max_length];
    udp::endpoint sender_endpoint;
    int length = sock.receive_from(boost::asio::buffer(data, max_length), sender_endpoint);
    std::string rep = "";
    std::string crequest = std::string(boost::asio::buffer_cast<char*>(boost::asio::buffer(data, max_length)));
    crequest = crequest.substr(0, length);

    std::string reply = exec_request(crequest, sender_endpoint.address().to_string(), std::to_string(sender_endpoint.port()));
    sock.send_to(boost::asio::buffer(reply.c_str(), reply.size()), sender_endpoint);
  }
}

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Bad usage - ./exe port_number" << std::endl;
    return -1;
  }

  Game* gm = new Game(atoi(argv[1]), 1, 1);

  gm->run();

  delete gm;
  return 0;
}

