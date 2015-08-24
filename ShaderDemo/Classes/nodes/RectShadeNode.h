//
//  RectShadeNode.h
//  ShaderDemo
//
//  Created by 林跃南 on 15/8/23.
//
//

#ifndef __ShaderDemo__RectShadeNode__
#define __ShaderDemo__RectShadeNode__

#include <stdio.h>
#include "cocos2d.h"


USING_NS_CC;


class RectShadeNode : public Node {
    
public:
    
    RectShadeNode();
    ~RectShadeNode();
    
    static RectShadeNode* create(Rect rect,Color4B color,float length);
    virtual bool init(Rect rect,Color4B color,float length);
    
    void onDraw(const Mat4 &transform, uint32_t flags);
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    void drawReckNode(Rect rect,Color4B color,float length);
    
protected:
    
    void ensureCapacity(int count);
    
    
    Vec2* _positions;
    float _length;
    
    int _bufferCapacity;
    GLsizei _bufferCount;
    V2F_C4B_T2F* _buffer;
    
    
    GLuint _vbo;
    GLuint _vao;
    
    
    GLuint m_uniformposition1;
    GLuint m_uniformposition2;
    GLuint m_uniformposition3;
    GLuint m_uniformposition4;
    GLuint m_uniformlenght;
    GLuint m_uniformresolution;
    
    
    BlendFunc _blendFunc;
    CustomCommand _customCommand;
    GLProgram* _program;
    GLProgramState* _state;
    
private:
    
    bool _dirty;
};

#endif /* defined(__ShaderDemo__RectShadeNode__) */
