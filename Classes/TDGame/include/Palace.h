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
		/**
		\return Current amount of gold
		*/
		unsigned int getGold()const;

		/**
		\brief Give gold to the palace
		\param g - amount of gold
		*/
		void addGold(unsigned int g);
		/**
		\breif Take gold from palace 
		\param amount of gold
		\returns true, if palace has enough amount of gold and false otherwise 
		*/
		bool takeGold(unsigned int);
		/**
		\return Current strength of palace
		*/
		unsigned int getStrength() const;
		/**
		\breif Damage palace
		\param d - damage value
		*/
		void getDamage(unsigned int d);
		/**
		@return Palace is destroyed flag
		*/
		bool isDestroyed() const;

		void init(unsigned int gold,unsigned int maxStrength);
	};
}
#endif // !__PALACE_H__

