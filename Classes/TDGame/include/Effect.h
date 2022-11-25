#ifndef __EFFECT_H__
#define __EFFECT_H__
#include "TowerDefence.h"
namespace TowerDefence {
	class Effect {
	public:
		enum EffectType {
			POISON, //����������
			WEAKNESS, //��������
			DECELERATION, //����������
			NONE //������ �� ����������
		};
	protected:
		//������������ ������� (����� �����)
		int duration = 0; 
		float value = 0;
		EffectType type = Effect::EffectType::NONE;
	public:
		/*
		����������� �������
		@param duration - ������������ �������
		@param value - �������� �������
		@throws std::invalid_argument - ��� ������������� duration
		**/
		Effect(int duration, float value, Effect::EffectType type);
		Effect();
		/*!
		\brief ������� ����������� �� �����
		\param e - ����
		*/
		virtual void apply(Enemy& e);
		/*!
		@return ��� �������
		**/
		EffectType getType() const;
		/*!
		\return ����������������� �������
		**/
		int getDuration() const;
		/*!
		\return �������� �������
		*/
		float getValue()const;
	};

	class PoisonEffect : public Effect {
	public:
		PoisonEffect(int duration, float value) : Effect(duration, value, Effect::EffectType::POISON) {}
		/*!
		\brief �������� �� �����
		\param e - ����
		*/
		virtual void apply(Enemy& e);
	};
	class WeaknessEffect : public Effect {
	public:
		WeaknessEffect(int duration, float value) : Effect(duration, value, Effect::EffectType::WEAKNESS) {}
		/*
		�������� �����
		@param e - ����
		**/
		virtual void apply(Enemy& e) override;
	};
	class DecelerationEffect : public Effect {
	public:
		DecelerationEffect(int duration, float value) : Effect(duration, value, Effect::EffectType::DECELERATION) {}
		/*
		��������� �����
		@param e - ����
		**/
		virtual void apply(Enemy& e) override;
	};
}
#endif // !__EFFECT_H__
