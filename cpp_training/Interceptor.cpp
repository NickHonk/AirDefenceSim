#include "Interceptor.hpp"
#include "SimulationEnvironment.hpp"
#include <cmath>

Interceptor::Interceptor(std::string n, float m, glm::vec3 pos, float speed, float gainPos, float gainVel)
    : SimulationEntity(n, m, pos) {
    this->maxSpeed = speed;
    this->gainPosFeedback = gainPos;
    this->gainVelFeedback = gainVel;
}

void Interceptor::update(float dt, const SimulationEnvironment& env) {

    // currently taking the place of detectors, which would normally provide this information. Later.
    glm::vec3 currentTargetPosition = env.getClosestTargetPosition(); 
    glm::vec3 currentTargetVelocity = env.getClosestTargetVelocity(); 

    // Berechne Folgefehler (Tracking Error)
    glm::vec3 trackingErrorPos = currentTargetPosition - position;
    glm::vec3 trackingErrorVel = currentTargetVelocity - velocity;
    
    // Norm des Tracking Errors für die Entscheidung, ob das Ziel erreicht ist oder nicht
    float lengthTrackingErr = glm::length(trackingErrorPos);

    // Prüfe ob Interceptor das Ziel erreicht hat 
    if (lengthTrackingErr > 1e-5) {
        velocity = trackingErrorPos * gainPosFeedback + trackingErrorVel * gainVelFeedback; // Proportional zum Positions- und Geschwindigkeitsfehler
        if (glm::length(velocity) > maxSpeed) {
            velocity = glm::normalize(velocity) * maxSpeed; // Begrenze die Geschwindigkeit auf maxSpeed
        } 
    } 

    position += velocity * dt;
}