#pragma once

#include <vector>
#include <memory>
#include <string>

// Ein einfacher 3D-Vektor für Position und Geschwindigkeit
struct Vector3 {
    double x, y, z;
};

class SimulationEnvironment;

class SimulationEntity {
protected:
    std::string name;
    Vector3 position;
    Vector3 velocity;

public:
    SimulationEntity(std::string n, Vector3 pos) : name(n), position(pos), velocity({0,0,0}) {}
    virtual ~SimulationEntity() = default; // Wichtig für Polymorphie!

    // Die zentrale Methode: Jedes Objekt berechnet seinen nächsten Zustand selbst
    virtual void update(double dt, const SimulationEnvironment& env) = 0; 

    Vector3 getPosition() const { return position; }
    std::string getName() const { return name; }
};