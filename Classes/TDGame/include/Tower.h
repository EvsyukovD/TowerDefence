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
			TargetSheduler() {}
			void dropShedule();
			void shedule(Enemy*);
			virtual Enemy* operator ()();
		};
		TargetSheduler s;
	public:
		static const int MAX_LEVEL = 3;
		Tower(const Point& palacePos,const std::string& name,const std::string& filename);
		Tower(const Point& palacePos,const Point& towerPos,const std::string& jsonConfig);
		unsigned int getLevel()const;
		/*
		ќбновить уровень башни
		@param ¬носимое количество золота
		@returns True, если обновление прошло успешно и false иначе
		**/
		bool updateLevel(unsigned int gold);
		/*
		@returns Cвойства башни
		**/
		TowerProperties getProperties()const;
		/*
		—бросить цель башни (у башни не будет цели дл€ атаки)
		**/
		void dropTarget();
		/*
		÷ель атаки дл€ данной башни
		@return ”казатель на врага
		**/
		Enemy* getTarget();
		/*
		‘ункци€ атаки
		@param enemies - живые враги на карте
		@return true если враги были атакованы и false иначе
		**/
		virtual bool fire(std::list<std::shared_ptr<Enemy>>& enemies);
	};
	class MagicTower: public Tower, public MagicObject {
	public:
		MagicTower(const Effect& e,
			const Point& palacePos,
			const std::string& name,
			const std::string& filename);
		MagicTower(const Effect&,const Point& palacePos,const std::string& jsonConfig);
		/*
		‘ункци€ атаки
		@param enemies - живые враги на карте
		@return true если враги были атакованы и false иначе
		**/
		virtual bool fire(std::list<std::shared_ptr<Enemy>>& enemies);
	};
}
#endif