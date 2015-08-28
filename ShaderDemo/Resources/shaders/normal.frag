
varying vec4 v_Color;
varying vec2 v_texCoord;

void main()
{
    gl_FragColor = v_Color * texture2D(CC_Texture0, v_texCoord);
}