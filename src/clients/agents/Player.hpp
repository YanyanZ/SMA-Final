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
# include <ctime>
# include <vector>
# include <map>

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

    std::string get_action(void);
    void action_result(std::string ret);

    int pos_x;
    int pos_y;

    int world_id;

    std::string user_name;
    std::string pwd;

  private:
    // int state;
    std::pair<int, int> dst;

    int req_type;
    std::vector<int> req_params;

    std::map<char, int> inventory;

    std::pair<int, int> get_move(void);
    void dump_inventory(void);
  };
}
#endif
