#include "../include/Lair.h"
#include "../include/Enemy.h"
#include "../lib/json/single_include/nlohmann/json.hpp"
#include <fstream>
using json = nlohmann::json;
namespace TowerDefence {
    Lair::Lair(const std::vector<Point>& path,const std::string& jsonConfigFile){
        json js;
        std::ifstream file(jsonConfigFile);
        file >> js;
        file.close();
        this->name = js["name"];
        std::string enemyConfig(js["enemy_config"]);
        for (int i = 0; i < js["ticks"].size(); i++) {
            enemyMap.insert_or_assign(js["ticks"][i],new Enemy(path,enemyConfig));
        }
    }
    int Lair::getNumOfEnemies()const {
        return enemyMap.size();
    }
    Enemy* Lair::getNextEnemy(unsigned int t) {
        auto res = enemyMap.find(t);
        if (res != enemyMap.end()) {
            Enemy* e = res->second;
            enemyMap.erase(res);
            return e;
        }
        else {
            return nullptr;
        }
    }
}