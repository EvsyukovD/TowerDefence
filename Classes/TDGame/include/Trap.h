#ifndef __TRAP_H__
#define __TRAP_H__
#include "MagicObject.h"
#include "AbstractAttackingObject.h"
namespace TowerDefence {
    class Trap: public MagicObject,public AbstractAttackingObject{
    protected:
        float radius;
        int cost;
    public:
        Trap(float radius,int cost, const Effect& e, const std::string& name, const std::string& filename);
        int getCost() const;
        float getRadius() const;
        /**
        Attack enemies, which is situated in radius of firing
        \param m - living enemies
        \return true, if trap was activated and false otherwise
        */
        virtual bool fire(MySTL::List<Enemy*>& m);
    };
}
#endif // !__TRAP_H__