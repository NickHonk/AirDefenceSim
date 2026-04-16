#include <gtest/gtest.h>
#include "SimulationEnvironment.hpp"
#include "Target.hpp"
#include "Interceptor.hpp"
#include <cmath>
#include <glm/glm.hpp>

// TEST 1: Grundlegende Flugmechanik
TEST(InterceptorTest, MovesTowardsTargetCorrectly) {
    auto env = std::make_unique<SimulationEnvironment>("unitTest_log.csv");
    
    env->addEntity(std::make_unique<Target>("Target", glm::vec3(100.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)));  
    env->addEntity(std::make_unique<Interceptor>("Missile", glm::vec3(0.0f, 0.0f, 0.0f), 10.0f));

    env->step(1.0f, *env);

    // Entitäten aus der Umgebung holen, um Ergebnis zu prüfen
    const auto& entities = env->getEntities();
    
    // entities[1] ist Interceptor
    glm::vec3 interceptorPos = entities[1]->getPosition();

    EXPECT_EQ(interceptorPos, glm::vec3(10.0f, 0.0f, 0.0f));
}

// TEST 2: Division durch Null
TEST(InterceptorTest, HandlesZeroDistanceWithoutNaN) {
    auto env = std::make_unique<SimulationEnvironment>("unitTest_log.csv");
    
    // Ziel und Interceptor spawnen am EXAKT selben Punkt (0,0,0)
    env->addEntity(std::make_unique<Target>("Target", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
    env->addEntity(std::make_unique<Interceptor>("Missile", glm::vec3(0.0f, 0.0f, 0.0f), 10.0f));

    // Einen Schritt simulieren
    env->step(0.1f, *env);

    const auto& entities = env->getEntities();

    glm::vec3 interceptorPos = entities[1]->getPosition();

    EXPECT_FALSE(glm::any(glm::isnan(interceptorPos)));
}