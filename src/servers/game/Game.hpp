/*!
 * \file Game.hpp
 * \brief Header for Game Server
 * \author Florian Thomassin
 * \version 1.0
 */

#ifndef GAME_HPP
# define GAME_HPP

# include <vector>
# include <tuple>
# include <map>
# include <cstdlib>
# include <iostream>
# include <algorithm>

# include <boost/asio.hpp>
# include <boost/config/warning_disable.hpp>

# include <boost/spirit/include/qi.hpp>
# include <boost/spirit/include/phoenix_core.hpp>
# include <boost/spirit/include/phoenix_operator.hpp>
# include <boost/spirit/include/phoenix_object.hpp>
# include <boost/fusion/include/adapt_struct.hpp>
# include <boost/fusion/include/io.hpp>

# include "../parsers/Parser.hpp"

using boost::asio::ip::udp;

enum { max_length = 1024 };

/*!
 * \brief Namespace that contains all servers
 */
namespace Servers
{
  typedef unsigned char uchar;
  // typedef std::vector<std::vector<uchar> > Cube;
  typedef std::vector<std::vector<std::pair<uchar, Player*> > > Matrix;

  using boost::spirit::ascii::space;
  typedef std::string::const_iterator iterator_type;
  typedef Parser::request_connexion<iterator_type> CRequest_parser;
  typedef Parser::request_move<iterator_type> MRequest_parser;

  /*!
   * \class Class that containt all Game Server fonction and data
   */
  class Game
  {
  private:
    CRequest_parser cg; /*!< Grammar for Connexion Requests*/
    MRequest_parser mg; /*!< Grammar for Move Requests */

  private:
    Parser::Connexion co; /*!< Connexion structure */
    Parser::Move mv; /*!< Move structure */

  private:
    const int max_nb_planets; /*!< Maximum number of planets in the game */
    const int max_nb_players; /*!< Maximum number of players in the game */

  private:
    std::vector<Matrix> univers; /*!< Planets pointer */
    std::vector<Player*> players;
//    std::map<std::string, std::tuple<std::string, BagDescriptor, PlayerInfo>
//	     accounts; /*<! Account list and players info */

  private:
    unsigned short port; /*<! Server port */
    boost::asio::io_service io_service; /*!< IO service */

  public:
    /*!
     * \brief Constructor
     * \param p : Server port
     * \param mnplan : Maximum number of planets
     * \param mnplay : Maximum number of players
     */
    Game(unsigned short p, const int mnplan, const int mnplay);
    /*!
     * \brief Destructor
     */
   ~Game(void);

  private:
    /*!
     * \brief Load planets from files
     * \param files : Planete Data files
     */
    void load_planets(void);
    /*!
     * \brief Loads accounts informations
     * \param file : XML file that contains player's accounts
     */
    void load_accounts(std::string file);

  private:
    /*!
     * \brief Test if an account exist
     * \param u : Username
     * \param p : Password
     * \return true if the accound is found, false otherwise
     */
    bool is_account_exist(std::string u, std::string p);

  private:
    /*!
     * \brief Parse the request send by the user
     * \param line : The string to parse
     * \return "fail" or "ok"
     */
    std::string parse_request(std::string line);

  private:
    void update_users(void);

  public:
    /*!
     * \brief Start Game Server
     */
    void run(void);
  };
}
#endif
