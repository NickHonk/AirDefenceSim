#include "Interceptor.hpp"
#include "SimulationEnvironment.hpp"
#include <cmath>

Interceptor::Interceptor(std::string n, Vector3 pos, double speed)
    : SimulationEntity(n, pos) {
    this->maxSpeed = speed;
}

void Interceptor::update(double dt, const SimulationEnvironment& env) {

    Vector3 currentTargetPosition = env.getClosestTargetPosition();

    // Berechne die Richtung zum Ziel
    Vector3 direction; 

    direction.x = currentTargetPosition.x - position.x;
    direction.y = currentTargetPosition.y - position.y;
    direction.z = currentTargetPosition.z - position.z;
    
    // Normalisiere die Richtung
    double length = std::sqrt(direction.x * direction.x 
                            + direction.y * direction.y 
                            + direction.z * direction.z);

    // Setze die Geschwindigkeit in Richtung zum Ziel
    if (length > 1e-6) {
        velocity.x = direction.x / length * maxSpeed;
        velocity.y = direction.y / length * maxSpeed;
        velocity.z = direction.z / length * maxSpeed;
    } else {
        // Ziel erreicht -> Interceptor stoppt 
        velocity = {0.0, 0.0, 0.0}; 
    }

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
    position.z += velocity.z * dt;
}