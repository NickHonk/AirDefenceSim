#pragma once

#include "SimulationEntity.hpp"

class Interceptor : public SimulationEntity {
private:
    float maxSpeed;               // Wie schnell der Interceptor maximal fliegen kann

public:
    Interceptor(std::string n, glm::vec3 pos, float speed);

    void update(float dt, const SimulationEnvironment& env) override;

    glm::vec3 getVelocity() const { return velocity; }
};