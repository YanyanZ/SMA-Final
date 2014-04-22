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
  , next_action(0)
  , next_action_msg_to_send("")
  , next_action_msg_to_send_ip("")
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
  else if (ret == "ok")
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
  else
    {
      std::cout << ret << std::endl;
      char c;
      std::cin >> c;
    }

  req_params.clear();
}

std::string Player::move(int dx, int dy)
{
  std::string req;

  req = "move{";
  req += std::to_string(dx) + ";" + std::to_string(dy) + "}";

  req_type = 0;
  req_params.push_back(dx);
  req_params.push_back(dy);

  return req;
}

std::string Player::put(char bc, int dx, int dy)
{
  std::string req;

  req = "put{" + std::to_string(bc) + ";" + std::to_string(dx)
    + ";" + std::to_string(dy) + "}";

  req_type = 1;
  req_params.push_back(20/*block_code*/);
  req_params.push_back(dx);
  req_params.push_back(dy);

  return req;
}

std::string Player::get(int dx, int dy)
{
  std::string req;

  req = "get{" + std::to_string(dx) + ";" + std::to_string(dy) + "}";

  req_type = 2;
  req_params.push_back(dx);
  req_params.push_back(dy);

  return req;
}

std::string Player::send_msg_broadcast(std::string msg)
{
  std::string req;

  req = "mb{\"" + msg + "\"}";

  return req;
}

std::string Player::send_msg(std::string user_ip, std::string msg)
{
  std::string req;

  req = "ms{\"" + user_ip + "\",\"" + msg + "\"}";

  return req;
}

int Player::contact_index(std::string ip)
{
  for (int i = 0; i < contacts_ip.size(); ++i)
    if (contacts_ip[i] == ip)
      return i;

  return -1;
}

int Player::friend_index(std::string ip)
{
  for (int i = 0; i < friend_contacts_ip.size(); ++i)
    if (friend_contacts_ip[i] == ip)
      return i;

  return -1;
}

int Player::enemy_index(std::string ip)
{
  for (int i = 0; i < enemy_contacts_ip.size(); ++i)
    if (enemy_contacts_ip[i] == ip)
      return i;

  return -1;
}

void Player::rcv_msg(std::string user_ip, std::string msg)
{
  // 0: move
  // 1: send global message
  // 2: send message to

  if (std::string::npos != msg.find("roger"))
  {
    next_action = 0;
  }
  else if (std::string::npos != msg.find("buddy"))
  {
    if (0 <= (i = friend_index(user_ip)))
    {
      if (0 < std::rand() % 6)
      {
        next_action = 2;
        next_action_msg_to_send_ip = user_ip;
        next_action_msg_to_send = "roger roger";
      }
    }
    else if (0 <= (i = contact_index(user_ip)))
    {
      contact_index.erase(contact_index.begin() + i);
      friend_index.push_back(user_ip);
      std::cout << "Contact " << user_ip << " is now a friend" << std::endl;
    }
    else if (0 <= (i = enemy_index(user_ip)))
    {
      enemy_index.erase(enemy_index.begin() + i);
      contact_index.push_back(user_ip);
      std::cout << "Enemy " << user_ip << " is now a contact" << std::endl;
    }
  }
  else if (std::string::npos != msg.find("hi"))
  {
    int i;
    if (0 <= (i = friend_index(user_ip)))
    {
      if (0 < std::rand() % 6)
      {
        next_action = 2;
        next_action_msg_to_send_ip = user_ip;
        next_action_msg_to_send = "no buddy!";
      }
    }
    else if (0 <= (i = contact_index(user_ip)))
    {
      if (0 < std::rand() % 4)
      {
        next_action = 2;
        next_action_msg_to_send_ip = user_ip;
        next_action_msg_to_send = "hi there buddy!";
      }
    }
    else if (0 <= (i = enemy_index(user_ip)))
    {
        next_action = 1;
        next_action_msg_to_send = "who cares? i don't!";
    }
    else
    {
      if (0 == std::rand() % 2)
      {
        contacts_ip.push_back(user_ip);
        std::cout << "New contact: " << user_ip << std::endl;
      }
      else if (0 == std::rand() % 2)
      {
        friend_contacts_ip.push_back(user_ip);
        std::cout << "New friend: " << user_ip << std::endl;
      }
      else
      {
        enemy_contacts_ip.push_back(user_ip);
        std::cout << "New enemy: " << user_ip << std::endl;
      }
    }
  }
  else if (std::string::npos != msg.find("nood"))
  {
    if (0 <= (i = friend_index(user_ip)))
    {
      friend_index.erase(friend_index.begin() + i);
      contact_index.push_back(user_ip);
      std::cout << "Friend " << user_ip << " is now a contact" << std::endl;
    }
    else if (0 <= (i = contact_index(user_ip)))
    {
      contact_index.erase(contact_index.begin() + i);
      enemy_index.push_back(user_ip);
      std::cout << "Contact " << user_ip << " is now an enemy" << std::endl;
    }
  }
  else
  {
    next_action = 2;
    next_action_msg_to_send = "roger roger";
    next_action_msg_to_send_ip = user_ip;
  }
}

std::string Player::get_action(void)
{
  std::string req;

  // Send message to
  if (2 == next_action)
  {
    req = send_msg(next_action_msg_to_send_ip, next_action_msg_to_send);

    next_action_msg_to_send = "";
    next_action_msg_to_send_ip = "";
  }

  // Send global message
  else if (1 == next_action)
  {
    req = send_msg_broadcast(next_action_msg_to_send);

    next_action_msg_to_send = "";
  }

  // Move
  else
  {
    if (pos_x == dst.first && pos_y == dst.second)
    {
      dst.first = std::rand() % 800;
      dst.second = std::rand() % 800;

      req = send_msg_broadcast("hi, i'm tired!");
    }
    else
    {
      int dx = dst.first - pos_x;
      int dy = dst.second - pos_y;

      if (0 != dx)
        dx = (0 > dx ? -1 : 1);

      if (0 != dy)
        dy = (0 > dy ? -1 : 1);

      req = move(dx, dy);
    }
  }

  if (0 == std::rand() % 4)
  {
    if ((0 == std::rand() % 4) // Send message to friend
      && 0 < friend_contacts_ip.size())
    {
      next_action = 2;
      int ip = std::rand() % friend_contacts_ip.size();
      next_action_msg_to_send_ip = friend_contacts_ip[ip];
      next_action_msg_to_send = "you're my buddy!";
    }
    else if ((0 == std::rand() % 4) // Send message to contact
      && 0 < contacts_ip.size())
    {
      next_action = 2;
      int ip = std::rand() % contacts_ip.size();
      next_action_msg_to_send_ip = contacts_ip[ip];
      next_action_msg_to_send = "are you my buddy?";
    }
    else if ((0 == std::rand() % 4) // Send message to enemy
      && 0 < enemy_contacts_ip.size())
    {
      next_action = 2;
      int ip = std::rand() % enemy_contacts_ip.size();
      next_action_msg_to_send_ip = enemy_contacts_ip[ip];
      next_action_msg_to_send = "noob.";
    }
    else
    {
      next_action = 0;
    }
  }
  else if (0 == std::rand() % 2) // Send global message
  {
    next_action = 1;
    next_action_msg_to_send = "hi, am i alone?";
  }
  else
  {
    next_action = 0;
  }

  return req;
}
