#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

#include <boost/filesystem.hpp>
#include <GL/glew.h>

#include "IStreamShaderLoader.hpp"

using namespace boost;

class LocalShaderProgramLoader
{
private:
  filesystem::path m_path;

public:
  LocalShaderProgramLoader():
    m_path(filesystem::current_path())
  {}

  LocalShaderProgramLoader(const filesystem::path& path):
    m_path(path)
  {}

  GLuint loadShaders(std::vector<std::pair<GLenum, std::string>> shaderFiles)
  {
    GLuint shaderProgram = glCreateProgram();

    if (shaderProgram == 0)
    {
      std::cerr << "Failed creating GL program" << std::endl;
    }

    std::vector<GLuint> shaders;
    shaders.reserve(shaderFiles.size());

    for (auto shaderInfo : shaderFiles)
    {
      std::string fullPathStr{(m_path / shaderInfo.second).string()};
      std::ifstream shaderStream{fullPathStr.c_str()};
      if (shaderStream.bad())
      {
        std::cerr << "Could not open file: " << fullPathStr << std::endl;
      }
      GLuint shader = IStreamShaderLoader(shaderStream).compileCurrentShader(shaderInfo.first, shaderInfo.second);
      glAttachShader(shaderProgram, shader);

      shaders.push_back(shader);
    }

    glLinkProgram(shaderProgram);

    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (success == 0)
    {
      GLchar infoLog[512];
      glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
      std::cerr << "Failed linking GL program: " << infoLog << std::endl;
    }

    for (GLuint shader : shaders)
    {
      glDeleteShader(shader);
    }

    return shaderProgram;
  }
};
