#include "../include/MagicObject.h"
#include "../include/Effect.h"
namespace TowerDefence {
    Effect* MagicObject::getEffect() const{
        switch (effect.getType()) {
        case Effect::EffectType::NONE:
            return new Effect(effect.getDuration(), effect.getValue(), Effect::EffectType::NONE);
        case Effect::EffectType::DECELERATION:
            return new DecelerationEffect(effect.getDuration(), effect.getValue());
        case Effect::EffectType::WEAKNESS:
            return new WeaknessEffect(effect.getDuration(), effect.getValue());
        case Effect::EffectType::POISON:
            return new PoisonEffect(effect.getDuration(), effect.getValue());
        }
    }
    void MagicObject::setEffect(const Effect& e) {
        effect = e;
    }
    MagicObject::MagicObject(const Effect& e) {
        effect = e;
    }
}