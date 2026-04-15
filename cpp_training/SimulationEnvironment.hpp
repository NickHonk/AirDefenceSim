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

public:
    SimulationEnvironment(const std::string& filename);

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
        return entities[0]->getPosition(); // currently assuming, that the first entity is always the target. In a more complex simulation, we would need to check all entities and find the closest one.
    }

    void initLogging(const std::string& filename);
    void logCurrentState();

// Für Unit-Tests: Lesezugriff auf Entitäten
const std::vector<std::unique_ptr<SimulationEntity>>& getEntities() const { return entities; }

};