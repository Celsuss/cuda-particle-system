#pragma once

namespace SimConstants {
  // Particle boundaries
  constexpr float MAX_RADIUS = 10.0;
  constexpr float MIN_RADIUS = 0.1;
  constexpr float MIN_SPEED = 0.1;
  constexpr float MAX_SPEED = 10.0;

  // Physical constants
  constexpr float GRAVITY = 9.81;
  constexpr float ELASTICITY_DEFAULT = 0.8;

  // Performance parameters
  constexpr int MAX_PARTICLES = 10000;
  constexpr float TIME_STEP = 0.01;

  // Visualization parameters
  constexpr int RENDER_QUALITY = 3; // Higher numbers = better quality
} // namespace SimConstants
