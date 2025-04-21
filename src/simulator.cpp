/**
 * @file      simulator.cpp
 * @brief     Header of
 * @date      Mon Apr 21 18:47:19 2025
 * @author    celsuss
 * @copyright BSD-3-Clause
 *
 * This module
 */

#include "simulator.h"
#include "particle.h"
#include "renderer.h"

Simulator::Simulator(int n_particles) {
  m_renderer = new Renderer();
  for(int i = 0; i < n_particles; ++i){
    m_particles.push_back(new Particle());
  }
}

Simulator::~Simulator(){}


void Simulator::run() {
  update();
}

void Simulator::update() {
  while(m_renderer->isWindowOpen()){
    m_renderer->render();
  }
  m_renderer->closeWindow();
}
