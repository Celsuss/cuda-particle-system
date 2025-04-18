#include <vector>

#pragma once

class Particle {
public:
  Particle();
  ~Particle();

  void update();
private:
  int m_x;
  int m_y;
  int m_speed;
  int m_mass;      // Mass of the particle for collision calculations
  int m_vx;        // Velocity in x-direction
  int m_vy;        // Velocity in y-direction
  float m_elasticity; // Elasticity for collision bounciness
  int m_ttl;       // Time to live for the particle
  unsigned char m_color[3]; // RGB color values for rendering
  int m_radius;    // Bounding radius for collision detection
  std::vector<Particle*> m_nearbyParticles; // List of nearby particles for collision checks
};
