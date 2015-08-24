//
//  GridNode.h
//  ShaderDemo
//
//  Created by 林跃南 on 15/7/26.
//
//

#ifndef __ShaderDemo__GridNode__
#define __ShaderDemo__GridNode__

#include <stdio.h>
#include "cocos2d.h"
//#include "RectCommand.h"

USING_NS_CC;


class GridNode : public Node {
public:
    
    GridNode();
    ~GridNode();
    
    virtual bool init();
    static GridNode* create();
    
public:
    
    virtual void visit(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags);
    void onDraw();
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);
    
public:
    
    CustomCommand _command;
    
};


#endif /* defined(__ShaderDemo__GridNode__) */
