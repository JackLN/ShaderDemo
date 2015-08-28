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
    
    auto winSize = Director::getInstance()->getWinSize();
    
    
    auto sprite = Sprite::create("hero.png");
    
    auto _program = GLProgram::createWithFilenames("blur.vert", "blur.frag");
    auto glProgramState = GLProgramState::getOrCreateWithGLProgram(_program);
    glProgramState->setUniformVec2("u_resolution",winSize);
    sprite->setGLProgramState(glProgramState);
    sprite->setGLProgram(_program);
    
    sprite->setPosition(winSize/2);
    addChild(sprite);
    
    
    
//    GridNode* gridNode = GridNode::create("hero.png");
//    //gridNode->setAnchorPoint(Point(0.5f, 0.5f));
//    //gridNode->setScale(3.0);
//    gridNode->setPosition(winSize/2-gridNode->getContentSize()/2);
//    addChild(gridNode);

    
//    auto sp = Sprite::create("HelloWorld.png");
//    
//    
//    sp->setScale(3.0);
//    sp->setPosition(visibleSize/2);
//    addChild(sp,0);
    
    //RectShadeNode* rsNode = RectShadeNode::create(Rect(400, 200, 200, 200),Color4B(0,0,0,220), 100);
    //rsNode->drawReckNode(Rect(100,100,100,100), Color4B(0,0,0,100), 200);
    //addChild(rsNode);

    
    return true;
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
