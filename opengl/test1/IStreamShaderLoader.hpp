#pragma  once

#include <istream>
#include <sstream>
#include <string>

#include <GL/glew.h>

class IStreamShaderLoader
{
private:
  std::istream& m_stream;
public:
  IStreamShaderLoader(std::istream& stream):
    m_stream(stream)
  {}

  GLuint compileCurrentShader(GLenum shaderType, const std::string name = "unnamed")
  {
    std::stringstream ss;
    ss << m_stream.rdbuf();

    if (m_stream.fail())
    {
      std::cerr << "Failure while  shader \"" << name << "\" from stream" << std::endl;
    }

    GLuint shaderID = glCreateShader(shaderType);
    std::string sdata{ss.str()};
    char *data = const_cast<char*>(sdata.c_str());
    glShaderSource(shaderID, 1, (GLchar**) &data, nullptr);
    glCompileShader(shaderID);

    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

    if (success == 0)
    {
      GLchar infoLog[512];
      glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
      std::cerr << "Shader " << name << ": compilation failed: " << infoLog << std::endl;
    }

    return shaderID;
  }
};
