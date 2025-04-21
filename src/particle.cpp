#include <cstdlib>
#include "particle.h"
#include "simulation_constants.h"

Particle::Particle() {
    m_x = 0;
    m_y = 0;
    m_speed = SimConstants::MIN_SPEED + (float)rand() / (SimConstants::MAX_SPEED - SimConstants::MIN_SPEED + 1);
    m_mass = 1;
    m_vx = 0;
    m_vy = 0;
    m_elasticity = 0.5f;
    m_ttl = 100;
    m_color[0] = 255;
    m_color[1] = 255;
    m_color[2] = 255;
    m_radius = 1;
}

Particle::~Particle() {
    // No dynamic resources to free
}

void Particle::update() {
    // Update position based on velocity
    m_x += m_vx;
    m_y += m_vy;

    // Decrease time to live
    m_ttl--;
}
