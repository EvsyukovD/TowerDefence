#ifndef __EFFECT_H__
#define __EFFECT_H__
#include "TowerDefence.h"
namespace TowerDefence {
	class Effect {
	public:
		enum EffectType {
			POISON, //Отравление
			WEAKNESS, //Слабость
			DECELERATION, //Замедление
			NONE //Ничего не происходит
		};
	protected:
		//длительность эффекта (число ходов)
		int duration = 0; 
		float value = 0;
		EffectType type = Effect::EffectType::NONE;
	public:
		/*
		Конструктор эффекта
		@param duration - длительность эффекта
		@param value - значение эффекта
		@throws std::invalid_argument - При отрицательном duration
		**/
		Effect(int duration, float value, Effect::EffectType type);
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
		/*
		@return Значение эффекта
		**/
		float getValue()const;
	};

	class PoisonEffect : public Effect {
	public:
		PoisonEffect(int duration, float value) : Effect(duration, value, Effect::EffectType::POISON) {}
		/*
		Отравить на врага
		@param e - враг
		**/
		virtual void apply(Enemy& e);
	};
	class WeaknessEffect : public Effect {
	public:
		WeaknessEffect(int duration, float value) : Effect(duration, value, Effect::EffectType::WEAKNESS) {}
		/*
		Ослабить врага
		@param e - враг
		**/
		virtual void apply(Enemy& e) override;
	};
	class DecelerationEffect : public Effect {
	public:
		DecelerationEffect(int duration, float value) : Effect(duration, value, Effect::EffectType::DECELERATION) {}
		/*
		Замедлить врага
		@param e - враг
		**/
		virtual void apply(Enemy& e) override;
	};
}
#endif // !__EFFECT_H__
