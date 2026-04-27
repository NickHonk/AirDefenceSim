#pragma once

#include "SimulationEntity.hpp"

class Target : public SimulationEntity {
protected:
    double accelCounter;
    glm::vec3 acceleration; // Beschleunigung durch Antrieb
    glm::vec3 g = glm::vec3(0.0f, 0.0f, -9.81f); // Beschleunigung durch Schwerkraft

public:
    Target(std::string n, float m, glm::vec3 pos, glm::vec3 vel, double accelCounter, glm::vec3 acceleration);

    void update(float dt, const SimulationEnvironment& env) override;

    double getAccelCounter() const;

};
