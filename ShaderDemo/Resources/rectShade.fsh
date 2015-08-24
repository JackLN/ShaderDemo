
#ifdef GL_ES						
precision lowp float;			
#endif	
							
varying vec4 v_fragmentColor;							
varying vec4 v_position;

uniform vec2 v_position1;
uniform vec2 v_position2;
uniform vec2 v_position3;
uniform vec2 v_position4;

uniform float f_lenght;
uniform vec2 resolution;

float aspe = resolution.x / resolution.y;

vec2 transv2(vec2 point)
{
    vec2 result = point.xy / resolution.xy;
    result.x *= aspe;
    return result;
}

float transf(float r)
{
    float re = r / resolution.y;
    re *= (1.2+0.8*cos(CC_Time[1]));
    return re;
}

vec2 position1 = transv2(v_position1);
vec2 position3 = transv2(v_position3);
vec2 position2 = transv2(v_position2);
vec2 position4 = transv2(v_position4);
float lenght = transf(f_lenght);


bool isInRect(vec2 pos)
{
    bool pRe = true;
  
    if ((pos.x < position1.x - lenght || pos.x > position4.x + lenght)||
        (pos.y < position1.y - lenght || pos.y > position2.y + lenght)) {
        pRe = false;
    }
    return pRe;
}

float getMask(vec2 pos,float lenght)
{
    
    if (isInRect(pos)) {
        
        float dis = abs(pos.x-position1.x+lenght);
        if (dis > abs(pos.x-position4.x-lenght))
            dis = abs(pos.x-position4.x-lenght);
        if (dis > abs(pos.y-position1.y+lenght))
            dis = abs(pos.y-position1.y+lenght);
        if (dis > abs(pos.y-position2.y-lenght))
            dis = abs(pos.y-position2.y-lenght);
    
        return smoothstep(lenght,0.0,dis)*v_fragmentColor.w;
    }
	return v_fragmentColor.w;
}



void main()
{
    vec2 pos = transv2(v_position.xy);
    float mask = getMask(pos,lenght);
    
    vec4 color = v_fragmentColor;
    color.w = mask;
    gl_FragColor = color;
}
