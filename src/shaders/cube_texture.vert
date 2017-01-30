#version 330 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec3 texCoord;
layout (location = 3) in mat4 model;
layout (location = 7) in int layer;

out vec3 TexCoord;

// uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
// uniform int layer;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    TexCoord = vec3(texCoord.x, texCoord.y, texCoord.z + layer);
}