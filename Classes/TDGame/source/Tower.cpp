#include "../include/Tower.h"
namespace TowerDefence {
    Tower::Tower(const Point& palacePos,
        const std::string& name, 
        const std::string& filename) : 
        AbstractAttackingObject(name, filename), 
        s(palacePos,object->getPosition()) {
    
       //загрузка из конфига
    }

    TowerProperties Tower::getProperties()const {
        return properties.at(level);
    }
    Tower::TargetSheduler::TargetSheduler(const Point& palacePos,const Point& towerPos): palacePos(palacePos),towerPos(towerPos) {}
    void Tower::TargetSheduler::shedule(Enemy* e) {
        if (!enemy || enemy->getHealth() <= 0) {
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
    void Tower::updateLevel() {
        if (level == MAX_LEVEL) {
            return;
        }
        level++;
    }
    bool Tower::fire(std::map<Point, Enemy>& enemies) {
        for (auto iter = enemies.begin(); iter != enemies.end(); ++iter) {
            Point& p = (Point&)iter->first;
            if ((double)p.distance(this->object->getPosition()) - (double)properties.at(level).radius < 1E-32) {
                s.shedule(&enemies.at(p));
            }
        }
        Enemy* target = s();
        if (target) {
            target->setHealth(target->getHealth() - properties.at(level).damage);
            return true;
        }
        return false;
    }
    MagicTower::MagicTower(const Effect& e,
        const Point& palacePos,
        const std::string& name,
        const std::string& filename):MagicObject(e), Tower(palacePos,name,filename) {}
    
    bool MagicTower::fire(std::map<Point, Enemy>& enemies) {
        for (auto iter = enemies.begin(); iter != enemies.end(); ++iter) {
            Point& p = (Point&)iter->first;
            if ((double)p.distance(this->object->getPosition()) - (double)properties.at(level).radius < 1E-32) {
                s.shedule(&enemies.at(p));
            }
        }
        Enemy* target = s();
        if (target) {
            target->addEffect(this->getEffect());
            return true;
        }
        return false;
    }
}