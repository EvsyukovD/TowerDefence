#ifndef __LANDSCAPE_H__
#define __LANDSCAPE_H__
#include "TDObject.h"
#include "Palace.h"
#include "cocos2d.h"
#include <memory>
namespace TowerDefence {
	class LandScape: public TDObject,public cocos2d::Layer{
	private:
		Palace palace;
		std::list<std::shared_ptr<Enemy>> enemies;
		//std::map<Point, Cell> battlefield;
		std::vector<std::vector<Cell>> battlefield;
		std::vector<Lair> lairs;
		std::list<std::shared_ptr<AbstractAttackingObject>> attackingObjects;
		int height = 0;
		int width = 0;
		unsigned int ticks = 0;
	public:
		LandScape(const std::string& jsonConfigFile);
		LandScape():TDObject(){}
		virtual bool init();
		int getFieldHeight()const;
		int getFieldLength() const;
		/*!
		 \brief Функции, отвечающие за касание экрана
		 */		
		void addAttackingObject(const Point&, AbstractAttackingObject*);
		/*virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
		virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
		virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
		virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);*/
		
		/*!
		\brief Попытаться обновить уровень башни
		\param t - данная башня
		\return true если обновление прошло успешно и false иначе
		*/
		bool tryUpdateTower(Tower& t);
		/*
		\brief Враги и башни делают ход
		*/
		void tick();
		/*
		Запуск игры
		**/
		//void run();
		virtual ~LandScape();
		CREATE_FUNC(LandScape);
	};
}
#endif // !__LANDSCAPE_H__
