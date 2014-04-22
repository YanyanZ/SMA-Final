# include "Game.hpp"

using namespace Servers;

bool Game::is_account_exist(std::string ip)
{
  return players.end() != players.find(ip);
}

void Game::sendmessage(std::string sender, std::string msg, udp::socket& sock)
{
  std::vector<std::string> res;
  boost::split(res, sender, boost::is_any_of(":"));
  udp::endpoint sender_endpoint(boost::asio::ip::address::from_string(res[0]),
				atoi(res[1].c_str()));

  sock.send_to(boost::asio::buffer(msg.c_str(), msg.size()), sender_endpoint);
}

void Game::broadcast(std::string from, std::string msg)
{
  udp::socket sock(io_service, udp::endpoint(udp::v4(), port + 1));
  for (std::map<std::string, Player*>::iterator it = players.begin(); it != players.end(); it++)
    {
      std::stringstream newmsg;
      newmsg << "bo{\"" << from << "\";\"" << it->second->user_name << "\"}"; 
      sendmessage(it->first, newmsg.str(), sock);
    }
}

int Game::parse_request(std::string& line, std::string& ip)
{
  std::string::const_iterator iter = line.begin();
  std::string::const_iterator end = line.end();

  std::cout << "> Request: '" << line << "'" << std::endl;
  if (phrase_parse(iter, end, cg, space, co) && iter == end)
  {
    std::cout << " DONE" << std::endl;
    if (!is_account_exist(ip))
    {
      return 0;
    }
    else
    {
      return -1;
    }
  }
  else if (phrase_parse(iter, end, mg, space, mv) && iter == end)
  {
    return 1;
  }
  else if (phrase_parse(iter, end, pg, space, pu) && iter == end)
  {
    return 2;
  }
  else if (phrase_parse(iter, end, gg, space, ge) && iter == end)
  {
    return 3;
  }
  else
  {
    std::cout << " FAIL" << std::endl;

    return -1;
  }
}

std::string Game::exec_request(std::string line, std::string ip, std::string port)
{
  int ret = -1;

  ip += ":" + port;
  if (0 > (ret = parse_request(line, ip)))
    return "fail";

  // connexion
  if (0 == ret)
  {
    Player* p = new Player(co.user, co.pass);
    players[ip] = p;
    update_users_page();
  }
  else if (1 == ret)
  {
    if (!is_account_exist(ip))
      return "fail";

    Player* p = players[ip];
    Matrix m = univers[p->world_id];

    m[p->pos_x][p->pos_y].second = nullptr;

    p->pos_x = (p->pos_x + mv.dx) % 800 < 0 ? 799 : (p->pos_x + mv.dx) % 800;
    p->pos_y = (p->pos_y + mv.dy) % 800 < 0 ? 799 : (p->pos_y + mv.dy) % 800;

    m[p->pos_x][p->pos_y].second = p;
  }
  else if (2 == ret)
  {
    if (!is_account_exist(ip))
      return "fail";

    Player* p = players[ip];
    Matrix m = univers[p->world_id];

    int dst_x = (p->pos_x + pu.dx) % 800 < 0 ? 799 : (p->pos_x + pu.dx) % 800;
    int dst_y = (p->pos_y + pu.dy) % 800 < 0 ? 799 : (p->pos_y + pu.dy) % 800;

    m[dst_x][dst_y].first = pu.block_code;
  }
  else if (3 == ret)
  {
    if (!is_account_exist(ip))
      return "fail";

    Player* p = players[ip];
    Matrix m = univers[p->world_id];

    int dst_x = (p->pos_x + ge.dx) % 800 < 0 ? 799 : (p->pos_x + ge.dx) % 800;
    int dst_y = (p->pos_y + ge.dy) % 800 < 0 ? 799 : (p->pos_y + ge.dy) % 800;

    char block_code = m[dst_x][dst_y].first;

    std::string ret;
    ret += block_code;
    return ret;
  }

  return "ok";
}
