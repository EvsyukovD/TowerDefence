#ifndef __ABSTRACT_ATTACKING_OBJECT_H__
#define __ABSTRACT_ATTACKING_OBJECT_H__
#include "Building.h"
#include "Enemy.h"
#include "../lib/list/list.h"
#include <memory>
namespace TowerDefence {
	class AbstractAttackingObject: public Building {
	public:
		AbstractAttackingObject(const std::string& name, const std::string& filename):Building(name,filename) {}
		AbstractAttackingObject() {}
		/**
		\brief Function of fire
		\param enemies - living enemies
		\return true if enemy was attacked and false otherwise 
		*/
		virtual bool fire(MySTL::List<Enemy*>& enemies) = 0;
	};
}
#endif // !__ABSTRACT_ATTACKING_OBJECT_H__
