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
		EffectType type;
	public:
		/**  
		Effect constructor
		\param duration - duration
		\param value - effect value
		\throws std::invalid_argument - if duration less than zero
		*/
		Effect(int duration, float value, Effect::EffectType type = EffectType::NONE);
		Effect();
		/*!
		\brief Apply to enemy
		\param e - враг
		*/
		virtual void apply(Enemy& e);
		/*!
		\return Effect type
		**/
		EffectType getType() const;
		/*!
		\return Duration of effect
		**/
		int getDuration() const;
		/*!
		\return Value of effect
		*/
		float getValue()const;
		void setType(Effect::EffectType type);
		static Effect::EffectType getType(int type);
	};

	class PoisonEffect : public Effect {
	public:
		PoisonEffect(int duration, float value) : Effect(duration, value, Effect::EffectType::POISON) {}
		/*!
		\brief Poison enemy
		\param e - enemy
		*/
		virtual void apply(Enemy& e);
	};
	class WeaknessEffect : public Effect {
	public:
		WeaknessEffect(int duration, float value) : Effect(duration, value, Effect::EffectType::WEAKNESS) {}
		/*
		\brief Weak the enemy
		\param e - enemy
		**/
		virtual void apply(Enemy& e) override;
	};
	class DecelerationEffect : public Effect {
	public:
		DecelerationEffect(int duration, float value) : Effect(duration, value, Effect::EffectType::DECELERATION) {}
		/**
		\brief Decelerate enemy
		\param e - enemy
		*/
		virtual void apply(Enemy& e) override;
	};
}
#endif // !__EFFECT_H__
