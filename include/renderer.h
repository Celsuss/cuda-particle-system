#pragma once
#include <GL/glew.h>

class GLFWwindow;
class Particle;

class Renderer {
public:
  Renderer();
  ~Renderer();
  void closeWindow();
  bool isWindowOpen() const;
  void render();
  void renderParticles(const Particle *particles, const int n_particles);

private:
  GLFWwindow *createWindow(const int width, const int height);
  GLuint createShaderProgram();

  GLFWwindow* m_window;
  GLuint m_particleVBO;   // Vertex Buffer Object to store particle data
  GLuint m_shaderProgram; // Compiled shader program
};
