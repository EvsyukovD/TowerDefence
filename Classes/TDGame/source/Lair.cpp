#include "../include/Lair.h"
namespace TowerDefence {
    Lair::Lair(const std::string& jsonConfigFile,const std::string& name,
        const std::string& filename):Building(name,filename) {/*Загрузка врагов из конфига*/}
    int Lair::getNumOfEnemies()const {
        return enemyMap.size();
    }
    std::shared_ptr<Enemy> Lair::getNextEnemy(unsigned int t) {
        auto res = enemyMap.find(t);
        if (res != enemyMap.end()) {
            std::shared_ptr<Enemy> e = (res->second);
            enemyMap.erase(res);
            return e;
        }
        else {
            return nullptr;
        }
    }
}