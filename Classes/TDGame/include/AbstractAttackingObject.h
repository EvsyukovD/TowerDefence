#ifndef __ABSTRACT_ATTACKING_OBJECT_H__
#define __ABSTRACT_ATTACKING_OBJECT_H__
#include "Building.h"
#include "Enemy.h"
namespace TowerDefence {
	class AbstractAttackingObject: public Building {
	public:
		AbstractAttackingObject(const std::string& name, const std::string& filename):Building(name,filename) {}
		/*
		Функция атаки
		@param enemies - живые враги на карте
		@return true если враги были атакованы и false иначе 
		**/
		virtual bool fire(std::list<Enemy*> & enemies) = 0;
	};
}
#endif // !__ABSTRACT_ATTACKING_OBJECT_H__
