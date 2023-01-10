#include "../include/LandScape.h"
#include "../include/Cell.h"
#include "../include/Tower.h"
#include "../include/Trap.h"
#include "../include/Lair.h"
#include "../include/TowerDefence.h"
#include "GameOverScene.h"
#include <fstream>
namespace TowerDefence {
    cocos2d::Scene* LandScape::createScene(const std::string& jsonConfig,const std::string& trapConfig,const std::string& simpleTowerConfig, const std::string& magicTowerConfig) {
        auto scene = Scene::create();
        LandScape* l = new LandScape();
        l->initWithConfig(jsonConfig,trapConfig, simpleTowerConfig, magicTowerConfig);
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
    void LandScape::updatePalaceParams() {
        Label* gold = (Label*)this->getChildByName("palace_gold");
        gold->setString("gold: " + std::to_string(palace.getGold()));
        Label* strength = (Label*)this->getChildByName("palace_strength");
        strength->setString("strength: " + std::to_string(palace.getStrength()));
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
            drawNode->drawRect(topLeft, topLeft + Point(battlefield[i][j].getWidth(), -battlefield[i][j].getHeight()), Color4F::BLACK);
            this->addChild(drawNode,TOWER_PLACES_PRIOR);
        }
    }
    void LandScape::initLairs(const json& config) {
        size_t lairsNum = config["lairs_num"];
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
    void LandScape::initWithConfig(const std::string& landscapeConfig, const std::string& trapConfig, const std::string& simpleTowerConfig, const std::string& magicTowerConfig){
        std::ifstream file(landscapeConfig);
        json config;
        file >> config;
        file.close();

        std::ifstream file1(trapConfig);
        file1 >> this->trapConfig;
        file1.close();
  

        std::ifstream simple(simpleTowerConfig);
        simple >> this->simpleTowerConfig;
        simple.close();

        std::ifstream magic(magicTowerConfig);
        magic >> this->magicTowerConfig;
        magic.close();

        std::ifstream file2("C:/Users/devsy/Desktop/GraphicsLib/my_tower_defence/Resources/Effects/effects_config.json");
        file2 >> this->effectConfig;
        file2.close();

        initMap(config);
        initRoad(config);
        initTowerPlaces(config);
        initLairs(config);

        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        float factor_h = 0.08;
        float factor_w = 0.12;
        float delta_h = visibleSize.height * factor_h;
        float delta_w = visibleSize.width * factor_w;
        float strength_x = origin.x + visibleSize.width - delta_w;
        float strength_y = origin.y + visibleSize.height - delta_h;
        float gold_x = strength_x, gold_y = strength_y - delta_h;
        Effect::EffectType trap_effect_type = Effect::getType(this->trapConfig["effect_type"]);
        Effect::EffectType tower_effect_type = Effect::getType(this->magicTowerConfig["effect_type"]);
        Label* strength = Label::createWithSystemFont("strength: " + std::to_string(palace.getStrength()),"Arial",15);
        Label* gold = Label::createWithSystemFont("gold: " + std::to_string(palace.getGold()), "Arial", 15);
        Label* trap_effect = Label::createWithSystemFont("Trap: " + Effect::to_string(trap_effect_type), "Arial", 15);
        Label* tower_type = Label::createWithSystemFont("Tower: simple", "Arial", 15);
        Label* tower_effect = Label::createWithSystemFont("Tower eff.: " + Effect::to_string(tower_effect_type), "Arial", 15);
        //Point palacePos = palace.getSprite()->getPosition();
        //float px = 0.1,py = 0.1;
        //strength->setPosition(palacePos.x * (1 + px), palacePos.y * (1.0 + py));
        //gold->setPosition(palacePos.x * (1 + px), palacePos.y * (1.0 - py));
        strength->setPosition(strength_x, strength_y);
        gold->setPosition(gold_x, gold_y);
        trap_effect->setPosition(gold_x, gold_y - delta_h);
        tower_type->setPosition(gold_x, gold_y - 2.0 * delta_h);
        tower_effect->setPosition(gold_x, gold_y - 3.0 * delta_h);
        this->addChild(strength, 10000, "palace_strength");
        this->addChild(gold, 10000, "palace_gold");
        this->addChild(trap_effect, 10000, "trap_effect");
        this->addChild(tower_type, 10000, "tower_type");
        this->addChild(tower_effect, 10000, "tower_effect");
    }
    int LandScape::getFieldHeight() const {
        return height;
    }
    int LandScape::getFieldLength() const {
        return width;
    }
    Trap* LandScape::createTrap(const Point& trapPos) {
        int type = trapConfig["effect_type"];
        Trap* res = nullptr;
        Effect e = Effect(effectConfig["type"][type]["duration"], effectConfig["type"][type]["value"],Effect::getType(type));
        res = new Trap(trapConfig["radius"], trapConfig["cost"],e,trapConfig["name"],trapConfig["sprite"]);
        res->getSprite()->setPosition(trapPos);
        return res;
    }
    Tower* LandScape::createTower(bool isMagic,const Point& towerPos) {
        if (!isMagic) {
            return new Tower(palace.getSprite()->getPosition(),towerPos,simpleTowerConfig);
        }
        else {
            int type = magicTowerConfig["effect_type"];
            Effect e = Effect(effectConfig["type"][type]["duration"], effectConfig["type"][type]["value"], Effect::getType(type));
            return new MagicTower(e, palace.getSprite()->getPosition(), towerPos, magicTowerConfig);
        }
    }
    void LandScape::updateTowerLevel(Tower* t) {
        unsigned int cost = t->getProperties().cost;
        if (t->updateLevel(palace.getGold())) {
            palace.takeGold(cost);
        }
        else {
            Label* l = Label::createWithSystemFont("Can't update tower","Arial",10);
            Point p = t->getSprite()->getPosition();
            l->setPosition(p);
            this->addChild(l,10000);
            float h = 70.0;
            MoveTo* moveTo = MoveTo::create(1.0f,p + Point(0.0,h));
            l->runAction(moveTo);
            l->removeFromParent();
            delete l;
        }
    }
    void LandScape::addAttackingObject(Cell& cell, AbstractAttackingObject* ob) { 
        if (cell.getType() == CellType::TOWER_PLACE) {
            int cost = ((Tower*)ob)->getProperties().cost;
            if (palace.getGold() >= cost) {
                palace.takeGold(cost);
                updatePalaceParams();
                cell.setType(CellType::TOWER, ob);
                this->addChild(ob->getSprite(), ATTACKING_OBJECTS_PRIOR);
                attackingObjects.push_back(&cell);
                log("You have bought tower");
            }
            else {
                delete ob;
                log("You can't buy tower");
            }
            return;
        }
        if (cell.getType() == CellType::ROAD) {
            int cost = ((Trap*)ob)->getCost();
            if (palace.getGold() >= cost) {
                palace.takeGold(cost);
                updatePalaceParams();
                cell.setType(CellType::TRAP, ob);
                this->addChild(ob->getSprite(), ATTACKING_OBJECTS_PRIOR);
                attackingObjects.push_back(&cell);
                log("You have bought trap");
            }
            else {
                delete ob;
                log("You can't buy trap");
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
            //Victory, game over
            isEnd = true;
            return;
        }
        bool increment;
        for (auto iter = enemies.begin(); iter != enemies.end();) {
            increment = true;
            Enemy* e = *iter;
            if (e->isDead()) {
                palace.addGold(e->getAward());
                updatePalaceParams();
                iter = enemies.erase(iter);
                e->tick();
                increment = false;
            }
            else if (e->isOnFinish()) {
                palace.getDamage(e->getHealth());
                updatePalaceParams();
                if (palace.isDestroyed()) {
                    //Fail, game over
                    isEnd = true;
                    isVictory = false;
                    return;
                }
                iter = enemies.erase(iter);
                e->tick();
                increment = false;
            }
            else {
                e->tick();
                if (e->isDead()) {
                    palace.addGold(e->getAward());
                    updatePalaceParams();
                    iter = enemies.erase(iter);
                    increment = false;
                }
            }
            if (increment) {
                ++iter;
            }
        }
        for (auto iter = attackingObjects.begin(); iter != attackingObjects.end();) {
            increment = true;
            if (instanceof<Trap,AbstractAttackingObject>((AbstractAttackingObject*)(*iter)->getObject())) {
                if (((Trap*)(*iter)->getObject())->fire(enemies)) {
                    (*iter)->setType(CellType::ROAD, nullptr);
                    iter = attackingObjects.erase(iter);
                    increment = false;
                }
            }
            else {
                ((Tower*)(*iter)->getObject())->fire(enemies);
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
    void LandScape::menu_change_tower_type(Ref* sender) {
         currentTowerIsMagic = !currentTowerIsMagic;
         std::string type = currentTowerIsMagic ? "Tower: magic" : "Tower: simple";
         Label* l = (Label*)this->getChildByName("tower_type");
         l->setString(type);
    }
    bool LandScape::init() {
         auto visibleSize = Director::getInstance()->getVisibleSize();
         Vec2 origin = Director::getInstance()->getVisibleOrigin();
         this->addChild(object, MAP_PRIOR);

         auto touchListener = EventListenerTouchOneByOne::create();

         touchListener->onTouchBegan = CC_CALLBACK_2(LandScape::onTouchBegan, this);

         _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
         
         Vector<MenuItem*> MenuItems;
         float factor_h = 0.1;
         float delta_h = visibleSize.height * factor_h;
         std::string trap_type = "trap_type.png";
         std::string trap_type_clicked = "trap_type_clicked.png";
         auto trapEffectTypeItem = MenuItemImage::create(trap_type, trap_type_clicked, CC_CALLBACK_1(LandScape::menu_change_trap_effect, this));
         float trap_x = origin.x + visibleSize.width - trapEffectTypeItem->getContentSize().width / 2;
         float trap_y = origin.y + trapEffectTypeItem->getContentSize().height / 2 + delta_h;
         trapEffectTypeItem->setPosition(trap_x, trap_y);
         trapEffectTypeItem->setScale(0.5);

         MenuItems.pushBack(trapEffectTypeItem);


         std::string type1 = "type.png";
         std::string type2 = "type_clicked.png";
         auto towerTypeItem = MenuItemImage::create(type1,type2,CC_CALLBACK_1(LandScape::menu_change_tower_type,this));
         float x = origin.x + visibleSize.width - towerTypeItem->getContentSize().width / 2;
         float y = origin.y + towerTypeItem->getContentSize().height / 2;
         towerTypeItem->setPosition(x, y);
         towerTypeItem->setScale(0.5);
        
         MenuItems.pushBack(towerTypeItem);

         std::string tower_effect = "tower_effect.png";
         std::string tower_effect_clicked = "tower_effect_clicked.png";
         auto towerEffectItem = MenuItemImage::create(tower_effect, tower_effect, CC_CALLBACK_1(LandScape::menu_change_tower_effect, this));
         towerEffectItem->setPosition(trap_x, trap_y + delta_h);
         towerEffectItem->setScale(0.5);

         MenuItems.pushBack(towerEffectItem);

         auto menu = Menu::createWithArray(MenuItems);
         menu->setPosition(Vec2::ZERO);
         this->addChild(menu, 1);
         this->schedule(CC_SCHEDULE_SELECTOR(LandScape::update), 0.5f);
         return true;
    }
    bool LandScape::onTouchBegan(cocos2d::Touch* t, cocos2d::Event*) {
        Point p = t->getLocation();
        Point top;
        for (auto line = battlefield.begin(); line != battlefield.end(); ++line) {
            for (auto cell_iter = (*line).begin(); cell_iter != (*line).end(); ++cell_iter) {
                Cell& cell = *cell_iter;
                top = cell.getTopLeft();
                if (top.x < p.x && p.x < top.x + cell.getWidth() && top.y > p.y && p.y > top.y - cell.getHeight()) {
                    if (cell.getType() == CellType::ROAD || cell.getType() == CellType::TOWER_PLACE) {
                        top = cell.getTopLeft();
                        AbstractAttackingObject* ob = nullptr;
                        Point delta = Point(cell.getWidth() / 2.0, cell.getHeight() / 2.0);
                        Point pos = Point(top.x + delta.x, top.y - delta.y);
                        switch (cell.getType())
                        {
                          case CellType::ROAD:
                               ob = createTrap(pos);
                               break;
                          case CellType::TOWER_PLACE:
                               int type = trapConfig["effect_type"];
                               ob = createTower(currentTowerIsMagic, pos);
                               break;
                        }
                        addAttackingObject(cell, ob);
                        return true;
                    } else {
                        if (cell.getType() == CellType::TOWER) {
                            top = cell.getTopLeft();
                            updateTowerLevel((Tower*)cell.getObject());
                            return true;
                        }
                    }
                }
            }
        }
        return true;
    }
    void LandScape::menu_change_trap_effect(Ref* sender) {
        int effectsNum = effectConfig["type"].size() - 1;
        trapConfig["effect_type"] = (trapConfig["effect_type"] + 1) % effectsNum;
        Effect::EffectType type = Effect::getType(trapConfig["effect_type"]);
        std::string str_type = Effect::to_string(type);
        Label* l = (Label*)this->getChildByName("trap_effect");
        l->setString("Trap: " + str_type);
    }

    void LandScape::menu_change_tower_effect(Ref* sender) {
        int effectsNum = effectConfig["type"].size() - 1;
        magicTowerConfig["effect_type"] = (magicTowerConfig["effect_type"] + 1) % effectsNum;
        Effect::EffectType type = Effect::getType(magicTowerConfig["effect_type"]);
        std::string str_type = Effect::to_string(type);
        Label* l = (Label*)this->getChildByName("tower_effect");
        l->setString("Tower eff.: " + str_type);
    }
    void LandScape::update(float dt) {
        if (!isEnd) {
            tick();
        }
        else {
            if (!_isRun) {
                if (isVictory) {
                    log("You have won!!!!!!");

                }
                else {
                    log("You lose!!!");
                }
                _isRun = true;
                auto scene = GameOver::createScene(isVictory);
                Director::getInstance()->replaceScene(TransitionFade::create(1.5, scene));
            }
        }
    }
}