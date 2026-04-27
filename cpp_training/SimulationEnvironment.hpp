#pragma once

#include <memory>
#include "SimulationEntity.hpp"
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>

class SimulationEnvironment {
private:

    std::vector<std::unique_ptr<SimulationEntity>> entities;
    
    float currentTime;

    std::ofstream logFile;

    bool isHit = false; // Flag, um zu verfolgen, ob der Interceptor das Ziel getroffen hat

    float hitThreshold; // Abstand, unter dem ein Treffer angenommen wird

public:
    SimulationEnvironment(const std::string& filename, float hitThreshold);

    ~SimulationEnvironment() {
        if (logFile.is_open()) {
        logFile.close();
    }
    };

    // Ownership-Transfer
    void addEntity(std::unique_ptr<SimulationEntity> entity);

    void step(float dt, const SimulationEnvironment& env);

    float getCurrentTime() const { return currentTime; }

    glm::vec3 getClosestTargetPosition() const {
        // currently assuming, that the first entity is always the target. 
        // Later check all entities and find the closest one.
        return entities[0]->getPosition(); 
    };

    glm::vec3 getClosestTargetVelocity() const {
        // currently assuming, that the first entity is always the target. 
        // Later check all entities and find the closest one.
        return entities[0]->getVelocity(); 
    };

    void checkForHit() {
        // Need at least 2 entities (target + interceptor) to check for a hit
        if (entities.size() < 2) return;

        float distance = glm::distance(entities[0]->getPosition(), entities[1]->getPosition());
        if (distance < hitThreshold) { // Treffer, wenn Abstand kleiner als hitThreshold
            isHit = true;
        } else {
            isHit = false;
        }
    };

    void initLogging(const std::string& filename);
    void logCurrentState();

// Für Unit-Tests: Lesezugriff auf Entitäten
const std::vector<std::unique_ptr<SimulationEntity>>& getEntities() const { return entities; }

};