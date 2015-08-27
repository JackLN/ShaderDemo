//
//  GridNode.cpp
//  ShaderDemo
//
//  Created by 林跃南 on 15/7/26.
//
//

#include "GridNode.h"
#include "CalculatePosition.h"

GridNode::GridNode()
:_bufferCount(0)
,_vbo(0)
,_bufferCapacity(0)
,_buffer(0)
,_enable(false)
{
    
}

GridNode::~GridNode()
{
    free(_buffer);
    _buffer = nullptr;
    glDeleteBuffers(1, &_vbo);
    _vbo = 0;
}

bool GridNode::init(std::string fileName)
{
    if (!Node::init()) {
        return false;
    }

    //program
    program = new GLProgram;
    program->initWithFilenames("gridnode.vert", "gridnode.frag");
    program->link();
    program->updateUniforms();
    
    _textureName = fileName;
    _textureID = Director::getInstance()->getTextureCache()->addImage(_textureName)->getName();
    
    auto texture = Director::getInstance()->getTextureCache()->getTextureForKey(fileName);
    auto size = texture->getContentSize();
    setContentSize(size);
   
    setUpBuffer( Vec2(0,0),Vec2(0,size.height), Vec2(size.width,size.height), Vec2(size.width,0), Color4B(155,0,0,255));
    //vbo
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(V2F_C4B_T2F)* _bufferCapacity, _buffer, GL_STREAM_DRAW);
    // vertex
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, vertices));
    // color
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, colors));
    // texcoord
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_TEX_COORD);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, texCoords));

    
    
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = CC_CALLBACK_2(GridNode::onTouchbegan,this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GridNode::onTouchEnded,this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

void GridNode::setUpBuffer(const Vec2 &lb, const Vec2 &lt, const Vec2 &rt, const Vec2& rb, const Color4B &color)
{
    unsigned int vertex_count = 2*3;
    ensureCapacity(vertex_count);
    
    V2F_C4B_T2F a = {lb, Color4B(color), Tex2F( 0.0,  1.0) };
    V2F_C4B_T2F b = {lt, Color4B(color), Tex2F( 0.0,  0.0) };
    V2F_C4B_T2F c = {rt, Color4B(color), Tex2F( 1.0,  0.0) };
    V2F_C4B_T2F d = {rb, Color4B(color), Tex2F( 1.0,  1.0) };
    
    V2F_C4B_T2F_Triangle *triangles = (V2F_C4B_T2F_Triangle *)(_buffer + _bufferCount);
    V2F_C4B_T2F_Triangle triangle0 = {a, b, c};
    V2F_C4B_T2F_Triangle triangle1 = {a, c, d};
    triangles[0] = triangle0;
    triangles[1] = triangle1;
    
    _bufferCount += vertex_count;
}


void GridNode::onDraw(const Mat4& transform, uint32_t flags)
{
    
    program->use();
    program->setUniformsForBuiltins(transform);
    
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(V2F_C4B_T2F)*_bufferCapacity, _buffer, GL_STREAM_DRAW);
    
    GLint enable = glGetUniformLocation(program->getProgram(), "_enable");
    program->setUniformLocationWith1i(enable, _enable);
    
    GL::bindTexture2D(_textureID);
    
    
    
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    
    
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_TEX_COORD);
    // vertex
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, vertices));
    // color
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, colors));
    // textrood
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, texCoords));
    glDrawArrays(GL_TRIANGLES, 0, _bufferCount);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _bufferCount);
    CHECK_GL_ERROR_DEBUG();
    
    GL::bindTexture2DN(0, _textureID);
}

GridNode* GridNode::create(std::string fileName)
{
    GridNode* pRe = new GridNode();
    if (pRe && pRe->init(fileName)) {
        return pRe;
    }else
    {
        pRe = NULL;
        delete pRe;
        return NULL;
    }
}

void GridNode::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    
   
    _command.init(_globalZOrder);
    //_command.func = CC_CALLBACK_0(GridNode::onDraw, this, _modelViewTransform, flags);
    _command.func = std::bind(&GridNode::onDraw, this, _modelViewTransform,flags);
    Director::getInstance()->getRenderer()->addCommand(&_command);
    
}

void GridNode::ensureCapacity(int count)
{
    CCASSERT(count>=0, "capacity must be >= 0");
    
    if(_bufferCount + count > _bufferCapacity)
    {
        _bufferCapacity += MAX(_bufferCapacity, count);
        _buffer = (V2F_C4B_T2F*)realloc(_buffer, _bufferCapacity*sizeof(V2F_C4B_T2F));
    }
}

bool GridNode::onTouchbegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    Vec2 pos = touch->getLocation();
    if (pos.x > _position.x &&
        pos.x < _position.x + _contentSize.width &&
        pos.y > _position.y &&
        pos.y < _position.y + _contentSize.height) {
        
        return true;
    }
    
    return false;
}

void GridNode::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    Vec2 pos = touch->getLocation();
    if (pos.x > _position.x &&
        pos.x < _position.x + _contentSize.width &&
        pos.y > _position.y &&
        pos.y < _position.y + _contentSize.height) {
        
         _enable = !_enable;
    }
}


