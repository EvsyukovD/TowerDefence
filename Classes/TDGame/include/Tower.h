#ifndef __TOWER_H__
#define __TOWER_H__
#include "AbstractAttackingObject.h"
#include "MagicObject.h"
#include "../lib/json/single_include/nlohmann/json.hpp"
using json = nlohmann::json;
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
		TowerProperties(): TowerProperties(0, 0, 0, 0, 0) {}
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
			TargetSheduler(const TargetSheduler& s);
			void dropShedule();
			void shedule(Enemy*);
			virtual Enemy* operator ()();
		};
		TargetSheduler s;
	private:
		void displayCurrentLevel();
	public:
		static const int MAX_LEVEL = 3;
		Tower(const Point& palacePos,const Point& towerPos,const std::string& jsonConfig);
		Tower(const Point& palacePos, const Point& towerPos, const json& js);
		unsigned int getLevel()const;
		Tower(const Tower& t);
		/**
		\brief Update tower's level
		\param amount of gold
		\return true, if updating was successful and false otherwise
		*/
		bool updateLevel(unsigned int gold);
		/**
		\return Tower's properties
		*/
		TowerProperties getProperties()const;
		/**
		Drop target of tower (in that case tower hasn't got target)
		*/
		void dropTarget();
		/**
		\return Tower's target pointer
		*/
		Enemy* getTarget();
		/**
		\brief Function of fire
		\param enemies - living enemies
		\return true if enemy was attacked and false otherwise
		*/
		virtual bool fire(std::list<Enemy*>& enemies);
	};
	class MagicTower: public Tower, public MagicObject {
	public:
		MagicTower(const Effect&,const Point& palacePos,const Point& towerPos,const std::string& jsonConfig);
		MagicTower(const Effect&,const Point& palacePos, const Point& towerPos, const json& js);
		/**
		\brief Function of fire
		\param enemies - living enemies
		\return true if enemy was attacked and false otherwise
		*/
		virtual bool fire(std::list<Enemy*>& enemies);
	};
}
#endif