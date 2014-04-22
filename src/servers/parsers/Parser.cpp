# include "Parser.hpp"

int main()
{
  std::cout << "/////////////////////////////////////////////////////////\n\n";
  std::cout << "\t\tAn Request parser for Spirit...\n\n";
  std::cout << "/////////////////////////////////////////////////////////\n";
  std::cout << "Type [q or Q] to quit" << std::endl << std::endl;

  using boost::spirit::ascii::space;
  typedef std::string::const_iterator iterator_type;
  typedef Parser::request_connexion<iterator_type> CRequest_parser;
  typedef Parser::request_move<iterator_type> MRequest_parser;

  CRequest_parser g; // Our grammar
  MRequest_parser g2;

  std::string str;

  std::cout << "> ";
  while (getline(std::cin, str))
  {
    if (str.empty() || str[0] == 'q' || str[0] == 'Q')
      break;

    Parser::Connexion emp;
    Parser::Move mv;
    std::string::const_iterator iter = str.begin();
    std::string::const_iterator end = str.end();

    bool r = phrase_parse(iter, end, g, space, emp);
    if (r && iter == end)
    {
      std::cout << "-------------------------\n";
      std::cout << "Parsing succeeded\n";
      std::cout << "got: " << boost::fusion::as_vector(emp) << std::endl;
      std::cout << "\n-------------------------\n";
    }
    else
    {
      r = phrase_parse(iter, end,  g2, space, mv);
      if (r && iter == end)
      {
	std::cout << "-------------------------\n";
	std::cout << "Parsing succeeded\n";
	std::cout << "got: " << boost::fusion::as_vector(mv) << std::endl;
	std::cout << "\n-------------------------\n";
      }
      else
      {
	std::cout << "-------------------------\n";
	std::cout << "Parsing failed\n";
	std::cout << "-------------------------\n";
      }
    }
    std::cout << "> ";
  }

  std::cout << "Bye... :-) \n\n";
  return 0;
}
