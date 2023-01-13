#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "TDObject.h"
#include "Effect.h"
#include "../lib/list/list.h"
namespace TowerDefence {
	class Enemy : public TDObject{
	private:
		  int health;
		  float speed;
		  float nativeSpeed;
		  MySTL::List<Effect*> effects;
		  std::string name;
		  std::vector<Point> path;
		  int currentPos;
		  unsigned int award = 0;
	public:
		int MAX_HEALTH;
		Enemy(int maxHealth,
			float speed,
			unsigned int award,
			const std::string& name,
			const std::vector<Point>& path, const std::string& filename);
		Enemy(const std::vector<Point>& path,const std::string& jsonConfig);
		Enemy(const Enemy&);
		/** 
		\return Enemy dead flag
		*/
		bool isDead()const;
		/**  
		\return current health
		*/
		int getHealth()const;
		/**  
		\return Award for destroing enemy
		*/
		unsigned int getAward() const;
		/**  
		Set current amount of health
		*/
		void setHealth(int);
		/**  
		* Damage enemy. If enemy has weakness effect
		* damage is increased
		\param d - damage value
		*/
		void getDamage(int d);
		/**  
		\return current speed
		*/
		float getSpeed()const;
		/**  
		Set current speed of enemy
		\param new value of speed
		\throws std::invalid_argument - if value less than 0
		*/
		void setSpeed(float);
		/**  
		Add effect to enemy
		\param effect
		*/
		void addEffect(Effect*);
		/**  
		\return Enemy name
		*/
		std::string getName()const;
		/**  
		\return Native speed of enemy
		*/
		float getNativeSpeed()const;
		/**  
		Set enemy name
		*/
		void setName(const std::string&);
		/**  
		\return amount of effects
		*/
		int getNumOfEffects()const;
		/**  
		Make step and calculate health\n
		If health less than zero\n
		he is destroyed
		*/
		void tick();
		/**
		\return Enemy come to the finish
		*/
		bool isOnFinish() const;
		virtual ~Enemy();
	private:
		ParticleExplosion* getEffectVisualization(Color3B effect_color);
	};
}
#endif // !__ENEMY_H__