#version 330 core
layout (location = 0) in vec3 aPos; 
  
out vec3 vertexColor;

void main()
{
    gl_Position = vec4(600.0 / 800.0 * aPos.x, aPos.y, aPos.z, 1.0);
    vertexColor = vec3(1.0, 1.0, 1.0); 
}  