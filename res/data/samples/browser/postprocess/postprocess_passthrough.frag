#ifdef OPENGL_ES
precision highp float;
#endif

// Uniforms
uniform sampler2D u_texture;

// Inputs
varying vec2 v_texcoord0;
varying vec4 v_color;

void main()
{
    gl_FragColor = texture2D(u_texture, v_texcoord0);
}
