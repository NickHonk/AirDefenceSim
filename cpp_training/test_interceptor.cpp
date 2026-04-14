#include <gtest/gtest.h>
#include "SimulationEnvironment.hpp"
#include "Target.hpp"
#include "Interceptor.hpp"
#include <cmath>

// TEST 1: Grundlegende Flugmechanik
TEST(InterceptorTest, MovesTowardsTargetCorrectly) {
    auto env = std::make_unique<SimulationEnvironment>("unitTest_log.csv");
    
    env->addEntity(std::make_unique<Target>("Target", Vector3{100.0, 0.0, 0.0}, Vector3{0.0, 0.0, 0.0}));
    
    env->addEntity(std::make_unique<Interceptor>("Missile", Vector3{0.0, 0.0, 0.0}, 10.0));

    env->step(1.0, *env);

    // Entitäten aus der Umgebung holen, um Ergebnis zu prüfen
    const auto& entities = env->getEntities();
    
    // entities[1] ist Interceptor
    Vector3 interceptorPos = entities[1]->getPosition();

    EXPECT_DOUBLE_EQ(interceptorPos.x, 10.0);
    EXPECT_DOUBLE_EQ(interceptorPos.y, 0.0);
    EXPECT_DOUBLE_EQ(interceptorPos.z, 0.0);
}

// TEST 2: Division durch Null
TEST(InterceptorTest, HandlesZeroDistanceWithoutNaN) {
    auto env = std::make_unique<SimulationEnvironment>("unitTest_log.csv");
    
    // Ziel und Interceptor spawnen am EXAKT selben Punkt (0,0,0)
    env->addEntity(std::make_unique<Target>("Target", Vector3{0.0, 0.0, 0.0}, Vector3{0.0, 0.0, 0.0}));
    env->addEntity(std::make_unique<Interceptor>("Missile", Vector3{0.0, 0.0, 0.0}, 10.0));

    // Einen Schritt simulieren
    env->step(0.1, *env);

    const auto& entities = env->getEntities();

    Vector3 interceptorPos = entities[1]->getPosition();

    EXPECT_FALSE(std::isnan(interceptorPos.x));
}