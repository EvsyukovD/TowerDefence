#ifndef __LANDSCAPE_H__
#define __LANDSCAPE_H__
#include "TDObject.h"
#include "../include/Palace.h"
namespace TowerDefence {
	class LandScape: public TDObject {
	private:
		Palace palace;
		std::map<Point, Enemy> enemies;
		std::map<Point, Cell> battlefield;
		std::map<Point,AbstractAttackingObject *> attackingObjects;
		int height = 0;
		int length = 0;
	public:
		LandScape(const std::string& fileWithLandScape);
		int getFieldHeight()const;
		int getFieldLength() const;
		void setFieldHeight(int); //реализовать
		void setFieldLength(int); //реализовать
		void addAttackingObject(Point&, AbstractAttackingObject*);
		//добавить обновление уровня башен
		
		void tick();
	};
}
#endif // !__LANDSCAPE_H__
