//
//  CalculatePosition.h
//  ShaderDemo
//
//  Created by 林跃南 on 15/7/31.
//
//

#ifndef ShaderDemo_CalculatePosition_h
#define ShaderDemo_CalculatePosition_h

#include "cocos2d.h"

USING_NS_CC;

inline float transLength(float tar,float glabal)
{
    return tar / glabal * 2 - 1;
}

inline Vec2 transPosition(Vec2 pos,Size FrameSize)
{
    return Vec2(transLength(pos.x,FrameSize.width),transLength(pos.y,FrameSize.height));
}

inline Vec2 mutiPos(Vec2 p1,Vec2 p2)
{
    return Vec2(p1.x*p2.x,p1.y*p2.y);
}





#endif
