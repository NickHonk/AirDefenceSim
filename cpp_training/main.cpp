#include "Interceptor.hpp"
#include "Target.hpp"
#include "SimulationEnvironment.hpp"
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

int main() {
    auto env = std::make_unique<SimulationEnvironment>("simulation_log.csv", 0.1f); 

    // create target and interceptor with initial conditions
    auto target = std::make_unique<Target>("Feindliches Projektil", glm::vec3(1000, 0, 0), glm::vec3(0, 0, 0), 30, glm::vec3(-5.0f, 1.0f, 3.0f));
    auto interceptor = std::make_unique<Interceptor>("IRIS-T", glm::vec3(0, -500, 0), 50.0, 15.5, 1.0);

    float dt = 0.1f;

    env->addEntity(std::move(target));
    env->addEntity(std::move(interceptor));

    for (int i = 0; i < 300; ++i) {

        env->step(dt, *env);

        // delay
        //std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }

    std::cout << "Simulation beendet. Daten in simulation_log.csv gespeichert.\n";

    return 0;
}