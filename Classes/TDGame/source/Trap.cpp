#include "../include/Trap.h"
namespace TowerDefence {
    Trap::Trap(float radius, 
        const Effect& e, 
        const std::string& name, 
        const std::string& filename) : 
        MagicObject(e),
        AbstractAttackingObject(name, filename) {
        this->radius = radius;
    }
    
    bool Trap::fire(std::map<Point, Enemy>& m) {
        bool isExploded = false;
        for (auto iter = m.begin(); iter != m.end(); ++iter) {
            if ((double)((Point)(iter->first)).distance(this->object->getPosition()) - (double)radius < 1E-32) {
                Enemy& e = (Enemy)(iter->second);
                e.addEffect(this->getEffect());
                isExploded = true;
            }
        }
        return isExploded;
    }
}
