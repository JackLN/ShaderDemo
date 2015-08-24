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
    
    typedef struct {
        float Position[3];
        float Color[4];
        float TexCoord[2];
    }Vertex;
    
    //virtual void visit(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags);
    void onDraw(const Mat4& transform, uint32_t flags);
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);
    
private:
    
    void setdefault();
    
    void calVectics();
    Vertex _vertices[4];
    
    CustomCommand _command;
    GLProgram* program;
    
    //texture maybe not
    GLuint _textureID;
    std::string _textureName;
    
    //vertexbuffer & indexbuffer
    GLuint vertexBuffer;
    GLuint indexBuffer;
    
    //locations
    GLint _colorLocation;
    GLint _positionLocation;
    GLint _textureLocation;
    
    //uniform
    GLuint _textureUniform;
};


#endif /* defined(__ShaderDemo__GridNode__) */
