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
      buffer << "\t\t\t<tr class=\"gradeA\">" << std::endl;
      buffer << "\t\t\t<td>" << it->first << "</td>" <<std::endl;
      buffer << "\t\t\t<td>" << it->second->user_name << "</td>" << std::endl;
      buffer << "\t\t\t<td>" << it->second->world_id << "</td>" << std::endl;
      buffer << "\t\t\t<td>" << it->second->pos_x << "</td>" << std::endl;
      buffer << "\t\t\t<td>" << it->second->pos_y << "</td>" << std::endl; 
    }

  buffer << "\t</table>" << std::endl;
  buffer << "<div>" << std::endl;

  std::cout << buffer.str() << std::endl;
}
