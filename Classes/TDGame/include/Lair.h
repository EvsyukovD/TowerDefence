#ifndef __LAIR_H__
#define __LAIR_H__
#include "Building.h"
namespace TowerDefence {
    class Lair {
    private:
        std::map<unsigned int, Enemy> enemyMap;
    public:
        Lair(const std::map<unsigned int, Enemy>&);
        Enemy& getNextEnemy(unsigned int);
        Enemy& getNextEnemy();
        int getNumOfEnemies()const;
    };
}
#endif