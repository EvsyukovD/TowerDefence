#ifndef __LAIR_H__
#define __LAIR_H__
#include "Building.h"
namespace TowerDefence {
    class Lair:public Building {
    private:
        std::map<unsigned int, Enemy*> enemyMap;
    public:
        Lair(const std::vector<Point>&,const std::string& jsonConfigFile);
        /**
         * \brief Release next enemy
         * 
         * \param current tick
         * \return Enemie's ptr or nullptr if time isn't come
         */
        Enemy* getNextEnemy(unsigned int);
        /**
         * \return Num of enemies in this lair 
         */
        int getNumOfEnemies()const;
    };
}
#endif //!__LAIR_H__