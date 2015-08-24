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

inline Vec2 transPosition(Vec2 pos,Vec2 FrameSize)
{
    return Vec2(transLength(pos.x,FrameSize.x),transLength(pos.y,FrameSize.y));
}





#endif
