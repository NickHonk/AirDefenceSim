#pragma once

#include <vector>
#include <memory>
#include "SimulationEntity.hpp"
#include <iostream>
#include <fstream>

class SimulationEnvironment {
private:

    std::vector<std::unique_ptr<SimulationEntity>> entities;
    
    double currentTime;

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

    void step(double dt, const SimulationEnvironment& env);

    double getCurrentTime() const { return currentTime; }

    Vector3 getClosestTargetPosition() const {
        return entities[0]->getPosition(); // currently assuming, that the first entity is always the target. In a more complex simulation, we would need to check all entities and find the closest one.
    }

    void initLogging(const std::string& filename);
    void logCurrentState();

// Für Unit-Tests: Lesezugriff auf Entitäten
const std::vector<std::unique_ptr<SimulationEntity>>& getEntities() const { return entities; }

};