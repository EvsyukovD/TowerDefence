#include "../include/LandScape.h"
#include "../include/Cell.h"
#include "../include/Tower.h"
#include "../include/Trap.h"
namespace TowerDefence {
    LandScape::LandScape(const std::string& file) : TDObject(file) {
        /*«агрузка путей, мест дл€ построек из конфига, установка начального положени€ дл€ врагов*/
    }
    int LandScape::getFieldHeight() const {
        return height;
    }
    int LandScape::getFieldLength() const {
        return length;
    }
    void LandScape::setFieldHeight(int h) {
        height = h;
    }
    void LandScape::setFieldLength(int l) {
        length = l;
    }
    void LandScape::addAttackingObject(Point& p, AbstractAttackingObject* ob) { 
        auto res = battlefield.find(p);
        if (res == battlefield.end()) {
            throw std::invalid_argument("This point doesn't exist");
        }
        Cell& cell = res->second;
        if (instanceof<Tower*>(ob) && cell.getType() == CellType::TOWER_PLACE) {
            int cost = ((Tower*)ob)->getProperties().cost;
            if (palace.getGold() >= cost) {
                palace.takeGold(cost);
                cell.setType(CellType::TOWER, (Building*)ob);
                attackingObjects.insert_or_assign(p, ob);
            }
            return;
        }
        if (instanceof<Trap*>(ob) && cell.getType() == CellType::ROAD) {
            int cost = ((Trap*)ob)->getCost();
            if (palace.getGold() >= cost) {
                palace.takeGold(cost);
                cell.setType(CellType::TRAP, (Building*)ob);
                attackingObjects.insert_or_assign(p, ob);
            }
        }
    }
}