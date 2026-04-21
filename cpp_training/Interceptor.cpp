#include "Interceptor.hpp"
#include "SimulationEnvironment.hpp"
#include <cmath>

Interceptor::Interceptor(std::string n, glm::vec3 pos, float speed, float gainPos, float gainVel)
    : SimulationEntity(n, pos) {
    this->maxSpeed = speed;
    this->gainPosFeedback = gainPos;
    this->gainVelFeedback = gainVel;
}

void Interceptor::update(float dt, const SimulationEnvironment& env) {

    // currently taking the place of a detector, which would normally provide this information. 
    // In a more complex simulation, we would need to check all entities and find the closest one.
    glm::vec3 currentTargetPosition = env.getClosestTargetPosition(); 

    // Berechne die Richtung zum Ziel
    glm::vec3 trackingError = currentTargetPosition - position;
    
    // Normalisiere die Richtung
    float lengthTrackingErr = glm::length(trackingError);

    // Setze die Geschwindigkeit in Richtung zum Ziel
   if (lengthTrackingErr > 1e-6) {
    velocity = trackingError * gainPosFeedback; // Proportional zum Positionsfehler
    if (glm::length(velocity) > maxSpeed) {
        velocity = glm::normalize(velocity) * maxSpeed; // Begrenze die Geschwindigkeit auf maxSpeed
    } 
    } else {
        // Ziel erreicht -> Interceptor stoppt 
        velocity = glm::vec3(0.0f, 0.0f, 0.0f); 
    }

    position += velocity * dt;
}