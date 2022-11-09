#include "../include/Enemy.h"
#include "../include/Effect.h"
namespace TowerDefence {
    Enemy::Enemy(int maxHealth,
        float speed,
        const std::string& name,
        const std::vector<Point>& path, const std::string& filename): TDObject(filename),MAX_HEALTH(maxHealth) {
        this->health = MAX_HEALTH;
        this->speed = speed;
        this->name = name;
        this->path = path;
        this->currentPos = 0;
        this->object->setPosition(path[currentPos]);
    }
    int Enemy::getHealth()const {
        return health;
    } 
    float Enemy::getSpeed()const {
        return speed;
    }
    std::string Enemy::getName()const {
        return name;
    }
    int Enemy::getNumOfEffects()const {
        this->effects.size();
    }
    void Enemy::setHealth(int health) {
        this->health;
    }
    void Enemy::setName(const std::string& name) {
        this->name = name;
    }
    void Enemy::setSpeed(float speed) {
        if (speed < 0) {
            throw std::invalid_argument("speed can't be negative");
        }
        this->speed = speed;
    }
    void Enemy::addEffect(const Effect& e) {
        effects.push_back(e);
    }

    Enemy::Enemy(const Enemy& e):TDObject(static_cast<const TDObject&>(e)), MAX_HEALTH(e.MAX_HEALTH) {
        health = e.health;
        speed = e.speed;
        name = e.name;
        path = e.path;
        effects = e.effects;
    }
    bool Enemy::isDead()const {
        return health <= 0 || !object;
    }
    void Enemy::tick() {
        for (auto iter = effects.begin(); iter != effects.end();++iter) {
             Effect& e = *iter;
             e.apply(*this);
             if (e.getDuration() == 0) {
                 effects.erase(iter);
             }
             if (health <= 0) {
                 kill();
             }
        }
        if (currentPos == path.size() - 1) {
            kill();
        }
        else {
            double dist = this->object->getPosition().distance(path[currentPos + 1]);
             auto move = MoveBy::create(dist / speed, path[currentPos + 1]);
             object->runAction(move);
             currentPos++;
        }
    }
    
}