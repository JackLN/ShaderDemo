//
//  GridNode.cpp
//  ShaderDemo
//
//  Created by 林跃南 on 15/7/26.
//
//

#include "GridNode.h"
#include "CalculatePosition.h"

#define TEX_COORD_MAX   1
GridNode::GridNode()
{
    _textureName = "HelloWorld.png";
}

GridNode::~GridNode()
{
    
}

bool GridNode::init()
{
    if (!Node::init()) {
        return false;
    }

    //program
    program = new GLProgram;
    program->initWithFilenames("textureVertexShader.vert", "textureFragmentShader.frag");
    program->link();
    program->updateUniforms();

    
    //textureID
    _textureID = Director::getInstance()->getTextureCache()->addImage(_textureName)->getName();
    
    //vbo
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    
    //vbo index
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    
    setdefault();
    
    return true;
}

void GridNode::calVectics()
{
    // 2---1
    // |   |
    // 3---0
    
    Vec2 pos = getPosition();
    if (getParent()) {
        Vec2 pos = getPosition() + getParent()->getPosition();
    }
    
    Size frameSize = Director::getInstance()->getVisibleSize();
    
    Vec2 re;
    //0
    re = pos + mutiPos(Vec2(_contentSize.width,-_contentSize.height)
                            ,Vec2(1-_anchorPoint.x,_anchorPoint.y));
    re = transPosition(re, frameSize);
    _vertices[0] = {{re.x,re.y,0}, {1, 1, 1, 1}, {TEX_COORD_MAX, TEX_COORD_MAX}};
    
    //1
    re = pos + mutiPos(Vec2(_contentSize.width,_contentSize.height)
                       ,Vec2(1-_anchorPoint.x,1-_anchorPoint.y));
    re = transPosition(re, frameSize);
    _vertices[1] = {{re.x,re.y,0}, {1, 1, 1, 1}, {TEX_COORD_MAX, 0}};
    
    //2
    re = pos + mutiPos(Vec2(-_contentSize.width,_contentSize.height)
                       ,Vec2(_anchorPoint.x,1-_anchorPoint.y));
    re = transPosition(re, frameSize);
    _vertices[2] = {{re.x,re.y,0}, {1, 1, 1, 1}, {0, 0}};
    
    //3
    re = pos + mutiPos(Vec2(-_contentSize.width,-_contentSize.height)
                       ,Vec2(_anchorPoint.x,_anchorPoint.y));
    re = transPosition(re, frameSize);
    _vertices[3] = {{re.x,re.y,0}, {1, 1, 1, 1}, {0, TEX_COORD_MAX}};

}


void GridNode::onDraw(const Mat4& transform, uint32_t flags)
{
    //push matrix
//    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
//    Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
//    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
//    Director::getInstance()->loadIdentityMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    
    //programe
    
    
    program->use();
    program->setUniformsForBuiltins();

    
    //calculate & get _vertices[4]
    calVectics();
    
    _positionZ = -1;
    
    _vertices[0] = {{300, 100, _positionZ}, {1, 0, 0, 1}, {TEX_COORD_MAX, 0}};
    _vertices[1] = {{300, 300, _positionZ}, {0, 1, 0, 1}, {TEX_COORD_MAX, TEX_COORD_MAX}};
    _vertices[2] = {{100, 300, _positionZ}, {0, 0, 1, 1}, {0, TEX_COORD_MAX}};
    _vertices[3] = {{100, 100, _positionZ}, {0, 0, 0, 1}, {0, 0}};

    
    GLubyte indices[] = {
        0, 1, 2,
        2, 3, 0,
    };
    
    //bind
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    //setting
    _positionLocation = glGetAttribLocation(program->getProgram(), "a_position");
    _colorLocation = glGetAttribLocation(program->getProgram(), "a_color");
    _textureLocation = glGetAttribLocation(program->getProgram(), "TextureCoord");
    _textureUniform = glGetAttribLocation(program->getProgram(), "CC_Texture0");
    
    //programe
    //program->use();
    //program->setUniformsForBuiltins();
    
    //enable
    glEnableVertexAttribArray(_positionLocation);
    glEnableVertexAttribArray(_colorLocation);
    glEnableVertexAttribArray(_textureLocation);
    
    //pointer
    glVertexAttribPointer(_positionLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Position));
    glVertexAttribPointer(_colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Color));
    glVertexAttribPointer(_textureLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoord));
    
    // pop matrix
    //Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    //Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    
    GL::bindTexture2DN(0, _textureID);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDrawElements(GL_TRIANGLES,  6, GL_UNSIGNED_BYTE, 0);
    glUniform1i(_textureUniform, 0);
}

GridNode* GridNode::create()
{
    GridNode* pRe = new GridNode();
    if (pRe && pRe->init()) {
        return pRe;
    }else
    {
        pRe = NULL;
        delete pRe;
        return NULL;
    }
}

//void GridNode::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags){
//    
//    
//    Node::visit(renderer, parentTransform, parentFlags);
//    
//    _command.init(_globalZOrder);
//    _command.func = CC_CALLBACK_0(GridNode::onDraw, this);
//    Director::getInstance()->getRenderer()->addCommand(&_command);
//    
//}

void GridNode::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    
   
    _command.init(_globalZOrder);
    //_command.func = CC_CALLBACK_0(GridNode::onDraw, this, _modelViewTransform, flags);
    _command.func = std::bind(&GridNode::onDraw, this, _modelViewTransform,flags);
    Director::getInstance()->getRenderer()->addCommand(&_command);
    
}

void GridNode::setdefault()
{
    Texture2D* tex = Director::getInstance()->getTextureCache()->getTextureForKey(_textureName);
    
    _contentSize = tex->getContentSize();
    _position = Vec2::ZERO;
    
}




