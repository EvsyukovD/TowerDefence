#include "../include/Effect.h"
#include "../include/Enemy.h"
namespace TowerDefence {
	Effect::Effect() {
		
	}
	Effect::Effect(int duration, float value, Effect::EffectType type) {
		if (duration < 0) {
			throw std::invalid_argument("duration can't be negative");
		}
		this->duration = duration;
		this->value = value;
		this->type = type;
	}
	Effect::EffectType Effect::getType() const {
		return type;
	}
	int Effect::getDuration()const {
		return duration;
	}
	float Effect::getValue()const {
		return value;
	}
	void Effect::apply(Enemy&) {
		if (duration > 0) {
			duration--;
			return;
		}
	}
	void PoisonEffect::apply(Enemy& e) {
		if (duration <= 0) {
			return;
		}
		e.setHealth(e.getHealth() * (1 - value));
		duration--;
	}
	void WeaknessEffect::apply(Enemy& e) {
		if (duration <= 0) {
			return;
		}
		duration--;
	}
	void DecelerationEffect::apply(Enemy& e) {
		if (duration <= 0) {
			e.setSpeed(e.getNativeSpeed());
			return;
		}
		e.setSpeed(e.getNativeSpeed() * (1 - value));
		duration--;
	}
}