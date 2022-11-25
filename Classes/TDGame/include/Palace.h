#ifndef __PALACE_H__
#define __PALACE_H__
#include "Building.h"
namespace TowerDefence {
	class Palace : public Building {
	private:
		unsigned int gold;
		unsigned int maxStrength;
		unsigned int currentStrength;
	public:
		Palace();
		Palace(const std::string& name, const std::string& filename,unsigned int gold, unsigned int maxStrength);
		/*
		@return Текущее количество золота
		**/
		unsigned int getGold()const;

		/*
		Дать замку золота
		@param g - добавочное значение золота
		**/
		void addGold(unsigned int g);
		/*
		Забрать у замка данное количество золота.
		@param Новое количество золота.
		@returns true, если у замка хватает золота и false иначе 
		**/
		bool takeGold(unsigned int);
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

		void init(unsigned int gold,unsigned int maxStrength);
	};
}
#endif // !__PALACE_H__

