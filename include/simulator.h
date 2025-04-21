#include <vector>
#include "particle.h"

#pragma once

class Simulator {
public:
  Simulator(int particles = 0);
  ~Simulator();

  void run();
private:
  void update();

  std::vector<Particle*> m_particles;
};
