/*!
 * \file Player.hpp
 * \brief Header for Game Server
 * \author Florian Thomassin
 * \version 1.0
 */

#ifndef Player_HPP
# define Player_HPP

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

using boost::asio::ip::udp;

/*!
 * \brief Namespace that contains all servers
 */
namespace Servers
{
  /*!
   * \class Class that containt all Game Server fonction and data
   */
  class Player
  {

  public:
    /*!
     * \brief Constructor
     * \param p : Server port
     * \param mnplan : Maximum number of planets
     * \param mnplay : Maximum number of players
     */
    Player(std::string user_name, std::string pwd);
    /*!
     * \brief Destructor
     */
    ~Player(void);

  private:
    std::string user_name;
    std::string pwd;

    int pos_x;
    int pos_y;
  };
}
#endif
