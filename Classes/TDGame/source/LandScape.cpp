#include "../include/LandScape.h"
#include "../include/Cell.h"
#include "../include/Tower.h"
#include "../include/Trap.h"
#include "../include/Lair.h"
#include "../include/TowerDefence.h"
#include "../lib/json/single_include/nlohmann/json.hpp"
using json = nlohmann::json;
namespace TowerDefence {
    LandScape::LandScape(const std::string& jsonConfig,const std::string& fileWithLandScape) : TDObject(fileWithLandScape) {
        json config(jsonConfig);

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
        if (instanceof<Tower, AbstractAttackingObject>(ob) && cell.getType() == CellType::TOWER_PLACE) {
            int cost = ((Tower*)ob)->getProperties().cost;
            if (palace.getGold() >= cost) {
                palace.takeGold(cost);
                std::shared_ptr<Building> b(ob);
                cell.setType(CellType::TOWER, b);
                std::shared_ptr<AbstractAttackingObject> p(ob);
                attackingObjects.push_back(p);
            }
            return;
        }
        if (instanceof<Trap,AbstractAttackingObject>(ob) && cell.getType() == CellType::ROAD) {
            int cost = ((Trap*)ob)->getCost();
            if (palace.getGold() >= cost) {
                palace.takeGold(cost);
                std::shared_ptr<Building> b(ob);
                cell.setType(CellType::TRAP, b);
                std::shared_ptr<AbstractAttackingObject> p(ob);
                attackingObjects.push_back(p);
            }
        }
    }
    void LandScape::tick() {
        bool emptyLairsFlag = true;
        for (int i = 0; i < lairs.size(); ++i) {
            emptyLairsFlag = emptyLairsFlag && lairs[i].getNumOfEnemies() == 0;
            std::shared_ptr<Enemy> e = lairs[i].getNextEnemy(ticks);
            if (e.get()) {
                enemies.push_back(e);
            }
        }
        if (emptyLairsFlag && enemies.empty()) {
            //Победа, конец игры
            return;
        }
        for (auto iter = enemies.begin(); iter != enemies.end(); ++iter) {
            Enemy* e = (*iter).get();
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
            if (instanceof<Trap,AbstractAttackingObject>((*iter).get())) {
                if ((*iter).get()->fire(enemies)) {
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
    bool LandScape::tryUpdateTower(Tower& t) {
        unsigned int cost = t.getProperties().updatingCost;
        if (t.updateLevel(palace.getGold())) {
            palace.takeGold(cost);
            return true;
        }
        return false;
    }
    bool LandScape::init() {
        if (battlefield.size() == 0) {
            return false;
        }

    }
}