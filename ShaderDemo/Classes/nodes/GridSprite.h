//
//  GridSprite.h
//  ShaderDemo
//
//  Created by 林跃南 on 15/8/1.
//
//

#ifndef __ShaderDemo__GridSprite__
#define __ShaderDemo__GridSprite__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class GridSprite : public Sprite {
public:
    
    GridSprite();
    ~GridSprite();
    
    static GridSprite* create(std::string filename);
    virtual bool init(std::string filename);
    virtual void update(float dt);
    
    void moveToPositon(Vec2 pos);
    
    CC_SYNTHESIZE(float, _speed, Speed);
    CC_SYNTHESIZE(Vec2, _targetPos, TargetPos);
    CC_SYNTHESIZE(bool, _isMove, IsMove);
    CC_SYNTHESIZE(int, _enable, Enable);
    
    void unuse();
private:
    
    Animation* _animation;
    GLProgramState* _glProgramState;
    bool _isUse;
    
};
#endif /* defined(__ShaderDemo__GridSprite__) */
