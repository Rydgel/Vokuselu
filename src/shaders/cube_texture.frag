#version 330 core
in vec3 TexCoord;

out vec4 color;

uniform sampler2DArray ourTexture;

void main()
{
    // texture(texSource, vec3(uv, float(layer))
    color = texture(ourTexture, TexCoord);
}