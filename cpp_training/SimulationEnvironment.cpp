#include "SimulationEnvironment.hpp"
#include <iostream>
    
SimulationEnvironment::SimulationEnvironment(const std::string& filename) : currentTime(0.0) {
    this->initLogging(filename);
}

/* SimulationEnvironment::~SimulationEnvironment() {
    if (logFile.is_open()) {
        logFile.close();
    }
} */

void SimulationEnvironment::addEntity(std::unique_ptr<SimulationEntity> entity) {
    entities.push_back(std::move(entity));
}

void SimulationEnvironment::step(double dt, const SimulationEnvironment& env) {

    std::cout << "Zeit: " << currentTime << "s, " << ")\n" << std::endl;

    for (auto& entity : entities) {
        entity->update(dt, env);
    }
    currentTime += dt;  
    this->logCurrentState();
}

void SimulationEnvironment::initLogging(const std::string& filename) {
    logFile.open(filename);
    if (logFile.is_open()) {
        logFile << "Time,TargetX,TargetY,InterceptorX,InterceptorY\n";
    } else {
        std::cerr << "Fehler: Konnte Log-Datei nicht erstellen!\n";
    }
}

void SimulationEnvironment::logCurrentState() {
    // Sicherheits-Check: Nur loggen, wenn die Datei offen ist und wir mindestens 2 Entitäten haben
    if (!logFile.is_open() || entities.size() < 2) return;

    logFile << currentTime << ","
            << entities[0]->getPosition().x << "," << entities[0]->getPosition().y << ","
            << entities[1]->getPosition().x << "," << entities[1]->getPosition().y << "\n";
}