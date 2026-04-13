#pragma once
#include "SimulationEntity.hpp"

class Interceptor : public SimulationEntity {
private:
    double maxSpeed;               // Wie schnell der Interceptor maximal fliegen kann

public:
    Interceptor(std::string n, Vector3 pos, double speed);

    void update(double dt, const SimulationEnvironment& env) override;
    
    Vector3 getVelocity() const { return velocity; }
};