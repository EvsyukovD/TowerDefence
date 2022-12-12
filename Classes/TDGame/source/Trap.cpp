#include "../include/Trap.h"
namespace TowerDefence {
    Trap::Trap(float radius, 
        int cost,
        const Effect& e, 
        const std::string& name, 
        const std::string& filename) : 
        MagicObject(e),
        AbstractAttackingObject(name, filename) {
        this->radius = radius;
        this->cost = cost;
    }
    bool Trap::fire(std::list<Enemy*>& m) {
        bool isExploded = false;
        for (auto iter = m.begin(); iter != m.end(); ++iter) {
            const Point& p = (*iter)->getSprite()->getPosition();
            if ((double)p.distance(this->object->getPosition()) - (double)radius < 1E-32) {
                
                (*iter)->addEffect(this->getEffect());
                isExploded = true;
            }
        }
        if (isExploded) {
            kill();
        }
        return isExploded;
    }
    int Trap::getCost()const {
        return cost;
    }
    float Trap::getRadius() const {
        return radius;
    }
}
