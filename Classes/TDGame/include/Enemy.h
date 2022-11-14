#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "TDObject.h"
namespace TowerDefence {
	class Enemy : public TDObject{
	private:
		  int health;
		  float speed;
		  std::list<Effect> effects;
		  std::string name;
		  std::vector<Point> path;
		  int currentPos;
		  unsigned int award = 0;
	public:
		const int MAX_HEALTH;
		Enemy(int maxHealth,
			float speed,
			unsigned int award,
			const std::string& name,
			const std::vector<Point>& path, const std::string& filename);
		
		Enemy(const Enemy&);
		/*
		@return флаг, что враг умер
		**/
		bool isDead()const;
		/*
		Вернуть текущее здоровье врага
		@return текущее здоровье
		**/
		int getHealth()const;
		/*
		Установить текущее здоровье врага
		**/
		/*
		@return награда за уничтожение врага
		**/
		unsigned int getAward() const;
		void setHealth(int);
		/*
		Нанести урон врагу. Если враг имеет эффект\n
		ослабления, то ему наносится дополнительный урон
		@param d - значение урона 
		**/
		void getDamage(int d);
		/*
		Вернуть текущую скорость врага
		@return текущую скорость
		**/
		float getSpeed()const;
		/*
		Установить текущую скорость врага
		@param новое значение скорости
		@throws std::invalid_argument - При отрицательной скорости
		**/
		void setSpeed(float);
		/*
		Добавить эффект врагу
		@param Накладываемый эффект
		**/
		void addEffect(const Effect&);
		/*
		Вернуть имя  врага
		@return имя врага
		**/
		std::string getName()const;
		/*
		Установить имя врага
		**/
		void setName(const std::string&);
		/*
		Получить количество эффектов
		@return кол-во эффектов
		**/
		int getNumOfEffects()const;
		/*
		Сделать ход и рассчитать здоровье\n
		Если здоровье врага не положительно то\n
		он уничтожается
		**/
		void tick();
		/*
		@return Флаг того, что враг дошёл до конца пути
		**/
		bool isOnFinish() const;

		virtual ~Enemy();
	};
}
#endif // !__ENEMY_H__