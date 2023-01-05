#include "../include/Tower.h"
#include "../lib/json/single_include/nlohmann/json.hpp"
#include <fstream>
using json = nlohmann::json;
namespace TowerDefence {
    Tower::Tower(const Point& palacePos,const Point& towerPos,const std::string& jsonConfig): s(palacePos,towerPos){
        json js;
        std::ifstream file(jsonConfig);
        file >> js;
        file.close();
        object->initWithFile(js["sprite"]);
        object->setScale(js["tower_scale"]);
        TowerProperties p;
        std::string level;
        for (int i = 0; i < MAX_LEVEL; i++) {
            level = "level_";
            level = level.append(std::to_string(i));
            p.cost = js[level]["cost"];
            p.damage = js[level]["damage"];
            p.radius = js[level]["radius"];
            p.rateOfFire = js[level]["rate_of_fire"];
            p.updatingCost = js[level]["updating_cost"];
            properties.insert_or_assign(i + 1, p);
        }
    }
    TowerProperties Tower::getProperties()const {
        return properties.at(level);
    }
    Tower::TargetSheduler::TargetSheduler(const Point& palacePos,
        const Point& towerPos): 
        palacePos(palacePos),
        towerPos(towerPos) {}
    
    void Tower::TargetSheduler::shedule(Enemy* e) {
        if (!enemy || enemy->isDead()) {
            enemy = e;
            return;
        }
        double distToTowerTarget = enemy->getSprite()->getPosition().distance(towerPos);
        double distToTowerInputEnemy = e->getSprite()->getPosition().distance(towerPos);
        if (distToTowerTarget - distToTowerInputEnemy < 1E-32) {
            enemy = e;
            return;
        }
        double distToPalaceTarget = enemy->getSprite()->getPosition().distance(palacePos);
        double distToPalaceInputEnemy = e->getSprite()->getPosition().distance(palacePos);
        if (distToPalaceTarget - distToPalaceInputEnemy < 1E-32) {
            enemy = e;
            return;
        }
        if (enemy->getHealth() > e->getHealth()) {
            enemy = e;
            return;
        }
        if (enemy->getHealth() < e->getHealth()) {
            enemy = e;
            return;
        }
        if ((double)e->getSpeed() - (double)enemy->getSpeed() > 1E-32) {
            enemy = e;
            return;
        }
    }
    Tower::TargetSheduler::TargetSheduler(const TargetSheduler& s):palacePos(s.palacePos), towerPos(s.towerPos) {
        enemy = s.enemy;
    }
    Tower::Tower(const Tower& t):s(t.s),properties(t.properties),level(t.level) {
    }
    Enemy* Tower::TargetSheduler::operator()() {
        return enemy;
    }
    void Tower::TargetSheduler::dropShedule() {
        enemy = nullptr;
    }
    void Tower::dropTarget() {
        this->s.dropShedule();
    }
    Enemy* Tower::getTarget() {
        return this->s();
    }
    unsigned int Tower::getLevel()const {
        return level;
    }
    bool Tower::updateLevel(unsigned int gold) {
        if (level == MAX_LEVEL) {
            return true;
        }
        if (gold >= properties.at(level).updatingCost) {
            level++;
            return true;
        }
        return false;
    }
    bool Tower::fire(std::list<Enemy*>& enemies) {
        for (auto iter = enemies.begin(); iter != enemies.end(); ++iter) {
            const Point& p = (*iter)->getSprite()->getPosition();
            if ((double)p.distance(this->object->getPosition()) - (double)properties.at(level).radius < 1E-32) {
                s.shedule(*iter);
            }
        }
        Enemy* target = s();
        if (target) {
            for (unsigned int i = 0; i < properties.at(level).rateOfFire; i++) {
                if (target->isDead()) {
                    this->dropTarget();
                    return true;
                }
                target->getDamage(properties.at(level).damage);
            }
            return true;
        }
        return false;
    }
    MagicTower::MagicTower(const Effect& e, 
        const Point& palacePos,
        const Point& towerPos, 
        const std::string& jsonConfig):
        MagicObject(e),
        Tower(palacePos,towerPos,jsonConfig) {}

    bool MagicTower::fire(std::list<Enemy*>& enemies) {
        for (auto iter = enemies.begin(); iter != enemies.end(); ++iter) {
            const Point& p = (*iter)->getSprite()->getPosition();
            if ((double)p.distance(this->object->getPosition()) - (double)properties.at(level).radius < 1E-32) {
                s.shedule(*iter);
            }
        }
        Enemy* target = s();
        if (target) {
            target->addEffect(this->getEffect());
            for (unsigned int i = 0; i < properties.at(level).rateOfFire; i++) {
                if (target->isDead()) {
                    return true;
                }
                target->getDamage(properties.at(level).damage);
            }
            return true;
        }
        return false;
    }
}