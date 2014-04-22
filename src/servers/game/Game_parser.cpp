# include "Game.hpp"

using namespace Servers;

bool Game::is_account_exist(std::string ip)
{
  return players.end() != players.find(ip));
}

int Game::parse_request(std::string& line, std::string& ip)
{
  std::string::const_iterator iter = line.begin();
  std::string::const_iterator end = line.end();

  std::cout << "> Request: '" << line << "'";
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
  }
  else if (1 == ret)
  {
    if (!is_account_exist(ip))
      return "fail";

    Player* p = players[ip];
    Matrix m = univers[p->world_id];

    m[p->pos_x][p->pos_y].second = nullptr;

    p->pos_x += mv.x;
    p->pos_y += mv.y;

    m[p->pos_x][p->pos_y].second = p;
  }

  return "ok";
}
