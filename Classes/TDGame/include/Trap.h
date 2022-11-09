#ifndef __TRAP_H__
#define __TRAP_H__
#include "MagicObject.h"
#include "AbstractAttackingObject.h"
namespace TowerDefence {
    class Trap: public MagicObject,public AbstractAttackingObject{
    protected:
        float radius;
    public:
        Trap(float radius, const Effect& e, const std::string& name, const std::string& filename);
        /*
        Атаковать врагов в радиусе действия
        @param m - таблица всех живых врагов на карте
        @return true - если ловушка была активирована и false иначе
        **/
        virtual bool fire(std::map<Point, Enemy>& m);
    };
}
#endif // !__TRAP_H__