#include "Target.hpp"

Target::Target(std::string n, Vector3 pos, Vector3 vel)
    : SimulationEntity(n, pos) {
    this->velocity = vel;
}

void Target::update(double dt, const SimulationEnvironment& env) {
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
    position.z += velocity.z * dt;
}
