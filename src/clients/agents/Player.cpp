/*!
 * \file Player.cpp
 * \brief Game Server Functions
 * \author Florian Thomassin
 * \version 1.0
 */
# include "Player.hpp"

using namespace Servers;

Player::Player(std::string user_name, std::string pwd)
  : pos_x (0)
  , pos_y (0)
  , world_id(0)
  , user_name(user_name)
  , pwd(pwd)
  , state(0)
{
}

Player::~Player(void)
{
}

std::pair<int, int> Player::get_move(void)
{
  std::pair<int, int> m = std::make_pair<int, int>(0, 0);

  if (0 == state)
  {
  	m.first = 1;
  	if (20 <= pos_x)
  		state++;
  }
  else if (1 == state)
  {
  	m.second = 1;
  	if (20 <= pos_y)
  		state++;
  }
  else if (2 == state)
  {
  	m.first = -1;
  	if (0 >= pos_x)
  		state++;
  }
  else // if (3 == state)
  {
  	m.second = -1;
  	if (0 >= pos_y)
  		state = 0;
  }

  return m;
}