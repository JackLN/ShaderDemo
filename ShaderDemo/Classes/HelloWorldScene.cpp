#include "HelloWorldScene.h"
#include "nodes/GridNode.h"
#include "nodes/RectShadeNode.h"
#include "nodes/GridSprite.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
   
    if ( !Layer::init() )
    {
        return false;
    }
    
    winSize = Director::getInstance()->getWinSize();
    
    
    auto hero1 = GridSprite::create("hero_run1.png");
    hero1->setPosition(Vec2(100,winSize.height/3));
    hero1->setName("hero");
    hero1->setScale(2);
    addChild(hero1);
    auto hero2 = GridSprite::create("hero_run1.png");
    hero2->setPosition(Vec2(100,winSize.height/3*2));
    hero2->setName("hero2");
    hero2->setScale(2);
    hero2->setEnable(0);
    addChild(hero2);
    
    
    //RectShadeNode* rsNode = RectShadeNode::create(Rect(400, 200, 200, 200),Color4B(0,0,0,220), 100);
    //rsNode->drawReckNode(Rect(100,100,100,100), Color4B(0,0,0,100), 200);
    //addChild(rsNode);

    
    
    //    GridNode* gridNode = GridNode::create("hero.png");
    //    //gridNode->setAnchorPoint(Point(0.5f, 0.5f));
    //    //gridNode->setScale(3.0);
    //    gridNode->setPosition(winSize/2-gridNode->getContentSize()/2);
    //    addChild(gridNode);
    
    
    
    auto sp = Sprite::create("HelloWorld.png");
    sp->setScale(3.0);
    sp->setPosition(winSize/2);
    addChild(sp,-1);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    
    return true;
}


bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    return true;
}

void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    ((GridSprite*)getChildByName("hero"))->moveToPositon(Vec2(800,winSize.height/2));
    ((GridSprite*)getChildByName("hero2"))->moveToPositon(Vec2(800,winSize.height/2));
}
