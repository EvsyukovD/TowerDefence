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
		Palace(int gold, unsigned int currentStrength, unsigned int maxStrength);

		unsigned int getGold()const;
		void setGold(unsigned int);
		unsigned int getStrength();
		void setStrength(unsigned int);

	};
}
#endif // !__PALACE_H__

