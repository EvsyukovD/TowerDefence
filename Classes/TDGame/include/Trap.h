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
        /*
        Атаковать врагов в радиусе действия
        @param m - таблица всех живых врагов на карте
        @return true - если ловушка была активирована и false иначе
        **/
        virtual bool fire(std::list<Enemy*>& m);
    };
}
#endif // !__TRAP_H__