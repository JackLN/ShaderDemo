//
//  GridNode.cpp
//  ShaderDemo
//
//  Created by 林跃南 on 15/7/26.
//
//

#include "GridNode.h"

GridNode::GridNode()
{
    
}

GridNode::~GridNode()
{
    
}

bool GridNode::init()
{
    if (!Node::init()) {    
        return false;
    }
    
    return true;
}

void GridNode::onDraw()
{

}

GridNode* GridNode::create()
{
    GridNode* pRe = new GridNode();
    if (pRe && pRe->init()) {
        return pRe;
    }else
    {
        return NULL;
    }
}

void GridNode::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags){
    
    Node::visit(renderer, parentTransform, parentFlags);
    _command.init(_globalZOrder);
    _command.func = CC_CALLBACK_0(GridNode::onDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_command);
    
}

void GridNode::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    
}

