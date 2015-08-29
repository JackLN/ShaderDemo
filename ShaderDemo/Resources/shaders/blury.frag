
#define N 20

varying vec2 v_texCoord;
varying vec4 v_color;

vec2 u_resolution = vec2(320,480);


vec4 verticalBlur(sampler2D t, vec2 p)
{
    vec4 sum = vec4(0.0);
    int count = 0;
    vec2 delta = vec2(1.0, 1.0) / u_resolution.xy;
    int n = int(abs(float(N) * cos(CC_Time[1])));
        
    for (int i = -n; i <= n; i++)
    {
        vec2 uv;
        uv.y = p.y - float(i) * delta.x;
        uv.x = p.x;
        if (uv.y < 0.0 || uv.y > 1.0)
            continue;
        sum += texture2D(t, uv);
        count ++;
    }
    return sum / float(count);
}

void main()
{
    gl_FragColor = verticalBlur(CC_Texture0, v_texCoord);
    //gl_FragColor = texture2D(CC_Texture0, v_texCoord);
}