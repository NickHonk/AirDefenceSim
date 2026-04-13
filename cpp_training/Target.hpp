#pragma once

#include "SimulationEntity.hpp"

class Target : public SimulationEntity {
public:
    Target(std::string n, Vector3 pos, Vector3 vel);

    void update(double dt, const SimulationEnvironment& env) override;

    void setVelocity(Vector3 v) { velocity = v; }
    Vector3 getVelocity() const { return velocity; }
};
