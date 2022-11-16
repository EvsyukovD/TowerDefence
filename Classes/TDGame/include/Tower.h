#ifndef __TOWER_H__
#define __TOWER_H__
#include "AbstractAttackingObject.h"
#include "MagicObject.h"
namespace TowerDefence {
	struct TowerProperties {
		int damage;
		unsigned int cost;
		float radius;
		unsigned int rateOfFire;
		unsigned int updatingCost;
		TowerProperties(int damage,
			unsigned int cost,
			float radius,
			unsigned int rateOfFire,unsigned int updatingCost) {
			this->damage = damage;
			this->cost = cost;
			this->radius = radius;
			this->rateOfFire = rateOfFire;
			this->updatingCost = updatingCost;
		}
	};
	class Tower: public AbstractAttackingObject {
	protected:
		unsigned int level = 1;
		std::map<unsigned int, TowerProperties> properties;
		class TargetSheduler {
		private:
			Enemy* enemy = nullptr;
			const Point palacePos;
			const Point towerPos;
		public:
			TargetSheduler(const Point&,const Point&);
			void dropShedule();
			void shedule(Enemy*);
			virtual Enemy* operator ()();
		};
		TargetSheduler s;
	public:
		static const int MAX_LEVEL = 3;
		Tower(const Point& palacePos,const std::string& name,const std::string& filename);
		
		unsigned int getLevel()const;
		/*
		�������� ������� �����
		@param �������� ���������� ������
		@returns True, ���� ���������� ������ ������� � false �����
		**/
		bool updateLevel(unsigned int gold);
		/*
		@returns C������� �����
		**/
		TowerProperties getProperties()const;
		/*
		�������� ���� ����� (� ����� �� ����� ���� ��� �����)
		**/
		void dropTarget();
		/*
		���� ����� ��� ������ �����
		@return ��������� �� �����
		**/
		Enemy* getTarget();
		/*
		������� �����
		@param enemies - ����� ����� �� �����
		@return true ���� ����� ���� ��������� � false �����
		**/
		virtual bool fire(std::list<std::shared_ptr<Enemy>>& enemies);
	};
	class MagicTower: public Tower, public MagicObject {
	public:
		MagicTower(const Effect& e,
			const Point& palacePos,
			const std::string& name,
			const std::string& filename);
		/*
		������� �����
		@param enemies - ����� ����� �� �����
		@return true ���� ����� ���� ��������� � false �����
		**/
		virtual bool fire(std::list<std::shared_ptr<Enemy>>& enemies);
	};
}
#endif