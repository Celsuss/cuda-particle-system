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

Simulator::Simulator(int n_particles) {
  for(int i = 0; i < n_particles; ++i){
    m_particles.push_back(new Particle());
  }
}

Simulator::~Simulator(){}


void Simulator::run() {
  for (int i = 0; i < 100; ++i){
    update();
  }
}

void Simulator::update() {

}
