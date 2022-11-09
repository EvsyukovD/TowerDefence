#ifndef __EFFECT_H__
#define __EFFECT_H__
#include "TowerDefence.h"
namespace TowerDefence {
	enum EffectType {
		POISON, //Отравление
		WEAKNESS, //Слабость
		DECELERATION, //Замедление
		NONE //Ничего не происходит
	};
	class Effect {
	protected:
		//длительность эффекта (число ходов)
		int duration; 
		float value;
		EffectType type;
	public:
		/*
		Конструктор эффекта
		@param duration - длительность эффекта
		@param value - значение эффекта
		@throws std::invalid_argument - При отрицательном duration
		**/
		Effect(int duration, float value, EffectType type);
		Effect();
		/*
		Оказать воздействие на врага
		@param e - враг
		**/
		virtual void apply(Enemy& e);
		/*
		@return тип эффекта
		**/
		EffectType getType() const;
		/*
		@return продолжительность эффекта
		**/
		int getDuration() const;
	};

	class PoisonEffect : public Effect {
	public:
		PoisonEffect(int duration, float value) : Effect(duration, value, EffectType::POISON) {}
		/*
		Отравить на врага
		@param e - враг
		**/
		virtual void apply(Enemy& e);
	};
	class WeaknessEffect : public Effect {
	public:
		WeaknessEffect(int duration, float value) : Effect(duration, value, EffectType::WEAKNESS) {}
		/*
		Ослабить врага
		@param e - враг
		**/
		virtual void apply(Enemy& e) override;
	};
	class DecelerationEffect : public Effect {
	public:
		DecelerationEffect(int duration, float value) : Effect(duration, value, EffectType::DECELERATION) {}
		/*
		Замедлить врага
		@param e - враг
		**/
		virtual void apply(Enemy& e) override;
	};
}
#endif // !__EFFECT_H__
