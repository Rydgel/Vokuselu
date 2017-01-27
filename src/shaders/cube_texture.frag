#version 330 core
in vec3 TexCoord;

out vec4 color;

uniform sampler2DArray ourTexture;
const vec4 fogColor = vec4(0.73, 0.82, 0.89, 1.0);

void main()
{
    float fog_factor =  1.0 - (gl_FragCoord.z / gl_FragCoord.w)/ 50.0;
    fog_factor = clamp(fog_factor, 0.0, 1.0 );
    color = mix(fogColor, texture(ourTexture, TexCoord), fog_factor);
    // color = texture(ourTexture, TexCoord);
}