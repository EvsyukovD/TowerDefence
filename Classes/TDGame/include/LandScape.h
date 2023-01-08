#ifndef __LANDSCAPE_H__
#define __LANDSCAPE_H__
#include "TDObject.h"
#include "Palace.h"
#include "cocos2d.h"
#include "Effect.h"
#include <memory>
#include "../lib/json/single_include/nlohmann/json.hpp"
using json = nlohmann::json;
namespace TowerDefence {
	class LandScape: public TDObject,public cocos2d::Layer{
	private:
		Palace palace;
		std::list<Enemy*> enemies;
		std::vector<std::vector<Cell>> battlefield;
		std::vector<Lair> lairs;
		std::list<AbstractAttackingObject*> attackingObjects;
		int height = 0;
		int width = 0;
		unsigned int ticks = 0;
		bool isEnd = false;
		bool isVictory = true;
		const static int LAYER_PRIOR = 0;
		const static int MAP_PRIOR = -1;
		const static int TOWER_PLACES_PRIOR = 100;
		const static int ENEMY_PRIOR = 200;
		const static int ATTACKING_OBJECTS_PRIOR = 400;
		json trapConfig;
		std::string towerConfig;
		bool currentTowerIsMagic = false;
		Trap* createTrap(const Point& trapPos);
		Tower* createTower(bool isMagic, const Point& towerPos, Effect::EffectType type);
		/**
		 * \brief display current palace params
		 */
		void updatePalaceParams();
		/**
		\brief Try to update tower's level
		\param t - tower
		*/
		void updateTowerLevel(Tower* t);
		void menu_change_tower_type(Ref* sender);
	public:
		static cocos2d::Scene* createScene(const std::string& jsonConfigFile,const json& trapConfig,const json& towerConfig);
		void initWithConfig(const std::string& jsonConfigFile,const std::string& trapConfig, const std::string& towerConfig);
		LandScape(){}
		virtual void update(float dt);
		virtual bool init();
		/**
		 * \return Battlefield height 
		 */
		int getFieldHeight()const;
		/**
		 * \return Battlefield length
		 */
		int getFieldLength() const;
		/**  
		 \brief Add attacking object
		 \param cell - cell for attacking object
		 \param ob - attacking object
		 */		
		void addAttackingObject(Cell& cell, AbstractAttackingObject* ob);

		virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
		/*virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
		virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
		virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);*/
		
		/**  
		\brief Try to update tower's level 
		\param t - tower
		\return true if updating was successfull and false otherwise
		*/
		bool tryUpdateTower(Tower& t);
		/*
		\brief Enemies and towers do their step
		*/
		void tick();
		virtual ~LandScape();
		/**
		\brief Running the game
		*/
		void  run();
		CREATE_FUNC(LandScape);
	private:
		/**  
		\brief Map initializing
		\param config - json config file
		*/
		void initMap(const json& config);
		/**  
		\brief Road initializing
		\param config - json config file
		*/
		void initRoad(const json& config);
		/**  
		\brief Tower places initializing
		\param config - json config file
		*/
		void initTowerPlaces(const json& config);
		/**  
		\brief Read enemy path with some number
		\param config - json config file
		\param pathNum - path number in config
		*/
		std::vector<Point> readPath(const json& config, int pathNum);
		/**  
		\brief Lairs initializing
		\param config - json config file
		*/
		void initLairs(const json& config);
	};
}
#endif // !__LANDSCAPE_H__
