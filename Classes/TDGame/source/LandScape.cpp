#include "../include/LandScape.h"
#include "../include/Cell.h"
#include "../include/Tower.h"
#include "../include/Trap.h"
#include "../include/Lair.h"
#include "../include/TowerDefence.h"
#include <fstream>
namespace TowerDefence {
    cocos2d::Scene* LandScape::createScene(const std::string& jsonConfig) {
        auto scene = Scene::create();
        LandScape* l = new LandScape();
        l->initWithConfig(jsonConfig);
        if (l->init()) {
            l->autorelease();
        }
        else {
            delete l;
            delete scene;
            return nullptr;
        }
        scene->addChild(l);
        return scene;
    }
    void LandScape::initMap(const json& config) {
        object->initWithFile(config["map"]);
        object->setScale((float)config["map_scale"]);
        float cellHeight = config["cell_height"], cellWidth = config["cell_width"];
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        object->setAnchorPoint(Vec2(0, 1));
        object->setPosition(Vec2(origin.x, origin.y + visibleSize.height));
        auto vis = object->getContentSize();
        height = vis.height, width = vis.width;
        for (int i = 0; i * cellHeight < visibleSize.height; i++) {
            battlefield.push_back(std::vector<Cell>());
            for (int j = 0; j * cellWidth < visibleSize.width; j++) {
                Vec2 v = Vec2(origin.x + j * cellWidth, origin.y + visibleSize.height - i * cellHeight);
                Cell cell = Cell(v, CellType::NONE, nullptr, cellHeight, cellWidth);
                battlefield[i].push_back(cell);
            }
        }
    }
    std::vector<Point> LandScape::readPath(const json& config,int pathNum) {
        size_t cellHeight = config["cell_height"], cellWidth = config["cell_width"];
        std::vector<Point> path;
        std::string field = "path_";
        field = field.append(std::to_string(pathNum));
        const Point& delta = Point(cellWidth, -cellHeight) / 2.0;
        for (int i = 0; i < config[field].size(); i++) {
            const Point& topLeft = battlefield[config[field][i][0]][config[field][i][1]].getTopLeft();
            path.push_back(topLeft + delta);
        }
        return path;
    }
    void LandScape::initRoad(const json& config) {
        for (int k = 0; k < config["road"].size(); k++) {
            int i = config["road"][k][0], j = config["road"][k][1];
            battlefield[i][j].setType(CellType::ROAD, nullptr);
        }
    }
    void LandScape::initTowerPlaces(const json& config) {
        for (int k = 0; k < config["towers"].size(); k++) {
            int i = config["towers"][k][0], j = config["towers"][k][1];
            battlefield[i][j].setType(CellType::TOWER_PLACE, nullptr);
        }
    }
    void LandScape::initLairs(const json& config) {
        size_t lairsNum = config["lairs_num"];
        //std::string lairConfigFile = "lair_config_";
        std::string lair_config;
        for (int i = 0; i < lairsNum; i++) {
            lair_config = "lair_config_";
            lair_config = config[lair_config.append(std::to_string(i))];
            lairs.push_back(Lair(readPath(config, i), lair_config));
        }
    }
    void LandScape::initWithConfig(const std::string& jsonConfig){
        std::ifstream file(jsonConfig);
        json config;
        file >> config;
        file.close();
        initMap(config);
        initRoad(config);
        initTowerPlaces(config);
        initLairs(config);
        palace.init((size_t)config["gold"], (size_t)config["max_strength"]);
    }
    int LandScape::getFieldHeight() const {
        return height;
    }
    int LandScape::getFieldLength() const {
        return width;
    }
    void LandScape::addAttackingObject(Cell& cell, AbstractAttackingObject* ob) { 
        /*auto res = battlefield.find(p);
        if (res == battlefield.end()) {
            throw std::invalid_argument("This point doesn't exist");
        }*/
        //Cell& cell = res->second;
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
                this->addChild(e->getSprite().get(),0,e->getObjectID());
            }
        }
        if (emptyLairsFlag && enemies.empty()) {
            //Победа, конец игры
            isEnd = true;
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
                    isEnd = true;
                    isVictory = false;
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
         this->addChild(object.get());
       // run();
        return true;
    }
    void LandScape::run() {
        while (!isEnd) {
            tick();
        }
    }
}