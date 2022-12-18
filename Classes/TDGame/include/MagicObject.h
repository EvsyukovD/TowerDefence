#ifndef __MAGIC_OBJECT_H__
#define __MAGIC_OBJECT_H__
#include "Effect.h"
namespace TowerDefence {
	class MagicObject {
	private:
		Effect effect;
	public:
		MagicObject(const Effect&);
		/**  
	    \return Trap's effect
		*/
		Effect* getEffect() const;
		/**
		Set trap's effect
		*/
		void setEffect(const Effect&);
	};
}
#endif // !__MAGIC_OBJECT_H__

