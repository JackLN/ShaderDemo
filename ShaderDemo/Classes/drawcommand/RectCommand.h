//
//  RectCommand.h
//  ShaderDemo
//
//  Created by 林跃南 on 15/7/29.
//
//

#ifndef __ShaderDemo__RectCommand__
#define __ShaderDemo__RectCommand__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class RectCommand : public CustomCommand{
public:
    
    RectCommand();
    void init(int globalOrder,GLProgram* shader,Vec3* vertices,Color4F* colors,GLuint* indices,int indexCount, const Mat4& mv);
    
private:
    
    void useMaterial();
    void onDraw();
    
    Color4F* _squareColors;
    Vec3* _noMVPVertices;
    GLuint* _indices;
    int _vertexCount;
    Mat4 _mv;
    GLProgram* _shader;
    
};

#endif /* defined(__ShaderDemo__RectCommand__) */
