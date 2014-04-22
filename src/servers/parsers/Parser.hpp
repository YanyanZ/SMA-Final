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
    int dx;
    int dy;
  };

  struct Put
  {
    char block_code;
    int dx;
    int dy;
  };

  struct Get
  {
    int dx;
    int dy;
  };

  struct ToClientBoolReply
  {
    int r;
  };

  struct ToClientGetReply
  {
    char block_code;
  };

  struct Message
  {
    std::string sender;
    std::string msg;
  };

  struct Broadcast
  {
    std::string msg;
  };

  struct RFieldOfView
  {
    int x;
    int y;
  };

  struct FieldOfView
  {
    int x00;
    int x01;
    int x02;
    int x03;
    int x04;

    int x10;
    int x11;
    int x12;
    int x13;
    int x14;

    int x20;
    int x21;
    int x22;
    int x23;
    int x24;

    int x30;
    int x31;
    int x32;
    int x33;
    int x34;

    int x40;
    int x41;
    int x42;
    int x43;
    int x44;
  };
}


BOOST_FUSION_ADAPT_STRUCT(
  Parser::RFieldOfView,
  (int, x)
  (int, y)
  )


BOOST_FUSION_ADAPT_STRUCT(
  Parser::Connexion,
  (std::string, user)
  (std::string, pass)
  )

BOOST_FUSION_ADAPT_STRUCT(
  Parser::Move,
  (int, dx)
  (int, dy)
  )

BOOST_FUSION_ADAPT_STRUCT(
  Parser::Put,
  (char, block_code)
  (int, dx)
  (int, dy)
  )

BOOST_FUSION_ADAPT_STRUCT(
  Parser::Get,
  (int, dx)
  (int, dy)
  )

BOOST_FUSION_ADAPT_STRUCT(
  Parser::ToClientBoolReply,
  (int, r)
  )

BOOST_FUSION_ADAPT_STRUCT(
  Parser::ToClientGetReply,
  (int, block_code)
  )

BOOST_FUSION_ADAPT_STRUCT(
			  Parser::Message,
			  (std::string, sender)
			  (std::string, msg)
			  )


BOOST_FUSION_ADAPT_STRUCT(
			  Parser::Broadcast,
			  (std::string, msg)
			  )

BOOST_FUSION_ADAPT_STRUCT(
			 Parser::FieldOfView,
			 (int, x00)
			 (int, x01)
			 (int, x02)
			 (int, x03)
			 (int, x04)			 
			 (int, x10)
			 (int, x11)
			 (int, x12)
			 (int, x13)
			 (int, x14)
			 (int, x20)
			 (int, x21)
			 (int, x22)
			 (int, x23)
			 (int, x24)
			 (int, x30)
			 (int, x31)
			 (int, x32)
			 (int, x33)
			 (int, x34)
			 (int, x40)
			 (int, x41)
			 (int, x42)
			 (int, x43)
			 (int, x44)
			 )


namespace Parser
{
  template <typename Iterator>
  struct request_rfov : qi::grammar<Iterator, RFieldOfView(), ascii::space_type>
  {
    request_rfov() : request_rfov::base_type(start)
    {
      using qi::int_;
      using qi::lit;
      using qi::lexeme;

      start %= lit("rfov")
	>> '{'
	>> int_  >> ';' >> int_
	>> '}';
    }
    qi::rule<Iterator, RFieldOfView(), ascii::space_type> start;
  };

  template <typename Iterator>
  struct request_fov : qi::grammar<Iterator, FieldOfView(), ascii::space_type>
  {
    request_fov() : request_fov::base_type(start)
    {
      using qi::int_;
      using qi::lit;

      start %= lit("fov")
	>> '{'
	>> int_ >> ';' 
	>> int_ >> ';'
	>> int_ >> ';'
	>> int_ >> ';'
	>> int_ >> ';'
	>> int_ >> ';'
	>> int_ >> ';'
	>> int_ >> ';'
	>> int_ >> ';'
	>> int_ >> ';'
	>> int_ >> ';'
	>> int_ >> ';'
	>> int_ >> ';'
	>> int_ >> ';'
	>> int_ >> ';'
	>> int_ >> ';'
	>> int_ >> ';'
	>> int_ >> ';'
	>> int_ >> ';'
	>> int_ >> ';'
	>> int_ >> ';'
	>> int_ >> ';'
	>> int_ >> ';'
	>> int_ >> ';'
	>> int_
	>> '}';
    }
    qi::rule<Iterator, FieldOfView(), ascii::space_type> start;
  };

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
  struct request_message : qi::grammar<Iterator, Message(), ascii::space_type>
  {
    request_message() : request_message::base_type(start)
    {
      using qi::lit;
      using qi::lexeme;
      using ascii::char_;

      quoted_string %= lexeme['"' >> +(char_ - '"') >> '"'];

      start %= lit("ms")
	>> '{'
	>> quoted_string >> ';'
	>> quoted_string
	>> '}';
    }

    qi::rule<Iterator, std::string(), ascii::space_type> quoted_string;
    qi::rule<Iterator, Message(), ascii::space_type> start;
  };


  template <typename Iterator>
  struct request_broadcast : qi::grammar<Iterator, Broadcast(), ascii::space_type>
  {
    request_broadcast() : request_broadcast::base_type(start)
    {
      using qi::lit;
      using qi::lexeme;
      using ascii::char_;

      quoted_string %= lexeme['"' >> +(char_ - '"') >> '"'];

      start %= lit("mb")
	>> '{'
	>> quoted_string
	>> '}';
    }

    qi::rule<Iterator, std::string(), ascii::space_type> quoted_string;
    qi::rule<Iterator, Broadcast(), ascii::space_type> start;
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

  template <typename Iterator>
  struct request_put : qi::grammar<Iterator, Put(), ascii::space_type>
  {
    request_put() : request_put::base_type(start)
    {
      using qi::int_;
      using ascii::char_;
      using qi::lit;

      start %= lit("put")
  >> '{'
  >> char_ >> ";" >> int_ >> ';' >> int_
  >> '}';
    }

    qi::rule<Iterator, Put(), ascii::space_type> start;
  };

  template <typename Iterator>
  struct request_get : qi::grammar<Iterator, Get(), ascii::space_type>
  {
    request_get() : request_get::base_type(start)
    {
      using qi::int_;
      using qi::lit;

      start %= lit("get")
  >> '{'
  >> int_ >> ';' >> int_
  >> '}';
    }

    qi::rule<Iterator, Get(), ascii::space_type> start;
  };

  template <typename Iterator>
  struct request_toclientboolreply : qi::grammar<Iterator, ToClientBoolReply(), ascii::space_type>
  {
    request_toclientboolreply() : request_toclientboolreply::base_type(start)
    {
      using qi::int_;
      using qi::lit;

      start %= lit("rep")
  >> '{'
  >> int_
  >> '}';
    }

    qi::rule<Iterator, ToClientBoolReply(), ascii::space_type> start;
  };

  template <typename Iterator>
  struct request_toclientgetreply : qi::grammar<Iterator, ToClientGetReply(), ascii::space_type>
  {
    request_toclientgetreply() : request_toclientgetreply::base_type(start)
    {
      using ascii::char_;
      using qi::lit;

      start %= lit("getrep")
  >> '{'
  >> char_
  >> '}';
    }

    qi::rule<Iterator, ToClientGetReply(), ascii::space_type> start;
  };
}

#endif
