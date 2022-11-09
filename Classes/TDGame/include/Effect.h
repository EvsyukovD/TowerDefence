#ifndef __EFFECT_H__
#define __EFFECT_H__
#include "TowerDefence.h"
namespace TowerDefence {
	enum EffectType {
		POISON, //����������
		WEAKNESS, //��������
		DECELERATION, //����������
		NONE //������ �� ����������
	};
	class Effect {
	protected:
		//������������ ������� (����� �����)
		int duration; 
		float value;
		EffectType type;
	public:
		/*
		����������� �������
		@param duration - ������������ �������
		@param value - �������� �������
		@throws std::invalid_argument - ��� ������������� duration
		**/
		Effect(int duration, float value, EffectType type);
		Effect();
		/*
		������� ����������� �� �����
		@param e - ����
		**/
		virtual void apply(Enemy& e);
		/*
		@return ��� �������
		**/
		EffectType getType() const;
		/*
		@return ����������������� �������
		**/
		int getDuration() const;
	};

	class PoisonEffect : public Effect {
	public:
		PoisonEffect(int duration, float value) : Effect(duration, value, EffectType::POISON) {}
		/*
		�������� �� �����
		@param e - ����
		**/
		virtual void apply(Enemy& e);
	};
	class WeaknessEffect : public Effect {
	public:
		WeaknessEffect(int duration, float value) : Effect(duration, value, EffectType::WEAKNESS) {}
		/*
		�������� �����
		@param e - ����
		**/
		virtual void apply(Enemy& e) override;
	};
	class DecelerationEffect : public Effect {
	public:
		DecelerationEffect(int duration, float value) : Effect(duration, value, EffectType::DECELERATION) {}
		/*
		��������� �����
		@param e - ����
		**/
		virtual void apply(Enemy& e) override;
	};
}
#endif // !__EFFECT_H__
