#include "../include/Tower.h"
namespace TowerDefence {
    Tower::Tower(const Point& palacePos,
        const std::string& name, 
        const std::string& filename) : 
        AbstractAttackingObject(name, filename), 
        s(palacePos,object->getPosition()) {
    
       //загрузка из конфига
        TowerProperties p(100, 100, 5, 1);
        for (int i = 1; i <= MAX_LEVEL;i++) {
            this->properties.insert({ i, TowerProperties(p.damage * i, p.cost + 2 * i, p.radius + (float)i, i) });
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
        const std::string& name,
        const std::string& filename):MagicObject(e), Tower(palacePos,name,filename) {}
    
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