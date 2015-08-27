//
//  RectShadeNode.cpp
//  ShaderDemo
//
//  Created by 林跃南 on 15/8/23.
//
//

#include "RectShadeNode.h"

const std::string POSITION1 = "v_position1";
const std::string POSITION2 = "v_position2";
const std::string POSITION3 = "v_position3";
const std::string POSITION4 = "v_position4";

const std::string LENGH = "f_lenght";
const std::string RESOLUTION = "resolution";

RectShadeNode::RectShadeNode()
:_vao(0)
,_vbo(0)
,_buffer(0)
,_bufferCapacity(0)
,_bufferCount(0)
,_dirty(true)
{
    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
}

RectShadeNode::~RectShadeNode()
{
    free(_buffer);
    _buffer = nullptr;
    free(_positions);
    _positions = nullptr;
    glDeleteBuffers(1, &_vbo);
    _vbo = 0;
}

RectShadeNode* RectShadeNode::create(cocos2d::Rect rect,Color4B color,float length)
{
    RectShadeNode* pRef = new RectShadeNode();
    if (pRef && pRef->init(rect,color,length))
    {
        pRef->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRef);
    }
    return pRef;
}

bool RectShadeNode::init(cocos2d::Rect rect,Color4B color,float length)
{
    if (!Node::init()) {
        return false;
    }
    
    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
    _program = new GLProgram;
    _program->initWithFilenames("rectShade.vert", "rectShade.frag");
    _program->link();
    _program->updateUniforms();
    
    _state = GLProgramState::getOrCreateWithGLProgram(_program);
    setGLProgramState(_state);
    
    ensureCapacity(8);
    
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(V2F_C4B_T2F)* _bufferCapacity, _buffer, GL_STREAM_DRAW);
    // vertex
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, vertices));
    // color
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_COLOR);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, colors));
    
    
    m_uniformposition1 = glGetUniformLocation(_program->getProgram(), POSITION1.c_str());
    m_uniformposition2 = glGetUniformLocation(_program->getProgram(), POSITION2.c_str());
    m_uniformposition3 = glGetUniformLocation(_program->getProgram(), POSITION3.c_str());
    m_uniformposition4 = glGetUniformLocation(_program->getProgram(), POSITION4.c_str());
    
    m_uniformlenght = glGetUniformLocation(_program->getProgram(), LENGH.c_str());
    m_uniformresolution = glGetUniformLocation(_program->getProgram(), RESOLUTION.c_str());
    
    drawReckNode(rect,color,length);
    
    return true;
}

void RectShadeNode::drawReckNode(Rect rect,Color4B color,float length)
{
    _length = length;
    auto size = Director::getInstance()->getWinSize();
    unsigned int vertex_count = 8*3;
    ensureCapacity(vertex_count);
    
    
    _positions = (Vec2*)malloc(4*sizeof(Vec2*));
    Vec2 position1 = rect.origin;
    Vec2 position2 = Vec2(rect.origin.x,rect.origin.y+rect.size.height);
    Vec2 position3 = Vec2(rect.origin.x+rect.size.width,rect.origin.y+rect.size.height);
    Vec2 position4 = Vec2(rect.origin.x+rect.size.width,rect.origin.y);
    _positions[0] = position1;
    _positions[1] = position2;
    _positions[2] = position3;
    _positions[3] = position4;
    
    
    
    V2F_C4B_T2F a = {Vec2(0,0), Color4B(color), Tex2F(0.0, 0.0) };
    V2F_C4B_T2F b = {Vec2(size.width,0), Color4B(color), Tex2F(0.0,  0.0) };
    V2F_C4B_T2F c = {position1, Color4B(color), Tex2F( 0.0,  0.0) };
    V2F_C4B_T2F d = {position4, Color4B(color), Tex2F( 0.0, 0.0) };
    V2F_C4B_T2F e = {Vec2(size.width,size.height), Color4B(color), Tex2F(0.0, 0.0) };
    V2F_C4B_T2F f = {position3, Color4B(color), Tex2F(0.0,  0.0) };
    V2F_C4B_T2F g = {position2, Color4B(color), Tex2F( 0.0,  0.0) };
    V2F_C4B_T2F h = {Vec2(0,size.height), Color4B(color), Tex2F( 0.0, 0.0) };
    
    V2F_C4B_T2F_Triangle *triangles = (V2F_C4B_T2F_Triangle *)(_buffer + _bufferCount);
    V2F_C4B_T2F_Triangle triangle0 = {a, b, c};
    V2F_C4B_T2F_Triangle triangle1 = {b, d, c};
    V2F_C4B_T2F_Triangle triangle2 = {e, d, b};
    V2F_C4B_T2F_Triangle triangle3 = {e, f, d};
    V2F_C4B_T2F_Triangle triangle4 = {e, g, f};
    V2F_C4B_T2F_Triangle triangle5 = {e, h, g};
    V2F_C4B_T2F_Triangle triangle6 = {h, c, g};
    V2F_C4B_T2F_Triangle triangle7 = {h, a, c};
    
    triangles[0] = triangle0;
    triangles[1] = triangle1;
    triangles[2] = triangle2;
    triangles[3] = triangle3;
    triangles[4] = triangle4;
    triangles[5] = triangle5;
    triangles[6] = triangle6;
    triangles[7] = triangle7;
    
    _bufferCount += vertex_count;
    _dirty = true;
}

void RectShadeNode::onDraw(const cocos2d::Mat4 &transform, uint32_t flags)
{
    _program->use();
    _program->setUniformsForBuiltins(transform);
    
    GL::blendFunc(_blendFunc.src, _blendFunc.dst);
    
    if (_dirty) {
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(V2F_C4B_T2F)*_bufferCapacity, _buffer, GL_STREAM_DRAW);
        _dirty = false;
    }
   
    
    
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    // vertex
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, vertices));
    // color
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(V2F_C4B_T2F), (GLvoid *)offsetof(V2F_C4B_T2F, colors));
    
    
    //GLProgramState* state = GLProgramState::getOrCreateWithGLProgram(_program);
    _program->setUniformLocationWith1f(m_uniformlenght, _length);
    _program->setUniformLocationWith2f(m_uniformresolution, Director::getInstance()->getWinSize().width,Director::getInstance()->getWinSize().height);
    _program->setUniformLocationWith2f(m_uniformposition1, _positions[0].x, _positions[0].y);
    _program->setUniformLocationWith2f(m_uniformposition2, _positions[1].x, _positions[1].y);
    _program->setUniformLocationWith2f(m_uniformposition3, _positions[2].x, _positions[2].y);
    _program->setUniformLocationWith2f(m_uniformposition4, _positions[3].x, _positions[3].y);
    
    
    glDrawArrays(GL_TRIANGLES, 0, _bufferCount);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, _bufferCount);
    CHECK_GL_ERROR_DEBUG();
}

void RectShadeNode::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(RectShadeNode::onDraw,this ,transform, flags);
    renderer->addCommand(&_customCommand);
}

void RectShadeNode::ensureCapacity(int count)
{
    CCASSERT(count>=0, "capacity must be >= 0");
    
    if(_bufferCount + count > _bufferCapacity)
    {
        _bufferCapacity += MAX(_bufferCapacity, count);
        _buffer = (V2F_C4B_T2F*)realloc(_buffer, _bufferCapacity*sizeof(V2F_C4B_T2F));
    }
}