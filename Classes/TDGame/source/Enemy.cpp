#include "../include/Enemy.h"
#include "../include/Effect.h"
#include "../lib/json/single_include/nlohmann/json.hpp"
#include <fstream>
using json = nlohmann::json;
namespace TowerDefence {
    Enemy::Enemy(int maxHealth,
        float speed,
        unsigned int award,
        const std::string& name,
        const std::vector<Point>& path, const std::string& filename): TDObject(filename),MAX_HEALTH(maxHealth) {
        this->health = MAX_HEALTH;
        this->nativeSpeed = speed;
        this->speed = speed;
        this->award = award;
        this->name = name;
        this->path = path;
        this->currentPos = 0;
        this->object->setPosition(path[currentPos]);
    }
    Enemy::Enemy(const std::vector<Point>& path,const std::string& jsonConfig):path(path) {
        json js;
        std::ifstream file(jsonConfig);
        file >> js;
        file.close();
        MAX_HEALTH = js["max_health"];
        health = MAX_HEALTH;
        award = js["award"];
        name = js["name"];
        nativeSpeed = js["native_speed"];
        speed = nativeSpeed;
        object->initWithFile(js["frames"][0]);
        object->setScale(js["enemy_scale"]);//0.65
        object->setVisible(true);
        /*Vector<SpriteFrame*> animFrames;
        animFrames.reserve(js["frames"].size());
        Rect r = Rect(js["rect"][0], js["rect"][1], js["rect"][2], js["rect"][3]);
        for (int i = 0; i < js["frames"].size(); i++) {
            animFrames.pushBack(SpriteFrame::create(js["frames"][i], r));
        }
        Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
        Animate* animate = Animate::create(animation);
        object->runAction(RepeatForever::create(animate));*/
        currentPos = 0;
        object->setPosition(path[currentPos]);
        Label* label = Label::createWithSystemFont(std::to_string(health), "Arial", 20);
        float p = 0.5;
        label->setPosition(path[currentPos].x,path[currentPos].y * (p + 1.0));
        object->addChild(label, 10000,"hp");
    }
    int Enemy::getHealth()const {
        return health;
    } 
    float Enemy::getSpeed()const {
        return speed;
    }
    float Enemy::getNativeSpeed()const {
        return nativeSpeed;
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
            Effect* e = *iter;
            if (e->getType() == Effect::EffectType::WEAKNESS) {
                damage += d * (1.0 - e->getValue() / 100.0);
            }
        }
        health -= (int)floor(damage);
        Label* l = (Label*) object->getChildByName("hp");
        l->setString(std::to_string(health));
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
    void Enemy::addEffect(Effect* e) {
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
        bool increment;
        for (auto iter = effects.begin(); iter != effects.end();) {
            Effect* e = *iter;
            increment = true;
            e->apply(*this);
            if (e->getDuration() == 0) {
                iter = effects.erase(iter);
                delete e;
                increment = false;
            }
            if (health <= 0) {
                kill();
                return;
            }
            if (increment) {
                ++iter;
            }
        }
        if (isOnFinish()) {
            kill();
            return;
        }
        else if(object->getReferenceCount() > 0){
            int d = floor(speed);
            currentPos = d + currentPos >= path.size() ? path.size() - 1 : currentPos + d;
            object->setPosition(path[currentPos]);
        }
    }
    Enemy::~Enemy() {
        this->effects.clear();
        this->path.clear();
    }
}