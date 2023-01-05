#include "../include/LandScape.h"
#include "../include/Cell.h"
#include "../include/Tower.h"
#include "../include/Trap.h"
#include "../include/Lair.h"
#include "../include/TowerDefence.h"
#include <fstream>
namespace TowerDefence {
    cocos2d::Scene* LandScape::createScene(const std::string& jsonConfig,const json& trapConfig,const json& towerConfig) {
        auto scene = Scene::create();
        LandScape* l = new LandScape();
        l->initWithConfig(jsonConfig,trapConfig,towerConfig);
        if (l->init()) {
            l->autorelease();
        }
        else {
            delete l;
            delete scene;
            return nullptr;
        }
        scene->addChild(l,LAYER_PRIOR);
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
        DrawNode* node = nullptr;
        for (int i = 0; i * cellHeight < vis.height; i++) {
            battlefield.push_back(std::vector<Cell>());
            for (int j = 0; j * cellWidth < vis.width; j++) {
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
        const Point& delta = Point(cellWidth / 2.0, cellHeight / 2.0) ;
        for (int i = 0; i < config[field].size(); i++) {
            const Point& topLeft = battlefield[config[field][i][0]][config[field][i][1]].getTopLeft();
            path.push_back(Point(topLeft.x + delta.x,topLeft.y - delta.y));
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
        DrawNode* drawNode = nullptr;
        Point topLeft;
        for (int k = 0; k < config["towers"].size(); k++) {
            int i = config["towers"][k][0], j = config["towers"][k][1];
            battlefield[i][j].setType(CellType::TOWER_PLACE, nullptr);
            drawNode = DrawNode::create();
            topLeft = battlefield[i][j].getTopLeft();
            drawNode->setAnchorPoint(Point(0, 1));
            //drawNode->setPosition(topLeft);
            drawNode->drawRect(topLeft, topLeft + Point(battlefield[i][j].getWidth(), -battlefield[i][j].getHeight()), Color4F::BLACK);
            this->addChild(drawNode,TOWER_PLACES_PRIOR);
        }
    }
    void LandScape::initLairs(const json& config) {
        size_t lairsNum = config["lairs_num"];
        //std::string lairConfigFile = "lair_config_";
        std::string lair_config;
        bool isInit = false;
        for (int i = 0; i < lairsNum; i++) {
            lair_config = "lair_config_";
            lair_config = config[lair_config.append(std::to_string(i))];
            const std::vector<Point>& path = readPath(config, i);
            if (!isInit) {
                palace.init((size_t)config["gold"], (size_t)config["max_strength"],path[path.size() - 1]);
                isInit = true;
            }
            Lair& l = Lair(path, lair_config);
            lairs.push_back(l);
        }
    }
    void LandScape::initWithConfig(const std::string& jsonConfig, const std::string& trapConfig, const std::string& towerConfig){
        std::ifstream file(jsonConfig);
        json config;
        file >> config;
        file.close();

        std::ifstream file1(trapConfig);
        file1 >> this->trapConfig;
        file1.close();
        
        this->towerConfig = towerConfig;

        initMap(config);
        initRoad(config);
        initTowerPlaces(config);
        initLairs(config);
        //palace.init((size_t)config["gold"], (size_t)config["max_strength"]);
    }
    int LandScape::getFieldHeight() const {
        return height;
    }
    int LandScape::getFieldLength() const {
        return width;
    }
    Trap* LandScape::createTrap() {
        int type = trapConfig["effect_type"];
        Trap* res = nullptr;
        Effect e;
        switch (type) {
        case Effect::EffectType::NONE:
            e = Effect(trapConfig["duration"], trapConfig["value"], Effect::EffectType::NONE);
        case Effect::EffectType::DECELERATION:
            e = Effect(trapConfig["duration"], trapConfig["value"], Effect::EffectType::DECELERATION);
        case Effect::EffectType::POISON:
            e = Effect(trapConfig["duration"], trapConfig["value"], Effect::EffectType::POISON);
        case Effect::EffectType::WEAKNESS:
            e = Effect(trapConfig["duration"], trapConfig["value"], Effect::EffectType::WEAKNESS);
        }
        return new Trap(trapConfig["radius"], trapConfig["cost"],e,trapConfig["name"],trapConfig["sprite"]);
    }
    Tower* LandScape::createTower(bool isMagic,const Point& towerPos,Effect::EffectType type = Effect::EffectType::NONE) {
        if (!isMagic) {
            return new Tower(palace.getSprite()->getPosition(),towerPos,towerConfig);
        }
        else {
            Effect e;
            switch (type) {
            case Effect::EffectType::NONE:
                e = Effect(trapConfig["duration"], trapConfig["value"], Effect::EffectType::NONE);
            case Effect::EffectType::DECELERATION:
                e = Effect(trapConfig["duration"], trapConfig["value"], Effect::EffectType::DECELERATION);
            case Effect::EffectType::POISON:
                e = Effect(trapConfig["duration"], trapConfig["value"], Effect::EffectType::POISON);
            case Effect::EffectType::WEAKNESS:
                e = Effect(trapConfig["duration"], trapConfig["value"], Effect::EffectType::WEAKNESS);
            }
            return new MagicTower(e, palace.getSprite()->getPosition(), towerPos, towerConfig);
        }
    }
    void LandScape::addAttackingObject(Cell& cell, AbstractAttackingObject* ob) { 
        if (cell.getType() == CellType::TOWER_PLACE) {
            int cost = ((Tower*)ob)->getProperties().cost;
            if (palace.getGold() >= cost) {
                palace.takeGold(cost);
                cell.setType(CellType::TOWER, ob);
                this->addChild(ob->getSprite(), ATTACKING_OBJECTS_PRIOR);
                attackingObjects.push_back(ob);
            }
            else {
                delete ob;
                log("You can't buy it");
            }
            return;
        }
        if (cell.getType() == CellType::ROAD) {
            int cost = ((Trap*)ob)->getCost();
            if (palace.getGold() >= cost) {
                palace.takeGold(cost);
                cell.setType(CellType::TRAP, ob);
                this->addChild(ob->getSprite(), ATTACKING_OBJECTS_PRIOR);
                attackingObjects.push_back(ob);
            }
            else {
                delete ob;
                log("You can't buy it");
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
                this->addChild(e->getSprite(),ENEMY_PRIOR);
            }
        }
        if (emptyLairsFlag && enemies.empty()) {
            //������, ����� ����
            isEnd = true;
            return;
        }
        bool increment;
        for (auto iter = enemies.begin(); iter != enemies.end();) {
            increment = true;
            Enemy* e = *iter;
            if (e->isDead()) {
                palace.addGold(e->getAward());
                iter = enemies.erase(iter);
                delete e;
                increment = false;
            }
            else if (e->isOnFinish()) {
                palace.getDamage(e->getHealth());
                if (palace.isDestroyed()) {
                    //��������, ����� ����
                    isEnd = true;
                    isVictory = false;
                    return;
                }
                iter = enemies.erase(iter);
                delete e;
                increment = false;
            }
            else {
                e->tick();
            }
            if (increment) {
                ++iter;
            }
        }
        for (auto iter = attackingObjects.begin(); iter != attackingObjects.end();) {
            increment = true;
            if (instanceof<Trap,AbstractAttackingObject>(*iter)) {
                if ((*iter)->fire(enemies)) {
                    iter = attackingObjects.erase(iter);
                    increment = false;
                }
            }
            else {
                (*iter)->fire(enemies);
            }
            if(increment){
                ++iter;
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
         this->addChild(object, MAP_PRIOR);
         this->schedule(CC_SCHEDULE_SELECTOR(LandScape::update), 0.5f);
         return true;
    }
    bool LandScape::onTouchBegan(cocos2d::Touch* t, cocos2d::Event*) {
        Point p = t->getLocation();
        Point top;
        for (auto line : battlefield) {
            for (auto cell : line) {
                if (cell.getType() == CellType::ROAD || cell.getType() == CellType::TOWER_PLACE) {
                    top = cell.getTopLeft();
                    if (top.x < p.x && p.x < top.x + cell.getWidth() && top.y > p.y && p.y > top.y - cell.getHeight()) {
                        AbstractAttackingObject* ob = nullptr;
                        switch (cell.getType())
                        {
                        case CellType::ROAD:
                            ob = createTrap();
                        case CellType::TOWER_PLACE:
                            Point delta = Point(cell.getWidth() / 2.0, cell.getHeight() / 2.0);
                            Point towerPos = Point(top.x + delta.x, top.y - delta.y);
                            ob = createTower(false, towerPos);
                        }
                        addAttackingObject(cell, ob);
                    }
                }
            }
        }
        return true;
    }
    void LandScape::update(float dt) {
        if (!isEnd) {
            tick();
        }
    }
    void LandScape::run() {
        while (!isEnd) {
            tick();
        }
    }
}