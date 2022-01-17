#version 330 core
out vec4 FragColor;

in vec4 color_light;

void main()
{
    FragColor = color_light; // set alle 4 vector values to 1.0
}