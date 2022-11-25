#include "../include/LandScape.h"
#include "../include/Cell.h"
#include "../include/Tower.h"
#include "../include/Trap.h"
#include "../include/Lair.h"
#include "../include/TowerDefence.h"
#include "../lib/json/single_include/nlohmann/json.hpp"
using json = nlohmann::json;
namespace TowerDefence {
    LandScape::LandScape(const std::string& jsonConfig){
        json config(jsonConfig);
        object->initWithFile(config["map"]);
        object->setScale(config["map_scale"]);
        object->setAnchorPoint(Vec2(0, 1));
        size_t cellHeight = config["cell_height"], cellWidth = config["cell_width"];
        auto visibleSize = object->getContentSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        height = visibleSize.height, width = visibleSize.width;
        for (int i = 0; i * cellHeight < height; i++) {
            battlefield.push_back(std::vector<Cell>());
            for (int j = 0; j * cellWidth < width; j++) {
                Vec2 v = Vec2(origin.x + j * cellWidth, origin.y + visibleSize.height - i * cellHeight);
                Cell cell = Cell(v,CellType::NONE,nullptr,cellHeight,cellWidth);
                battlefield[i].push_back(cell);
            }
        }
        for (int k = 0; k < config["road"].size(); k++) {
            int i = config["road"][k][0], j = config["road"][k][1];
            battlefield[i][j].setType(CellType::ROAD, nullptr);
        }
        for (int k = 0; k < config["towers"].size(); k++) {
            int i = config["towers"][k][0], j = config["towers"][k][1];
            battlefield[i][j].setType(CellType::TOWER_PLACE,nullptr);
        }
        std::vector<Point> path;
        const Point& delta = Point(cellWidth,-cellHeight) / 2.0;
        for (int i = 0; i < config["path"].size(); i++) {
            const Point& topLeft  = battlefield[config["path"][i][0]][config["path"][i][1]].getTopLeft();
            path.push_back(topLeft + delta);
        }
        size_t lairsNum = config["lairs_num"];
        std::string lairConfigFile = "lair_config_";
        std::string lair_config;
        for (int i = 0; i < lairsNum; i++) {
            lair_config = config[lairConfigFile.append(std::to_string(i))];
            lairs.push_back(Lair(path,lair_config));
        }
        palace.init((size_t)config["gold"], (size_t)config["max_strength"]);
    }
    int LandScape::getFieldHeight() const {
        return height;
    }
    int LandScape::getFieldLength() const {
        return width;
    }
    void LandScape::addAttackingObject(const Point& p, AbstractAttackingObject* ob) { 
        /*auto res = battlefield.find(p);
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
        */
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
                enemies.erase(iter);
            }
            e->tick();
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
        ticks++;
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