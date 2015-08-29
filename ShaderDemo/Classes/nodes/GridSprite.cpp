//
//  GridSprite.cpp
//  ShaderDemo
//
//  Created by 林跃南 on 15/8/1.
//
//

#include "GridSprite.h"
#define FLOAT_ZERO 0.000001

GridSprite::GridSprite()
:_speed(3.0)
,_animation(0)
,_glProgramState(0)
,_isMove(false)
,_isUse(false)
,_enable(1)
{
    _targetPos = Vec2(0,0);
}

GridSprite::~GridSprite()
{
    CC_SAFE_RELEASE(_animation);
}

GridSprite* GridSprite::create(std::string filename)
{
    GridSprite* pRef = new GridSprite();
    if (pRef && pRef->init(filename))
    {
        pRef->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRef);
    }
    return pRef;
}

bool GridSprite::init(std::string filename)
{
    if (!Sprite::initWithFile(filename)) {
        return false;
    }
    
    auto winSize = Director::getInstance()->getWinSize();
    
    //program
    auto _program = GLProgram::createWithFilenames("blur.vert", "blurx.frag");
    _glProgramState = GLProgramState::getOrCreateWithGLProgram(_program);
    _glProgramState->setUniformVec2("u_resolution",winSize);
    _glProgramState->setUniformInt("u_enable",0);
    setGLProgramState(_glProgramState);
    setGLProgram(_program);
    
    //animation
    char str[100]={0};
    _animation = Animation::create();
    for(int i = 1;i < 9 ; i++)
    {
        sprintf(str,"hero_run%d.png",i);
        _animation->addSpriteFrameWithFile(str);
    }
    _animation->setDelayPerUnit(0.2f);
    _animation->setLoops(-1);
    _animation->retain();
    
    scheduleUpdate();
    
    return true;
}

void GridSprite::update(float dt)
{
    if (!_isUse) {
        return;
    }
    if (abs(getPositionX() - _targetPos.x) > FLOAT_ZERO + _speed)
    {
        _glProgramState->setUniformInt("u_enable",_enable);
        setPositionX(getPositionX() + _speed);
        if (!_isMove) {
            runAction(Animate::create(_animation));
            _isMove = true;
        }
    }
    else
    {
        _glProgramState->setUniformInt("u_enable",0);
        stopAllActions();
        _isMove = false;
    }
}

void GridSprite::moveToPositon(cocos2d::Vec2 pos)
{
    _targetPos = pos;
    _isUse = true;
}

void GridSprite::unuse()
{
    _isUse = false;
}