# include "Game.hpp"

using namespace Servers;

# include <fstream>

void Game::update_users_page(void)
{
  std::ofstream file;
  std::stringstream buffer;

  file.open("website/users.html");

  buffer << "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\" \"http://www.w3.org/TR/html4/strict.dtd\">" << std::endl;
  buffer << "<html>" << std::endl;
  buffer << "<head>" << std::endl;
  buffer << "\t<meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\" />" << std::endl;;
  buffer <<  "\t<style type=\"text/css\" title=\"currentStyle\">" << std::endl;
  buffer << "\t<script type=\"text/javascript\" language=\"javascript\" src=\"DataTable-1.9.4/media/js/jquery.js\"></script>" << std::endl;
  buffer << "\t<script type=\"text/javascript\" language=\"javascript\" src=\"DataTable-1.9.4/media/js/jquery.dataTables.js\"></script>" << std::endl;
  buffer << "\t<script type=\"text/javascript\" charset=\"utf-8\">" << std::endl;
  buffer << "\t\t$(document).ready(function() {" << std::endl;
  buffer << "\t\t\t$('#example').dataTable();" << std::endl;
  buffer << "\t\t} );" << std::endl;
  buffer << "\t</script>" << std::endl;

  buffer << "</head>" << std::endl;

  buffer << "<body>" << std::endl;
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
  buffer << "</body>" << std::endl;
  buffer << "<html>" << std::endl;
  file << buffer.str();

  file.close();

  std::cout << buffer.str() << std::endl;
}
