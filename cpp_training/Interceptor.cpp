#include "Interceptor.hpp"
#include "SimulationEnvironment.hpp"
#include <cmath>

Interceptor::Interceptor(std::string n, glm::vec3 pos, float speed)
    : SimulationEntity(n, pos) {
    this->maxSpeed = speed;
}

void Interceptor::update(float dt, const SimulationEnvironment& env) {

    glm::vec3 currentTargetPosition = env.getClosestTargetPosition();

    // Berechne die Richtung zum Ziel
    glm::vec3 direction; 

    direction = currentTargetPosition - position;
    
    // Normalisiere die Richtung
    float length = glm::length(direction);

    // Setze die Geschwindigkeit in Richtung zum Ziel
   if (length > 1e-6) {
    velocity = direction / length * maxSpeed;
    } else {
        // Ziel erreicht -> Interceptor stoppt 
        velocity = glm::vec3(0.0f, 0.0f, 0.0f); 
    }

    position += velocity * dt;
}