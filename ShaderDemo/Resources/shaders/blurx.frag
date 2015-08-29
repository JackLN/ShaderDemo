
#define N 40

varying vec2 v_texCoord;
varying vec4 v_color;

uniform vec2 u_resolution;
uniform int u_enable;

vec4 verticalBlur(sampler2D t, vec2 p)
{
    vec4 sum = vec4(0.0);
    int count = 0;
    vec2 delta = vec2(1.0, 1.0) / u_resolution.xy;
    //int n = int(abs(float(N) * cos(CC_Time[1])));
    int n = N;
    for (int i = -n; i <= n; i++)
    {
        vec2 uv;
        uv.x = p.x - float(i) * delta.x;
        uv.y = p.y;
        if (uv.x < 0.0 || uv.x > 1.0)
            continue;
        sum += texture2D(t, uv);
        count ++;
    }
    return sum / float(count);
}

void main()
{
    if (u_enable == 1)
    {
        gl_FragColor = verticalBlur(CC_Texture0, v_texCoord);
    }
    else
    {
        gl_FragColor = texture2D(CC_Texture0, v_texCoord);
    }
}