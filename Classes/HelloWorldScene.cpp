/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "TDGame/lib/json/single_include/nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include "TDGame/include/LandScape.h"
#include "TDGame/include/Lair.h"
#include "TDGame/include/Enemy.h"
#include "TDGame/include/Cell.h"
using json = nlohmann::json;
Scene* HelloWorld::createScene()
{   
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    std::ifstream file("C:/Users/devsy/Desktop/GraphicsLib/my_tower_defence/Resources/Backgrounds/Levels/levels_config.json");
    json config;
    file >> config;
    file.close();
    labelTouchInfo = Label::create();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    this->addChild(labelTouchInfo);
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(x, y);
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Tower Defence", "fonts/Marker Felt.ttf", 24);
    
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }
    
    Vector<MenuItem*> MenuItems;
    float factor = 0.2;
    float deltaY = visibleSize.height * factor;
    if (config["campaign_level"] > 1) {
        auto changeItem = MenuItemImage::create("update_level.png", "update_level_clicked.png", CC_CALLBACK_1(HelloWorld::updateLevel, this));
        float changeItemX = origin.x + visibleSize.width / 2;
        float changeItemY = origin.y + visibleSize.height / 2 - deltaY;
        changeItem->setPosition(changeItemX, changeItemY);
        MenuItems.pushBack(changeItem);
    }
    auto playItem = MenuItemImage::create("Play Button.png", "Play Button Clicked.png", CC_CALLBACK_1(HelloWorld::GoToGameScene, this));
    playItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    MenuItems.pushBack(playItem);
    cocos2d::Menu* menu1 = Menu::createWithArray(MenuItems);
    menu1->setPosition(Point::ZERO);
    this->addChild(menu1);
    Label* level = Label::createWithSystemFont("Current level: " + std::to_string(config["current_level"] + 1), "Arial", 20);
    level->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + deltaY);
    this->addChild(level, 1, "current_level");
    /*
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("Level_1.png");
    if (sprite == nullptr)
    {
        problemLoading("'Level_1.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }*/
    /*auto ghost = Sprite::create("Enemies/Ghost/frame_00001.png");
    auto simpleTower = Sprite::create("SimpleTower.png");
    auto magicTower = Sprite::create("MagicTower.png");
    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + visibleSize.height / 2;
    ghost->setPosition(x, y);
    simpleTower->setPosition(x - 20, y);
    simpleTower->setScale(0.65);
    magicTower->setScale(0.65);
    magicTower->setPosition(x, y - 20);
    this->addChild(simpleTower);
    this->addChild(magicTower);
    ghost->setScale(0.2);
    //ghost->setAnchorPoint(Point(0, 0));
    cocos2d::Vector<SpriteFrame*> frames;
    frames.reserve(13);
    frames.pushBack(SpriteFrame::create("Enemies/Ghost/frame_00001.png", Rect(0, 0, 1280, 720)));
    frames.pushBack(SpriteFrame::create("Enemies/Ghost/frame_00002.png", Rect(0, 0, 1280, 720)));
    frames.pushBack(SpriteFrame::create("Enemies/Ghost/frame_00003.png", Rect(0, 0, 1280, 720)));
    frames.pushBack(SpriteFrame::create("Enemies/Ghost/frame_00004.png", Rect(0, 0, 1280, 720)));
    frames.pushBack(SpriteFrame::create("Enemies/Ghost/frame_00005.png", Rect(0, 0, 1280, 720)));
    frames.pushBack(SpriteFrame::create("Enemies/Ghost/frame_00006.png", Rect(0, 0, 1280, 720)));
    frames.pushBack(SpriteFrame::create("Enemies/Ghost/frame_00007.png", Rect(0, 0, 1280, 720)));
    frames.pushBack(SpriteFrame::create("Enemies/Ghost/frame_00008.png", Rect(0, 0, 1280, 720)));
    frames.pushBack(SpriteFrame::create("Enemies/Ghost/frame_00009.png", Rect(0, 0, 1280, 720)));
    frames.pushBack(SpriteFrame::create("Enemies/Ghost/frame_00010.png", Rect(0, 0, 1280, 720)));
    frames.pushBack(SpriteFrame::create("Enemies/Ghost/frame_00011.png", Rect(0, 0, 1280, 720)));
    frames.pushBack(SpriteFrame::create("Enemies/Ghost/frame_00012.png", Rect(0, 0, 1280, 720)));
    frames.pushBack(SpriteFrame::create("Enemies/Ghost/frame_00013.png", Rect(0, 0, 1280, 720)));
    auto animation = Animation::createWithSpriteFrames(frames,0.1);
    Animate* animate = Animate::create(animation);
    ghost->runAction(RepeatForever::create(animate));
    this->addChild(ghost,0,1);
    const Point& p = ghost->getPosition();
    //Node* n = this->getChildByTag(1);
    auto moveBy = MoveBy::create(3, Vec2(30, 20));
    auto moveTo = MoveTo::create(3, Vec2(30, 20));
    ghost->runAction(moveBy);*/
    return true;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch*, cocos2d::Event*) {
    return true;
}
void HelloWorld::updateLevel(Ref* sender) {
    std::ifstream file("C:/Users/devsy/Desktop/GraphicsLib/my_tower_defence/Resources/Backgrounds/Levels/levels_config.json");
    json config;
    file >> config;
    file.close();
    config["current_level"] = (config["current_level"] + 1) % config["campaign_level"];
    std::ofstream file1("C:/Users/devsy/Desktop/GraphicsLib/my_tower_defence/Resources/Backgrounds/Levels/levels_config.json");
    file1 << config;
    file1.close();
    Label* level = (Label*)this->getChildByName("current_level");
    level->setString("Current level: " + std::to_string((config["current_level"] + 1)));
}
void HelloWorld::GoToGameScene(cocos2d::Ref* sender)
{   
    std::ifstream file("C:/Users/devsy/Desktop/GraphicsLib/my_tower_defence/Resources/Backgrounds/Levels/levels_config.json");
    json config;
    file >> config;
    file.close();
    int current_level = config["current_level"];
    std::string folder = config["levels"][current_level];
  
    std::string landConf = folder + "/landscape_config.json";
    std::string trapConf = folder + "/Buildings/Traps/trap_config.json";
    std::string simpleTowerConf = folder + "/Buildings/Towers/tower_config.json";
    std::string magicTowerConf = folder + "/Buildings/Towers/magic_tower_config.json";

    /*std::string landConf = "C:/Users/devsy/Desktop/GraphicsLib/my_tower_defence/Resources/Backgrounds/Levels/Level_1/landscape_config.json";
    std::string trapConf = "C:/Users/devsy/Desktop/GraphicsLib/my_tower_defence/Resources/Backgrounds/Levels/Level_1/Buildings/Traps/trap_config.json";
    std::string simpleTowerConf = "C:/Users/devsy/Desktop/GraphicsLib/my_tower_defence/Resources/Backgrounds/Levels/Level_1/Buildings/Towers/tower_config.json";
    std::string magicTowerConf = "C:/Users/devsy/Desktop/GraphicsLib/my_tower_defence/Resources/Backgrounds/Levels/Level_1/Buildings/Towers/magic_tower_config.json";*/
    auto scene = TowerDefence::LandScape::createScene(landConf,trapConf, simpleTowerConf,magicTowerConf);
    Director::getInstance()->replaceScene(TransitionFade::create(1.5, scene));
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
