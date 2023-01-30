#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D texture;

varying vec3 v_normal;
varying vec2 v_texcoord;
varying vec3 v_pos;

//! [0]
void main()
{
    vec3 lightcolor;
    lightcolor.xyz = vec3(1.0, 1.0, 1.0);

    vec3 lightpos;
    lightpos.xyz = vec3(0.0, 0.0, 1.0);

    float ambient_strength = 1.0;
    vec3 ambient = ambient_strength * lightcolor;

    vec3 norm = normalize(v_normal);
    vec3 lightDir = normalize(lightpos - v_pos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightcolor;

    vec3 result;
    vec3 objectcolor;
    // Set fragment color from texture
    objectcolor.xyz = vec3(texture2D(texture, v_texcoord));
    result = (ambient + 0.0*diffuse) * objectcolor;
    gl_FragColor = vec4(result, 1.0);
}
//! [0]

