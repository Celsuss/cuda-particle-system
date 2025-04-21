#pragma once

#include <vector>
#include "particle.h"

class Renderer;

class Simulator {
public:
  Simulator(int particles = 0);
  ~Simulator();

  void run();
private:
  void update();

  std::vector<Particle*> m_particles;
  Renderer* m_renderer;
};
