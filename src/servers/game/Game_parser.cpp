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
      newmsg << "ms{\"" << from << "\";\"" << it->second->user_name << ": " << msg <<"\"}"; 
      sendmessage(it->first, newmsg.str(), sock);
    }
  sock.close();
}

int Game::parse_request(std::string& line, std::string& ip, udp::socket& sock)
{
  std::string::const_iterator iter = line.begin();
  std::string::const_iterator end = line.end();

  std::cout << "> Request: '" << line << "'" << std::endl;
  if (phrase_parse(iter, end, cg, space, co) && iter == end)
  {
    if (!is_account_exist(ip))
    {
      return 0;
    }
    else
    {
      return -1;
    }
  }
  else if (phrase_parse(iter, end, bg, space, broad) && iter == end)
    {
      broadcast(ip, broad.msg);
      broad.msg = "";
      return -2;
      }
  else if (phrase_parse(iter, end, sg, space, send) && iter == end)
    {
      sendmessage(send.sender, send.msg, sock);
      send.sender = "";
      send.msg = "";
      return -2;
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
  else if (phrase_parse(iter, end, rfovg, space, rfov) && iter == end)
    return 4;
  else
  {
    return -1;
  }
}

std::string Game::exec_request(std::string line, std::string ip, std::string port, udp::socket& sock)
{
  int ret = -1;

  ip += ":" + port;
  if (0 > (ret = parse_request(line, ip, sock)))
    return "rep{1}";

  // connexion
  if (0 == ret)
  {
    Player* p = new Player(co.user, co.pass);
    players[ip] = p;
    co.user = "";
    co.pass = "";
  }
  else if (1 == ret)
  {
    if (!is_account_exist(ip))
      return "rep{1}";

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
      return "rep{0}";

    Player* p = players[ip];
    Matrix m = univers[p->world_id];

    int dst_x = (p->pos_x + pu.dx) % 800 < 0 ? 799 : (p->pos_x + pu.dx) % 800;
    int dst_y = (p->pos_y + pu.dy) % 800 < 0 ? 799 : (p->pos_y + pu.dy) % 800;

    m[dst_x][dst_y].first = pu.block_code;
  }
  else if (3 == ret)
  {
    if (!is_account_exist(ip))
      return "rep{1}";

    Player* p = players[ip];
    Matrix m = univers[p->world_id];

    int dst_x = (p->pos_x + ge.dx) % 800 < 0 ? 799 : (p->pos_x + ge.dx) % 800;
    int dst_y = (p->pos_y + ge.dy) % 800 < 0 ? 799 : (p->pos_y + ge.dy) % 800;

    char block_code = m[dst_x][dst_y].first;

    std::string ret;
    ret += block_code;
    return ret;
  }
  else if (4 == ret)
    {
      std::stringstream ss;
      ss << "fov{";

      for (int i = rfov.x - 2; i < rfov.x + 1; i++)
	for (int j = rfov.y - 2; j < rfov.y + 2; j++)
	    ss << univers[0][i][j].first << ";"; 
      ss << univers[0][rfov.x + 1][rfov.y + 1].first << "}";

      return ss.str();
    }

  return "rep{0}";
}
