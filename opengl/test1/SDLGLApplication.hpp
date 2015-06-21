#pragma once

#include <iostream>
#include <string>
#include <cstdint>
#include <cassert>

#include <SDL.h>
#include <SDL_opengl.h>

class SDLGLApplication
{
private:
  SDL_Window* m_window;
  SDL_GLContext m_glContext;
  bool m_running;
  bool m_error;

  int32_t m_xPosition;
  int32_t m_yPosition;
  int32_t m_width;
  int32_t m_height;

public:
  SDLGLApplication(int32_t xPosition, int32_t yPosition,
                   int32_t width, int32_t height,
                   const std::string& caption = ""):
     m_running(false),
     m_xPosition(xPosition),
     m_yPosition(yPosition),
     m_width(width),
     m_height(height)
  {
    m_error = false;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
      std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
      m_error = true;
      return;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    //The window we'll be rendering to
    m_window = SDL_CreateWindow("SDL+OpenGL test",
                                m_xPosition,
                                m_yPosition,
                                m_width,
                                m_height,
                                SDL_WINDOW_OPENGL);
    if (m_window == nullptr)
    {
      std::cerr << "Error during window creation: " << SDL_GetError() << std::endl;
      m_error = true;
      return;
    }

    m_glContext = SDL_GL_CreateContext(m_window);

    glewExperimental = GL_TRUE;
    GLenum glewResult = glewInit();
    if (glewResult != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW: " << glewGetErrorString(glewResult) << std::endl;
        m_error = true;
        return;
    }
  }

  virtual ~SDLGLApplication()
  {
    SDL_DestroyWindow(m_window);
    SDL_Quit();
  }

  void setWindowSize(int32_t width, int32_t height)
  {
    m_width = width;
    m_height = height;

    SDL_SetWindowSize(m_window, m_width, m_height);
  }

  void setRunning(bool value)
  {
    m_running = value;
  }

  bool isRunning() const
  {
    return m_running;
  }

  int32_t getHeight() const
  {
    return m_height;
  }

  int32_t getWidth() const
  {
    return m_width;
  }

  void runLoop()
  {
    if (m_error)
    {
      std::cerr << "Cannot run main loop because of errors occurring during initialization" << std::endl;
      return;
    }

    setRunning(true);
    SDL_Event evt;
    while (isRunning())
    {
      while (SDL_PollEvent(&evt) != 0)
      {
        switch (evt.type)
        {
          case SDL_QUIT:
            handleQuit(evt);
            break;

          case SDL_KEYDOWN:
            handleKeyDown(evt);
            break;

          case SDL_WINDOWEVENT:
            switch (evt.window.event)
            {
              case SDL_WINDOWEVENT_SIZE_CHANGED:
                handleSizeChange(evt.window);
                break;
            }

        }
      }

      drawGLContext(m_glContext);
      SDL_GL_SwapWindow(m_window);
    }
  }

protected:
  virtual void handleQuit(SDL_Event& evt)
  {
    setRunning(false);
  };

  virtual void handleSizeChange(SDL_WindowEvent& evt)
  {
    assert(SDL_GetWindowID(m_window) == evt.windowID);

    m_width = evt.data1;
    m_height = evt.data2;
  }

  virtual void handleKeyDown(SDL_Event& evt) {};
  virtual void drawGLContext(SDL_GLContext& context) = 0;

};
