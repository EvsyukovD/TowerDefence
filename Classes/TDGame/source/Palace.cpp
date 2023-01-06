#include "../include/Palace.h"
namespace TowerDefence {
    Palace::Palace(const std::string& name, 
        const std::string& filename,
        unsigned int gold, 
        unsigned int maxStrength): 
        Building(name,filename),
        gold(gold),
        currentStrength(maxStrength),
        maxStrength(maxStrength){
    }
    Palace::Palace(){
        gold = 0;
        currentStrength = 0;
        maxStrength = 0;
    }
    unsigned int Palace::getGold()const {
        return gold;
    }
    unsigned int Palace::getStrength() const {
        return currentStrength;
    }
    void Palace::addGold(unsigned int g) {
        this->gold += g;
    }
    bool Palace::takeGold(unsigned int gold) {
        if (gold <= this->gold) {
            this->gold -= gold;
            return true;
        }
        else {
            return false;
        }
    }
    void Palace::getDamage(unsigned int d) {
        if (this->currentStrength >= d) {
            this->currentStrength -= d;
        }
        else {
            this->currentStrength = 0;
        }
    }
    bool Palace::isDestroyed() const{
        return currentStrength == 0;
    }
    void Palace::init(unsigned int gold,unsigned int maxStrength,const Point& pos) {
        this->maxStrength = maxStrength;
        this->gold = gold;
        this->currentStrength = maxStrength;
        this->object->setPosition(pos);
    }
}