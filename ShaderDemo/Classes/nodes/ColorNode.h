//
//  ColorNode.h
//  ShaderDemo
//
//  Created by 林跃南 on 15/8/26.
//
//

#ifndef __ShaderDemo__ColorNode__
#define __ShaderDemo__ColorNode__

#include <stdio.h>
#include <cocos2d.h>
#include <vector>

USING_NS_CC;
using namespace std;

class ColorNode : public Node
{
public:
    ColorNode();
    ~ColorNode();
    virtual bool init();
    virtual void update(float delta);
    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
    static ColorNode* create();
    
    void switchEnable();
private:
    Texture2D* _texture;
    Sprite* _sprite;
    RenderTexture* _textureRenderer;
    CustomCommand _customCommand;
    vector<Point> _vertices;
    vector<Vec2> _texCoords;
    
    bool _enable;
};


#endif /* defined(__ShaderDemo__ColorNode__) */
