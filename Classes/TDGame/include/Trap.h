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
        ��������� ������ � ������� ��������
        @param m - ������� ���� ����� ������ �� �����
        @return true - ���� ������� ���� ������������ � false �����
        **/
        virtual bool fire(std::list<std::shared_ptr<Enemy>>& m);
    };
}
#endif // !__TRAP_H__