
attribute vec4 a_position;
attribute vec4 a_color;

varying vec4 v_fragmentColor;
varying vec4 v_position;

void main()
{
    gl_Position = CC_MVPMatrix * a_position;
    v_fragmentColor = a_color;
    v_position = a_position;
    //v_texCoord = a_texCoord;
}