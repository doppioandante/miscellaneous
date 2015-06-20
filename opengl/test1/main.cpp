#include <iostream>
#include <cmath>

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>

#include "SDLGLApplication.hpp"
#include "LocalShaderProgramLoader.hpp"

const unsigned int SCREEN_WIDTH = 768;
const unsigned int SCREEN_HEIGHT = 768;

class MyApplication: public SDLGLApplication
{
private:
  GLuint vao;
  GLuint vbo;
  GLuint ebo;
  double angle;
  GLfloat vertices[3*4];
  GLuint indices[6];

public:
  MyApplication():
    SDLGLApplication(SDL_WINDOWPOS_UNDEFINED,
                     SDL_WINDOWPOS_UNDEFINED,
                     SCREEN_WIDTH,
                     SCREEN_HEIGHT),
    angle(0.0),
    vertices{0.5f,  0.5f, 0.0f,  // Top Right
             0.5f, -0.5f, 0.0f,  // Bottom Right
             -0.5f, -0.5f, 0.0f,  // Bottom Left
             -0.5f,  0.5f, 0.0f},   // Top Left
    indices{0, 1, 3,
            1, 2, 3}
  {
    LocalShaderProgramLoader loader(SHADER_DIRECTORY);
    GLuint shaderProgram = loader.loadShaders({{GL_VERTEX_SHADER, "vertexShader.glsl"},
                                               {GL_FRAGMENT_SHADER, "fragmentShader.glsl"}});
    glUseProgram(shaderProgram);

    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

      glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(GLfloat), (GLvoid*)0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

protected:
  virtual void drawGLContext(SDL_GLContext&)
  {
    glViewport(0, 0, getHeight(), getWidth());

    glClearColor(0.2f,0.2f,0.2f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(vao);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    angle += (2.0*M_PI * 0.001) / 5.0;

  }

private:
  static void rotate2(GLfloat* vec3, double theta)
  {
    using std::cos;
    using std::sin;
    vec3[0] = vec3[0]*cos(theta) - vec3[1]*sin(theta);
    vec3[1] = vec3[1]*sin(theta) + vec3[1]*cos(theta);
  }

};

int main()
{
  MyApplication myApp;
  myApp.runLoop();

  return 0;
}
