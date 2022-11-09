#ifndef __LANDSCAPE_H__
#define __LANDSCAPE_H__
#include "TDObject.h"

namespace TowerDefence {
	class LandScape: private TDObject {
	private:
		std::map<Point, Enemy> enemies;
		std::map<Point, Cell> battlefield;
		std::map<Point,AbstractAttackingObject> attackingObjects;
	public:
		LandScape();
		int getFieldHeight()const;
		int getFieldLength() const;
		void setFieldHeight(int)const;
		void setFieldLength(int)const;
		void addAttackingObject(Point&, AbstractAttackingObject&);
		void addEnemy(Point&, Enemy&);
		void tick();
	};
}
#endif // !__LANDSCAPE_H__
