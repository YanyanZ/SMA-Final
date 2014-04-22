# include "Game.hpp"

using namespace Servers;

void Game::update_users_page(void)
{
  const std::string page = "users.html";
  std::stringstream buffer;

  buffer << "<div>" << std::endl;
  buffer << "\t<table cellpadding=\"0\" cellspacing=\"0\" border=\"0\" class=\"display\" id=\"example\" width=\"100%\">" << std::endl;
  buffer << "\t\t<thread>" << std::endl;
  buffer << "\t\t\t<tr>" << std::endl;
  buffer << "\t\t\t\t<th>ID</th>" << std::endl;
  buffer << "\t\t\t\t<th>User name</th>" << std::endl;
  buffer << "\t\t\t\t<th>Address</th>" << std::endl;
  buffer << "\t\t\t\t<th>World</th>" << std::endl;
  buffer << "\t\t\t\t<th>X</th>" << std::endl;
  buffer << "\t\t\t\t<th>Y</th>" << std::endl;
  buffer << "\t\t\t</tr>" << std::endl;
  buffer << "\t\t</thread>" << std::endl;
  buffer << "\t\t<tbody>" << std::endl;

  for (std::map<std::string, Player*>::iterator it = players.begin(); it != players.end(); it++)
    {
      buffer << "Address: " << it->first << std::endl;
      buffer << "Username: " << it->second->user_name << std::endl;
      buffer << "World: " << it->second->world_id << std::endl;
      buffer << "Position: {" << it->second->pos_x << "; " << it->second->pos_y << "}" << std::endl; 
      buffer << std::endl;
    }

  buffer << "\t</table>" << std::endl;
  buffer << "<div>" << std::endl;

  std::cout << buffer.str() << std::endl;
}
