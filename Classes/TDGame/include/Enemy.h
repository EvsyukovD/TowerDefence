#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "TDObject.h"
namespace TowerDefence {
	class Enemy : public TDObject{
	private:
		  int health;
		  float speed;
		  std::list<Effect> effects;
		  std::string name;
		  std::vector<Point> path;
		  int currentPos;
	public:
		const int MAX_HEALTH;
		Enemy(int maxHealth,
			float speed,
			const std::string& name,
			const std::vector<Point>& path, const std::string& filename);
		
		Enemy(const Enemy&);
		/*
		@return ����, ��� ���� ����
		**/
		bool isDead()const;
		/*
		������� ������� �������� �����
		@return ������� ��������
		**/
		int getHealth()const;
		/*
		���������� ������� �������� �����
		**/
		void setHealth(int);
		/*
		������� ������� �������� �����
		@return ������� ��������
		**/
		float getSpeed()const;
		/*
		���������� ������� �������� �����
		@param ����� �������� ��������
		@throws std::invalid_argument - ��� ������������� ��������
		**/
		void setSpeed(float);
		/*
		�������� ������ �����
		@param ������������� ������
		**/
		void addEffect(const Effect&);
		/*
		������� ���  �����
		@return ��� �����
		**/
		std::string getName()const;
		/*
		���������� ��� �����
		**/
		void setName(const std::string&);
		/*
		�������� ���������� ��������
		@return ���-�� ��������
		**/
		int getNumOfEffects()const;
		/*
		������� ��� � ���������� ��������
		**/
		void tick();
	};
}
#endif // !__ENEMY_H__