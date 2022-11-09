#include "../include/MagicObject.h"
#include "../include/Effect.h"
namespace TowerDefence {
    Effect MagicObject::getEffect() const{
        return effect;
    }
    void MagicObject::setEffect(const Effect& e) {
        effect = e;
    }
    MagicObject::MagicObject(const Effect& e) {
        effect = e;
    }
}