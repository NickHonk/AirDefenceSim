#pragma once

#include <memory>
#include <string>
#include <glm/glm.hpp>



class SimulationEnvironment;

class SimulationEntity {
protected:
    std::string name;
    glm::vec3 position;
    glm::vec3 velocity;

public:
    SimulationEntity(std::string n, glm::vec3 pos) : name(n), position(pos), velocity(glm::vec3(0.0f, 0.0f, 0.0f)) {}
    virtual ~SimulationEntity() = default; // Wichtig für Polymorphie!

    // Jedes Objekt berechnet seinen nächsten Zustand selbst
    virtual void update(float dt, const SimulationEnvironment& env) = 0; 
    
    glm::vec3 getPosition() const { return position; }
    glm::vec3 getVelocity() const { return velocity; }
    std::string getName() const { return name; }
};