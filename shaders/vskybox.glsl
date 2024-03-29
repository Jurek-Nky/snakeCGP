#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp_matrix;
uniform mat4 model_matrix;

attribute vec4 a_position;
attribute vec2 a_texcoord;
attribute vec3 a_normal;

varying vec2 v_texcoord;
varying vec3 v_normal;
varying vec3 v_pos;
//! [0]
void main()
{
    // Calculate vertex position in screen space
    gl_Position = mvp_matrix * a_position;

    // Pass texture coordinate to fragment shaders
    // Value will be automatically interpolated to fragments inside polygon faces
    v_texcoord = a_texcoord;

    v_normal = a_normal;

    v_pos = vec3(model_matrix * a_position);
}
//! [0]