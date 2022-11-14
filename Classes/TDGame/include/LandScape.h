#ifndef __LANDSCAPE_H__
#define __LANDSCAPE_H__
#include "TDObject.h"
#include "../include/Palace.h"
namespace TowerDefence {
	class LandScape: public TDObject{
	private:
		Palace palace;
		std::list<Enemy*> enemies;
		std::map<Point, Cell> battlefield;
		std::vector<Lair> lairs;
		std::list<AbstractAttackingObject*> attackingObjects;
		int height = 0;
		int length = 0;
		unsigned int ticks = 0;
	public:
		LandScape(const std::string& fileWithLandScape);
		int getFieldHeight()const;
		int getFieldLength() const;
		void setFieldHeight(int); //�����������
		void setFieldLength(int); //�����������
		void addAttackingObject(const Point&, AbstractAttackingObject*);
		//�������� ���������� ������ �����
		
		void tick();
		virtual ~LandScape();
	};
}
#endif // !__LANDSCAPE_H__
