#include <gtest/gtest.h>
#include "SimulationEnvironment.hpp"
#include "Target.hpp"
#include <cmath>
#include <glm/glm.hpp>

// TEST 1: Grundlegende Flugmechanik
TEST(TargetTest, TargetMovesCorrectlyAndName) {
    auto env = std::make_unique<SimulationEnvironment>("unitTest_log.csv", 10.0f);
    
    env->addEntity(std::make_unique<Target>("Target", glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), 30, glm::vec3(-100, 100, 100)));  

    env->step(0.1f, *env);

    // Entitäten aus der Umgebung holen, um Ergebnis zu prüfen
    const auto& entities = env->getEntities();
    const std::string& targetName = entities[0]->getName();
    
    // entities[0] ist Target
    glm::vec3 targetPos = entities[0]->getPosition();
    glm::vec3 targetVel = entities[0]->getVelocity();
    float accelCounter = dynamic_cast<Target*>(entities[0].get())->getAccelCounter();

    // expected position after 0.1s: 
    EXPECT_NEAR(targetPos.x, -1.0f, 1e-5f); //1e-5f is for floating point comparison tolerance 
    EXPECT_NEAR(targetPos.y, 1.0f, 1e-5f);
    EXPECT_NEAR(targetPos.z, 1.0f, 1e-5f);
    EXPECT_NEAR(targetVel.x, -10.0f, 1e-5f); 
    EXPECT_NEAR(targetVel.y, 10.0f, 1e-5f);
    EXPECT_NEAR(targetVel.z, 10.0f, 1e-5f);
    EXPECT_EQ(targetName, "Target");
    EXPECT_EQ(accelCounter, 29);
}
