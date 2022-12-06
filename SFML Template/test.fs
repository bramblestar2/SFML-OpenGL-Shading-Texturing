#version 330 core
out vec4 FragColor;
  
uniform vec4 ourColor;
uniform sampler2D texture;

void main()
{
    FragColor = ourColor;
} 