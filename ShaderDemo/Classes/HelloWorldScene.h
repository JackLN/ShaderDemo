#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "GridNode.h"
class HelloWorld : public cocos2d::Layer
{
public:
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(HelloWorld);
    
public:
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
private:
    
    Size winSize;
};

#endif // __HELLOWORLD_SCENE_H__
