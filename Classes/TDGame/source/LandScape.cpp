#include "../include/LandScape.h"
#include "../include/Cell.h"
#include "../include/Tower.h"
#include "../include/Trap.h"
#include "../include/Lair.h"
#include "../include/TowerDefence.h"
namespace TowerDefence {
    LandScape::LandScape(const std::string& file) : TDObject(file) {
        /*Загрузка путей, мест для построек из конфига, установка начального положения для врагов*/
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
    void LandScape::addAttackingObject(const Point& p, AbstractAttackingObject* ob) { 
        auto res = battlefield.find(p);
        if (res == battlefield.end()) {
            throw std::invalid_argument("This point doesn't exist");
        }
        Cell& cell = res->second;
        if (instanceof<Tower, AbstractAttackingObject>(ob) && cell.getType() == Cell::CellType::TOWER_PLACE) {
            int cost = ((Tower*)ob)->getProperties().cost;
            if (palace.getGold() >= cost) {
                palace.takeGold(cost);
                cell.setType(Cell::CellType::TOWER, (Building*)ob);
                attackingObjects.push_back(ob);
            }
            return;
        }
        if (instanceof<Trap,AbstractAttackingObject>(ob) && cell.getType() == Cell::CellType::ROAD) {
            int cost = ((Trap*)ob)->getCost();
            if (palace.getGold() >= cost) {
                palace.takeGold(cost);
                cell.setType(Cell::CellType::TRAP, (Building*)ob);
                attackingObjects.push_back(ob);
            }
        }
    }
    void LandScape::tick() {
        bool emptyLairsFlag = true;
        for (int i = 0; i < lairs.size(); ++i) {
            emptyLairsFlag = emptyLairsFlag && lairs[i].getNumOfEnemies() == 0;
            Enemy* e = lairs[i].getNextEnemy(ticks);
            if (e) {
                enemies.push_back(e);
            }
        }
        if (emptyLairsFlag && enemies.empty()) {
            //Победа, конец игры
            return;
        }
        for (auto iter = enemies.begin(); iter != enemies.end(); ++iter) {
            Enemy* e = *iter;
            if (e->isDead()) {
                palace.addGold(e->getAward());
                enemies.erase(iter);
            }
            else if (e->isOnFinish()) {
                palace.getDamage(e->getHealth());
                if (palace.isDestroyed()) {
                    //Проигрыш, конец игры
                    return;
                }
            }
        }
        for (auto iter = attackingObjects.begin(); iter != attackingObjects.end(); ++iter) {
            if (instanceof<Trap,AbstractAttackingObject>(*iter)) {
                if ((*iter)->fire(enemies)) {
                    attackingObjects.erase(iter);
                }
            }
            else {
                (*iter)->fire(enemies);
            }
        }
    }
    LandScape::~LandScape() {
        this->attackingObjects.clear();
        this->battlefield.clear();
        this->enemies.clear();
    }
}