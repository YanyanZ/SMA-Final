# include "Game.hpp"

using namespace Servers;

bool Game::is_account_exist(std::string u, std::string p)
{
  return true;
}

std::string Game::parse_request(std::string line)
{
  std::string::const_iterator iter = line.begin();
  std::string::const_iterator end = line.end();

  std::cout << "> Request: '" << line << "'";
  if (phrase_parse(iter, end, cg, space, co) && iter == end)
  {
    std::cout << " DONE" << std::endl;
    if (is_account_exist(co.user, co.pass))
    {
      return "ok";
    }
    else
    {
      return "fail";
    }
  }
  else if (phrase_parse(iter, end, mg, space, mv) && iter == end)
  {
    return "ok";
  }
  else
  {
    std::cout << " FAIL" << std::endl;

    return "fail";
  }
}
