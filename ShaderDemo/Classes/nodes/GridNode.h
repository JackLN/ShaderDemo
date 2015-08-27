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
    
    virtual bool init(std::string fileName);
    static GridNode* create(std::string fileName);
    
public:
    
    //virtual void visit(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags);
    void onDraw(const Mat4& transform, uint32_t flags);
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);
    bool onTouchbegan(Touch *touch, Event *unused_event);
    void onTouchEnded(Touch *touch, Event *unused_event);
    
private:
    
    void ensureCapacity(int count);
    void setUpBuffer(const Vec2 &lb, const Vec2 &lt, const Vec2 &rt, const Vec2& rb, const Color4B &color);
    
    CustomCommand _command;
    GLProgram* program;
    
    //texture maybe not
    GLuint _textureID;
    std::string _textureName;
    
    //vertexbuffer & indexbuffer
    GLsizei _bufferCount;
    GLuint _vbo;
    V2F_C4B_T2F* _buffer;
    
    int _bufferCapacity;
    
    bool _enable;
};


#endif /* defined(__ShaderDemo__GridNode__) */
