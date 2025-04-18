#include <vector>
#include "particle.h"

#pragma once

class Simulator {
public:
  Simulator();
  ~Simulator();

  void update();
private:
  std::vector<Particle*> m_particles;
};
