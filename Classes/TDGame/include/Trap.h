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
        ��������� ������ � ������� ��������
        @param m - ������� ���� ����� ������ �� �����
        @return true - ���� ������� ���� ������������ � false �����
        **/
        virtual bool fire(std::map<Point, Enemy>& m);
    };
}
#endif // !__TRAP_H__