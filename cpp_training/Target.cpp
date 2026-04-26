#include "Target.hpp"

Target::Target(std::string n, glm::vec3 pos, glm::vec3 vel, double accelCounter, glm::vec3 acceleration)
    : SimulationEntity(n, pos) {
    this->velocity = vel;
    this->acceleration = acceleration;
    this->accelCounter = accelCounter;
}

void Target::update(float dt, const SimulationEnvironment& env) {
    if (accelCounter > 0) {
        velocity += acceleration * dt; // Beschleunigung in Richtung X und Y
        accelCounter -= 1; // simulatimg the depleting fuel in the missile
    }
    position += velocity * dt;
}

double Target::getAccelCounter() const {
    return accelCounter;
}
