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
# include <boost/algorithm/string.hpp>

# include "../parsers/Parser.hpp"
# include "Player.hpp"

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
  typedef Parser::request_put<iterator_type> PRequest_parser;
  typedef Parser::request_get<iterator_type> GRequest_parser;
  typedef Parser::request_broadcast<iterator_type> BRequest_parser;
  typedef Parser::request_message<iterator_type> SRequest_parser;

  /*!
   * \class Class that containt all Game Server fonction and data
   */
  class Game
  {
  private:
    CRequest_parser cg; /*!< Grammar for Connexion Requests*/
    MRequest_parser mg; /*!< Grammar for Move Requests */
    PRequest_parser pg; /*!< Grammar for Put Requests */
    GRequest_parser gg; /*!< Grammar for Get Requests */
    BRequest_parser bg; /*!< Grammar for Broadcast */
    SRequest_parser sg;

  private:
    Parser::Connexion co; /*!< Connexion structure */
    Parser::Move mv; /*!< Move structure */
    Parser::Put pu; /*!< Put structure */
    Parser::Get ge; /*!< Put structure */
    Parser::Broadcast broad;
    Parser::Message send;

  private:
    const int max_nb_planets; /*!< Maximum number of planets in the game */
    const int max_nb_players; /*!< Maximum number of players in the game */

  private:
    std::vector<Matrix> univers; /*!< Planets pointer */
    // std::vector<Player*> players;
    std::map<std::string, Player*> players;
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
    int create_planet(int i);
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
    bool is_account_exist(std::string ip);

  private:
    void sendmessage(std::string sender, std::string msg, udp::socket& sock);
    void broadcast(std::string from, std::string msg);

  private:
    /*!
     * \brief Parse the request send by the user
     * \param line : The string to parse
     * \return "fail" or "ok"
     */
    int parse_request(std::string& line, std::string& ip, udp::socket& sock);
    std::string exec_request(std::string line, std::string ip, std::string port, udp::socket& sock);

  private:
    void update_users_page(void);

  public:
    /*!
     * \brief Start Game Server
     */
    void run(void);
  };
}
#endif
