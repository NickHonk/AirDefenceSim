#pragma once

#include "SimulationEntity.hpp"

class Target : public SimulationEntity {
public:
    Target(std::string n, glm::vec3 pos, glm::vec3 vel);

    void update(float dt, const SimulationEnvironment& env) override;

};
