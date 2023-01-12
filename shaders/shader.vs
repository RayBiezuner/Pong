#version 330 core
layout (location = 0) in vec3 aPos; 
  
out vec3 vertexColor;

uniform vec2 uCoord;
uniform vec2 uScale;

void main()
{
    gl_Position = vec4(3.0/4.0 * (uScale.x * aPos.x + uCoord.x), uScale.y * aPos.y + uCoord.y, 0.0, 1.0);
    vertexColor = vec3(1.0, 1.0, 1.0); 
}  