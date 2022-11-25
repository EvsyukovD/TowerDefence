#ifndef __LAIR_H__
#define __LAIR_H__
#include "Building.h"
namespace TowerDefence {
    class Lair:public Building {
    private:
        std::map<unsigned int, std::shared_ptr<Enemy>> enemyMap;
    public:
        Lair(const std::vector<Point>&,const std::string& jsonConfigFile);
        std::shared_ptr<Enemy> getNextEnemy(unsigned int);
        int getNumOfEnemies()const;
    };
}
#endif //!__LAIR_H__