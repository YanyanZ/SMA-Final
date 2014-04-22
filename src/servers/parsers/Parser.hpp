#ifndef PARSERS_HPP
# define PARSERS_HPP

# include <boost/config/warning_disable.hpp>
# include <boost/spirit/include/qi.hpp>
# include <boost/spirit/include/phoenix_core.hpp>
# include <boost/spirit/include/phoenix_operator.hpp>
# include <boost/spirit/include/phoenix_object.hpp>
# include <boost/fusion/include/adapt_struct.hpp>
# include <boost/fusion/include/io.hpp>

namespace Parser
{
  namespace qi = boost::spirit::qi;
  namespace ascii = boost::spirit::ascii;

  struct Connexion
  {
    std::string user;
    std::string pass;
  };

  struct Move
  {
    int x;
    int y;
  };
}

BOOST_FUSION_ADAPT_STRUCT(
  Parser::Connexion,
  (std::string, user)
  (std::string, pass)
  )

BOOST_FUSION_ADAPT_STRUCT(
  Parser::Move,
  (int, x)
  (int, y)
  )

namespace Parser
{
  template <typename Iterator>
  struct request_connexion : qi::grammar<Iterator, Connexion(), ascii::space_type>
  {
    request_connexion() : request_connexion::base_type(start)
    {
      using qi::int_;
      using qi::lit;
      using qi::lexeme;
      using ascii::char_;

      quoted_string %= lexeme['"' >> +(char_ - '"') >> '"'];

      start %= lit("co")
	>> '{'
	>> quoted_string >> ';'
	>> quoted_string
	>> '}';
    }

    qi::rule<Iterator, std::string(), ascii::space_type> quoted_string;
    qi::rule<Iterator, Connexion(), ascii::space_type> start;
  };

  template <typename Iterator>
  struct request_move : qi::grammar<Iterator, Move(), ascii::space_type>
  {
    request_move() : request_move::base_type(start)
    {
      using qi::int_;
      using qi::lit;

      start %= lit("move")
	>> '{'
	>> int_ >> ';' >> int_
	>> '}';
    }

    qi::rule<Iterator, Move(), ascii::space_type> start;
  };
}

#endif
