#ifndef __ABSTRACT_ATTACKING_OBJECT_H__
#define __ABSTRACT_ATTACKING_OBJECT_H__
#include "Building.h"
#include "Enemy.h"
#include <memory>
namespace TowerDefence {
	class AbstractAttackingObject: public Building {
	public:
		AbstractAttackingObject(const std::string& name, const std::string& filename):Building(name,filename) {}
		AbstractAttackingObject() {}
		/*
		������� �����
		@param enemies - ����� ����� �� �����
		@return true ���� ����� ���� ��������� � false ����� 
		**/
		virtual bool fire(std::list<std::shared_ptr<Enemy>> & enemies) = 0;
	};
}
#endif // !__ABSTRACT_ATTACKING_OBJECT_H__
