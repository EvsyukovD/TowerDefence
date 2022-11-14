#include "../include/Enemy.h"
#include "../include/Effect.h"
namespace TowerDefence {
    Enemy::Enemy(int maxHealth,
        float speed,
        unsigned int award,
        const std::string& name,
        const std::vector<Point>& path, const std::string& filename): TDObject(filename),MAX_HEALTH(maxHealth) {
        this->health = MAX_HEALTH;
        this->speed = speed;
        this->award = award;
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
    unsigned int Enemy::getAward()const {
        return award;
    }
    std::string Enemy::getName()const {
        return name;
    }
    int Enemy::getNumOfEffects()const {
        return this->effects.size();
    }
    void Enemy::setHealth(int health) {
        this->health = health;
    }
    void Enemy::getDamage(int d) {
        double damage = d;
        for (auto iter = effects.begin(); iter != effects.end(); ++iter) {
            Effect& e = *iter;
            if (e.getType() == Effect::EffectType::WEAKNESS) {
                damage += d * (1.0 - e.getValue() / 100.0);
            }
        }
        health -= (int)floor(damage);
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
        award = e.award;
    }
    bool Enemy::isDead()const {
        return health <= 0 || !object;
    }
    bool Enemy::isOnFinish()const {
        return currentPos == path.size() - 1;
    }
    void Enemy::tick() {
        if (health <= 0) {
            kill();
            return;
        }
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
        if (isOnFinish()) {
            return;
        }
        else {
            double dist = this->object->getPosition().distance(path[currentPos + 1]);
             auto move = MoveBy::create(dist / speed, path[currentPos + 1]);
             object->runAction(move);
             currentPos++;
        }
    }
    Enemy::~Enemy() {
        this->effects.clear();
        this->path.clear();
    }
}