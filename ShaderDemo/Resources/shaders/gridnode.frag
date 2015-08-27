#ifdef GL_ES
precision lowp float;
#endif

varying vec2 v_texCoord;
varying vec4 v_color;

uniform bool _enable;

void main()
{
    vec4 color = texture2D(CC_Texture0, v_texCoord);
    if (_enable && color.a > 0.0)
        color = v_color;
    gl_FragColor = color;
}