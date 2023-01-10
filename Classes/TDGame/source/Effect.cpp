#include "../include/Effect.h"
#include "../include/Enemy.h"
#include "../lib/json/single_include/nlohmann/json.hpp"
using json = nlohmann::json;
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
	void Effect::setType(Effect::EffectType type) {
		this->type = type;
	}
	Effect::EffectType Effect::getType() const {
		return type;
	}
	int Effect::getDuration()const {
		return duration;
	}
	Effect::EffectType Effect::getType(int type) {
		switch (type) {
		case 0:
			return Effect::EffectType::POISON;
		case 1:
			return Effect::EffectType::WEAKNESS;
		case 2:
			return Effect::EffectType::DECELERATION;
		case 3:
			return Effect::EffectType::NONE;
		default:
			return Effect::EffectType::NONE;
		}
	}
	std::string Effect::to_string(Effect::EffectType type) {
		switch (type)
		{
		case TowerDefence::Effect::POISON:
			return "poison";
		case TowerDefence::Effect::WEAKNESS:
			return "weakness";
		case TowerDefence::Effect::DECELERATION:
			return "deceleration";
		case TowerDefence::Effect::NONE:
			return "none";
		default:
			return "none";
		}
	}
	Color3B Effect::getColorOfEffect(Effect::EffectType type) {
		switch (type)
		{
		case Effect::POISON:
			return Color3B::GREEN;
		case Effect::WEAKNESS:
			return Color3B::RED;
		case Effect::DECELERATION:
			return Color3B::BLUE;
		case Effect::NONE:
			return Color3B::BLACK;
		default:
			return Color3B::BLACK;
		}
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
		if (duration > 0) {
			e.setHealth(floor(e.getHealth() * (1 - value)));
			duration--;
		}
		if (duration == 0) {
			return;
		}
	}
	void WeaknessEffect::apply(Enemy& e) {
		if (duration > 0) {
			duration--;
		}
		if (duration == 0) {
			return;
		}
	}
	void DecelerationEffect::apply(Enemy& e) {
		if (duration > 0) {
			e.setSpeed(floor(e.getNativeSpeed() * (1 - value)));
			duration--;
		}
		if(duration == 0) {
			e.setSpeed(e.getNativeSpeed());
			return;
		}
	}
}