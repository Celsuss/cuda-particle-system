#include "renderer.h"
#include "particle.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>

Renderer::Renderer() {
  initialize();
  m_window = createWindow(1024, 768);
  m_shaderProgram = createShaderProgram();
}

Renderer::~Renderer() { closeWindow(); }

void Renderer::closeWindow() {
  // Cleanup
  // delete[] particles;
  glDeleteBuffers(1, &m_particleVBO);
  glDeleteProgram(m_shaderProgram);
  glfwTerminate();
}

bool Renderer::isWindowOpen() const { return glfwWindowShouldClose(m_window); }

void Renderer::render() {
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Draw particles
  // renderParticles(particles);

  // Swap buffers and poll events
  glfwSwapBuffers(m_window);
  glfwPollEvents();

  // Exit on ESC
  if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(m_window, true);
}

void Renderer::renderParticles(const Particle *particles, const int m_particles) {
    // Update the buffer with new particle data (if you have updated particles)
    // glBindBuffer(GL_ARRAY_BUFFER, particleVBO);
    // glBufferSubData(GL_ARRAY_BUFFER, 0, NUM_PARTICLES * sizeof(Particle), particles);

    // Use the shader program
    glUseProgram(m_shaderProgram);

    // Setup camera
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1024.0f / 768.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 5.0f),   // Camera position
        glm::vec3(0.0f, 0.0f, 0.0f),   // Look at point
        glm::vec3(0.0f, 1.0f, 0.0f)    // Up vector
    );

    // Set uniform variables for the shader
    GLint projLoc = glGetUniformLocation(m_shaderProgram, "projection");
    GLint viewLoc = glGetUniformLocation(m_shaderProgram, "view");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    // Bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_particleVBO);

    // Set up vertex attributes for position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)0);
    glEnableVertexAttribArray(0);

    // Set up vertex attributes for color
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Enable point rendering features
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Draw the particles
    // glDrawArrays(GL_POINTS, 0, NUM_PARTICLES);
    glDrawArrays(GL_POINTS, 0, m_particles);
};

int Renderer::initialize() {
  // Initialize GLFW
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  // Configure GLFW for OpenGL 3.3 core profile
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Initialize GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW" << std::endl;
    return -1;
  }
  return 0;
}

GLFWwindow *Renderer::createWindow(const int width, const int height) {
  GLFWwindow *window = glfwCreateWindow(width, height, "Particle Renderer", nullptr, nullptr);
  if (window == nullptr) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    // TODO Throw error
    return nullptr;
  }
  glfwMakeContextCurrent(window);
  return window;
}

GLuint Renderer::createShaderProgram() {
  // TODO Move shaders away from method.
  const char *vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

uniform mat4 projection;
uniform mat4 view;

out vec4 particleColor;

void main() {
    particleColor = aColor;
    gl_Position = projection * view * vec4(aPos, 1.0);
    gl_PointSize = 5.0;
}
)";

  const char *fragmentShaderSource = R"(
#version 330 core
in vec4 particleColor;
out vec4 FragColor;

void main() {
    // Create a circle-like point
    vec2 coord = gl_PointCoord - vec2(0.5);
    if(length(coord) > 0.5)
        discard;
    FragColor = particleColor;
}
)";

  // Create vertex shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  // Create fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  // Create and link shader program
  GLuint program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  // Clean up
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return program;
}
