#include "Target.hpp"

Target::Target(std::string n, glm::vec3 pos, glm::vec3 vel)
    : SimulationEntity(n, pos) {
    this->velocity = vel;
}

void Target::update(float dt, const SimulationEnvironment& env) {
    position += velocity * dt;
}
