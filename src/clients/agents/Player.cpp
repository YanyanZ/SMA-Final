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
  // , state(0)
  , req_type(0)
{
  std::srand((unsigned int)std::time(NULL));
  dst.first = std::rand() % 800;
  dst.second = std::rand() % 800;
}

Player::~Player(void)
{
}

std::pair<int, int> Player::get_move(void)
{
  std::pair<int, int> m = std::make_pair<int, int>(0, 0);

  m.first = dst.first - pos_x;
  m.second = dst.second - pos_y;

  if (0 != m.first)
    m.first = (m.first < 0 ? -1 : 1);

  if (0 != m.second)
    m.second = (m.second < 0 ? -1 : 1);

  return m;
}

void Player::dump_inventory(void)
{
  std::cout << "Inventory is:" << std::endl
    << "code:\tnb" << std::endl;

  for (auto& item: inventory)
    std::cout << "  " << (int)(item.first) << ":\t" << item.second << std::endl;
}

void Player::action_result(std::string ret)
{
  // Prper parsing here

  if (0 == ret.compare("fail"))
  {
    std::cout << "Failed action type: " << req_type << "with params:" << std::endl;
    for (int i = 0; i < req_params.size(); ++i)
        std::cout << i << " " << req_params[i] << std::endl;

    dst.first = std::rand() % 800;
    dst.second = std::rand() % 800;
  }
  else
  {
    // Move
    if (0 == req_type)
    {
        pos_x += req_params[0];
        pos_y += req_params[1];
        std::cout << "New pos: x: " << pos_x << " y: " << pos_y << std::endl;
    }

    // Put
    else if (1 == req_type)
    {
      dst.first = std::rand() % 800;
      dst.second = std::rand() % 800;

      std::cout << "Added block type " << req_params[0] << " @ pos: x: "
        << pos_x + req_params[1] << " y: " << pos_y + req_params[2] << std::endl;

      inventory[(char)(req_params[0])]--;

      dump_inventory();

      char c;
      std::cin >> c;
    }

    // Get
    else if (2 == req_type)
    {
      char block_code = ret.c_str()[0];

      dst.first = std::rand() % 800;
      dst.second = std::rand() % 800;

      std::cout << "Got block type " << (int)block_code << " @ pos: x: "
        << pos_x + req_params[0] << " y: " << pos_y + req_params[1] << std::endl;

      inventory[block_code]++;

      dump_inventory();

      char c;
      std::cin >> c;
    }
  }

  req_params.clear();
}

std::string Player::move(int dx, int dy)
{
  std::stirng req;

  req = "move{";
  req += std::to_string(dx) + ";" + std::to_string(dy) + "}";

  req_type = 0;
  req_params.push_back(dx);
  req_params.push_back(dy);

  return req;
}

std::string Player::put(char bc, int dx, int dy)
{
  std::stirng req;

  req = "put{" + std::to_string(bc) + ";" + std::to_string(dx)
    + ";" + std::to_string(dy) + "}";

  req_type = 1;
  req_params.push_back((int)block_code);
  req_params.push_back(dx);
  req_params.push_back(dy);

  return req;
}

std::string Player::get(int dx, int dy)
{
  std::stirng req;

  req = "get{" + std::to_string(dx) + ";" + std::to_string(dy) + "}";

  req_type = 2;
  req_params.push_back(dx);
  req_params.push_back(dy);

  return req;
}

std::string Player::msg_broadcast(std::string msg)
{
  std::stirng req;

  req = "mb{\"" + msg + "\"}";

  return req;
}

std::string Player::msg(std::string user_ip, std::string msg)
{
  std::stirng req;

  req = "ms{\"" + user_ip + "\",\"" + msg + "\"}";

  return req;
}

std::string Player::get_action(void)
{
  std::string req;

  // std::pair<int, int> m = get_move();
  // req = move(m.first, m.second);

  // req = put((char)0, 0, 0);

  // req = get(0, 0);

  // req = msg_broadcast("Hello!");

  // req = msg("128.0.0.1:8088", "Hello!");

  return req;
}
