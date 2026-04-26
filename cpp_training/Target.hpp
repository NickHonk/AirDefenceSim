#pragma once

#include "SimulationEntity.hpp"

class Target : public SimulationEntity {
protected:
    double accelCounter;
    glm::vec3 acceleration; // Beschleunigung

public:
    Target(std::string n, glm::vec3 pos, glm::vec3 vel, double accelCounter, glm::vec3 acceleration);

    void update(float dt, const SimulationEnvironment& env) override;

    double getAccelCounter() const;

};
