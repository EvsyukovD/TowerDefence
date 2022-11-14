#ifndef __PALACE_H__
#define __PALACE_H__
#include "Building.h"
namespace TowerDefence {
	class Palace : public Building {
	private:
		unsigned int gold;
		const unsigned int MAX_STRENGTH;
		unsigned int currentStrength;
	public:
		Palace();
		Palace(const std::string& name, const std::string& filename,unsigned int gold, unsigned int maxStrength);
		/*
		@return Текущее количество золота
		**/
		unsigned int getGold()const;
		/*
		Забрать у замка данное количество золота
		@param Новое количество золота
		@throws std::invalid_argument - если у замка не хватает золота
		**/
		void takeGold(unsigned int);
		/*
		@return Текущая прочность замка
		**/
		unsigned int getStrength() const;
		/*
		Нанести урон замку
		@param d - величина урона
		**/
		void getDamage(unsigned int d);
		/*
		@return Флаг уничтожен ли замок
		**/
		bool isDestroyed() const;
	};
}
#endif // !__PALACE_H__

