#pragma once

#include "SimulationEntity.hpp"

class Interceptor : public SimulationEntity {
private:
    float maxSpeed;               // Wie schnell der Interceptor maximal fliegen kann
    float gainPosFeedback;       // Wie stark der Interceptor auf Positionsfehler reagiert
    float gainVelFeedback;       // Wie stark der Interceptor auf Geschwindigkeitsfehler reagiert

public:
    Interceptor(std::string n, float m, glm::vec3 pos, float speed, float gainPos, float gainVel);

    void update(float dt, const SimulationEnvironment& env) override;

    //glm::vec3 getVelocity() const { return velocity; }
};