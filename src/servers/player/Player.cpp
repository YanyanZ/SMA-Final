/*!
 * \file Player.cpp
 * \brief Game Server Functions
 * \author Florian Thomassin
 * \version 1.0
 */
# include "Player.hpp"

using namespace Servers;

Player::Player(std::string user_name, std::string pwd)
  : user_name (user_name), pwd (pwd)
{
}

Player::~Player(void)
{
}
