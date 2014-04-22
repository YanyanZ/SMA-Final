/*!
 * \file Player.hpp
 * \brief Header for Game Server
 * \author Florian Thomassin
 * \version 1.0
 */

#ifndef Player_HPP
# define Player_HPP

# include <cstdlib>
# include <iostream>

/*!
 * \brief Namespace that contains all servers
 */
namespace Servers
{
  /*!
   * \class Player that containt all Players fonction and data
   */
  class Player
  {

  public:
    /*!
     * \brief Constructor
     * \param user_name : User Name
     * \param pwd : Pass word
     */
    Player(std::string user_name, std::string pwd);
    /*!
     * \brief Destructor
     */
    ~Player(void);

    bool is_user(std::string& u, std::string& p) const;

    int pos_x;
    int pos_y;

    int world_id;

  public:
    std::string user_name;

  private:
    std::string pwd;
  };
}
#endif
