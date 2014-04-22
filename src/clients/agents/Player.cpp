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
  if (0 == ret.compare("fail"))
  {
    std::cout << "Failed action type: " << req_type << "with params:" << std::endl;
    for (int i = 0; i < req_params.size(); ++i)
        std::cout << i << " " << req_params[i] << std::endl;

    dst.first = std::rand() % 800;
    dst.second = std::rand() % 800;
  }
  else if (ret == "ok")
  {
    if (0 == req_type)
    {
        pos_x += req_params[0];
        pos_y += req_params[1];
        std::cout << "New pos: x: " << pos_x << " y: " << pos_y << std::endl;
    }
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
  else
    {
      std::cout << ret << std::endl;
      char c;
      std::cin >> c;
    }

  req_params.clear();
}

std::string Player::get_action(void)
{
  std::string req;

  if (pos_x == dst.first && pos_y == dst.second)
  {
    int dx = 0;
    int dy = 0;

    req = "get{" + std::to_string(dx) + ";" + std::to_string(dy) + "}";

    req_type = 2;
    req_params.push_back(dx);
    req_params.push_back(dy);

    // char block_code = 1;
    // int dx = 0;
    // int dy = 0;

    // req = "put{" + std::to_string(block_code) + ";" + std::to_string(dx)
    //   + ";" + std::to_string(dy) + "}";

    // req_type = 1;
    // req_params.push_back((int)block_code);
    // req_params.push_back(dx);
    // req_params.push_back(dy);
  }
  else
  {
    std::pair<int, int> m = get_move();

    req = "move{";
    req += std::to_string(m.first) + ";" + std::to_string(m.second) + "}";

    req_type = 0;
    req_params.push_back(m.first);
    req_params.push_back(m.second);
  }

  return req;
}
