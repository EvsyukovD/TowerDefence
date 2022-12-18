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
//USING_NS_CC;
using json = nlohmann::json;
Scene* HelloWorld::createScene()
{   
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
    //return HelloWorld::create();
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
    //labelTouchInfo = Label::createWithSystemFont("Touch or clicksomewhere to begin", "Arial", 30);
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
    /*auto ghost = Sprite::create("Backgrounds/Levels/Level_1/Enemies/Ghost/frame_1.png");
    std::shared_ptr<Sprite> p(ghost);
    ghost->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    auto move = MoveBy::create(1.0,Vec2(30, 30));
    ghost->runAction(move);
    auto backgroundSprite = Sprite::create("Level_1.png");
    backgroundSprite->setScale(0.8);
    backgroundSprite->setAnchorPoint(Vec2(0,1));
    backgroundSprite->setPosition(Vec2(origin.x,origin.y + visibleSize.height));
    float width = 5, height = 5;
    this->addChild(backgroundSprite);
    this->addChild(ghost,0,1);
    auto vis = backgroundSprite->getContentSize();
    for (int i = 0; i * height< vis.height; i++) {
        nodes.push_back(std::vector<Point>());
        for (int j = 0; j * width< vis.width; j++) {
            DrawNode* node = DrawNode::create();
            node->setAnchorPoint(Vec2(0,1));
            Vec2 v = Vec2(origin.x + j * width, origin.y + visibleSize.height - i * height);
            nodes[i].push_back(v);
            node->drawRect(v, Vec2(origin.x + 5 + j * width, origin.y + visibleSize.height - 5 - i * height), Color4F::BLACK);
            this->addChild(node);
        }
    }*/
    /*Vec2 &v = Vec2(origin.x, origin.y + visibleSize.height);
    Vec2& dest = Vec2(origin.x + 5, origin.y + visibleSize.height - 5);
    auto backgroundSprite = Sprite::create("Backgrounds/Background.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    Point o = Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);*/
    auto playItem = MenuItemImage::create("Play Button.png", "Play Button Clicked.png", CC_CALLBACK_1(HelloWorld::GoToGameScene, this));
    playItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    cocos2d::Menu* menu1 = Menu::create(playItem, NULL);
    menu1->setPosition(Point::ZERO);
    this->addChild(menu1);
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
void HelloWorld::GoToGameScene(cocos2d::Ref* sender)
{
   // TowerDefence::LandScape l;
    //l.initWithConfig("C:/Users/devsy/Desktop/GraphicsLib/my_tower_defence/Resources/Backgrounds/Levels/Level_1/landscape_config.json");
    std::string conf = "C:/Users/devsy/Desktop/GraphicsLib/my_tower_defence/Resources/Backgrounds/Levels/Level_1/landscape_config.json";
    auto scene = TowerDefence::LandScape::createScene(conf);
    //l.getSprite()->setPosition(Point::ZERO);
    //scene->addChild(l.getSprite().get());
    Director::getInstance()->replaceScene(TransitionFade::create(1.5, scene));
    //l.init();
   /*Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto scene = Scene::create();//GameScene::createScene();
    auto layer = Layer::create();
    auto label = Label::createWithTTF("Tower Defence", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - label->getContentSize().height));
    auto backgroundSprite = Sprite::create("Backgrounds/Levels/Level_1/Level_1.png");
    backgroundSprite->setScale(0.8);
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    scene->addChild(backgroundSprite);
    scene->addChild(layer);
    scene->addChild(label);
    Director::getInstance()->replaceScene(TransitionFade::create(1.5, scene));*/
   /* auto closeItem = MenuItemImage::create(
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
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - 102, origin.y + visibleSize.height / 2 + 9));
        const Point& pos = closeItem->getPosition();
        std::ofstream file("C:/Users/devsy/Desktop/GraphicsLib/my_tower_defence/Resources/Backgrounds/Levels/Level_1/path.txt");
        file << "Button posx: " << pos.x << " posy: " << pos.y << std::endl;
        file.close();
    }
    scene->addChild(closeItem);*/
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
