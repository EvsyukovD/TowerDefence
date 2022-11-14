#ifndef __TOWER_DEFENCE_H__
#define __TOWER_DEFENCE_H__
#include "cocos2d.h"
USING_NS_CC;
namespace TowerDefence {
	template<class Base, class T>
	bool instanceof(T*);
	
	class TDObject;
	class Effect;
	enum EffectType;
	class PoisonEffect;
	class WeaknessEffect;
	class DecelerationEffect;
	class Cell;
	enum CellType;
	class MagicObject;

	class Building;
	class Enemy;
	class LandScape;

	class Lair;
	class Palace;
	class AbstractAttackingObject;

	struct TowerProperties;
	class Trap;
	class Tower;
	class MagicTower;
}
#endif