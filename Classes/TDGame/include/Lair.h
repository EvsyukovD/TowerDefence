#ifndef __LAIR_H__
#define __LAIR_H__
#include "Building.h"
namespace TowerDefence {
    class Lair:public Building {
    private:
        std::map<unsigned int, Enemy*> enemyMap;
    public:
        Lair(const std::string& name,const std::string& filename);
        Enemy* getNextEnemy(unsigned int);
        int getNumOfEnemies()const;
    };
}
#endif //!__LAIR_H__