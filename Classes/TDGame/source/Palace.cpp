#include "../include/Palace.h"
namespace TowerDefence {
    Palace::Palace(const std::string& name, 
        const std::string& filename, 
        unsigned int gold, 
        unsigned int maxStrength): 
        Building(name,filename),
        gold(gold),
        currentStrength(maxStrength),
        MAX_STRENGTH(maxStrength){
        //загрузка из конфига
    }
    Palace::Palace():Palace("NONE","NONE",0,0){}
    unsigned int Palace::getGold()const {
        return gold;
    }
    unsigned int Palace::getStrength() const {
        return currentStrength;
    }
    void Palace::addGold(unsigned int g) {
        this->gold += g;
    }
    void Palace::takeGold(unsigned int gold) {
        if (gold <= this->gold) {
            this->gold -= gold;
        }
        else {
            throw std::invalid_argument("Doesn't have enough gold");
        }
    }
    void Palace::getDamage(unsigned int d) {
        this->currentStrength -= d;
    }
    bool Palace::isDestroyed() const{
        return currentStrength <= 0;
    }
}