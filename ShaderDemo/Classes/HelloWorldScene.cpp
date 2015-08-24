#include "HelloWorldScene.h"
#include "nodes/GridNode.h"
#include "nodes/RectShadeNode.h"

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
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    sp = Sprite::create("HelloWorld.png");
    sp->setScale(3.0);
    sp->setPosition(visibleSize/2);
    addChild(sp,0);
    
    RectShadeNode* rsNode = RectShadeNode::create(Rect(400, 200, 200, 200),Color4B(0,0,0,220), 100);
    //rsNode->drawReckNode(Rect(100,100,100,100), Color4B(0,0,0,100), 200);
    addChild(rsNode);
    

    //GridNode* gnode = new GridNode();
//    gnode = GridNode::create();
//    gnode->setPosition(100,100);
//    //gnode->setScale(0,1);
//    addChild(gnode);
    

//    
//    auto sp1 = Sprite::create("HelloWorld.png");
//    
//    sp1->setPosition(200,200);
//    sp->addChild(sp1);
//    
//    for (int i = 0; i < 50; i++) {
//        auto sp1 = Sprite::create("HelloWorld.png");
//        
//        sp1->setPosition(100,100);
//        sp->addChild(sp1,0);
//    }
//    
//    scheduleUpdate();
    
    return true;
}

void HelloWorld::update(float dt)
{

    sp->getPosition();

    gnode->getPosition();
    
}



void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
