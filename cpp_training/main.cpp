#include "Interceptor.hpp"
#include "Target.hpp"
#include "SimulationEnvironment.hpp"
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

int main() {
    auto env = std::make_unique<SimulationEnvironment>("simulation_log.csv");

    // create target and interceptor with initial conditions
    auto target = std::make_unique<Target>("Feindliche Drohne", Vector3{1000, 500, 0}, Vector3{-50, 0, 0});
    auto interceptor = std::make_unique<Interceptor>("IRIS-T", Vector3{0.0, 0.0, 0.0}, 90.0);

    // save simulation data to csv file
    std::ofstream logFile("simulation_log.csv");
    logFile << "Time,TargetX,TargetY,InterceptorX,InterceptorY\n";

    double dt = 0.1;

    env->addEntity(std::move(target));
    env->addEntity(std::move(interceptor));

    for (int i = 0; i < 150; ++i) {

        env->step(dt, *env);

        // delay
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }

    std::cout << "Simulation beendet. Daten in simulation_log.csv gespeichert.\n";

    return 0;
}