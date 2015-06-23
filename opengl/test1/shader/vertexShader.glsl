#version 330

layout (location = 0) in vec3 position;
out vec4 vertexColor;

void main()
{
  gl_Position = vec4(position, 1.0);
  vertexColor = vec4(1.0, 1.0, 1.0, 1.0);
}
