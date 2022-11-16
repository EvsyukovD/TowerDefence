#ifndef __LANDSCAPE_H__
#define __LANDSCAPE_H__
#include "TDObject.h"
#include "Palace.h"
#include "cocos2d.h"
#include <memory>
namespace TowerDefence {
	class LandScape: public TDObject,public cocos2d::Scene{
	private:
		Palace palace;
		std::list<std::shared_ptr<Enemy>> enemies;
		std::map<Point, Cell> battlefield;
		std::vector<Lair> lairs;
		std::list<std::shared_ptr<AbstractAttackingObject>> attackingObjects;
		int height = 0;
		int length = 0;
		unsigned int ticks = 0;
	public:
		LandScape(const std::string& jsonConfigFile,const std::string& fileWithLandScape);
		LandScape():TDObject("Empty.png"){}
		virtual bool init();
		int getFieldHeight()const;
		int getFieldLength() const;
		void setFieldHeight(int); //�����������
		void setFieldLength(int); //�����������
		void addAttackingObject(const Point&, AbstractAttackingObject*);
		/*
		���������� �������� ������� �����
		@param t - ������ �����
		@returns true ���� ���������� ������ ������� � false �����
		**/
		bool tryUpdateTower(Tower& t);
		/*
		����� � ����� ������ ���
		**/
		void tick();
		virtual ~LandScape();
		CREATE_FUNC(LandScape);
	};
}
#endif // !__LANDSCAPE_H__
