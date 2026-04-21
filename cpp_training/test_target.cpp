#include <gtest/gtest.h>
#include "SimulationEnvironment.hpp"
#include "Target.hpp"
#include <cmath>
#include <glm/glm.hpp>

// TEST 1: Grundlegende Flugmechanik
TEST(TargetTest, TargetMovesCorrectlyAndName) {
    auto env = std::make_unique<SimulationEnvironment>("unitTest_log.csv", 10.0f);
    
    env->addEntity(std::make_unique<Target>("Target", glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(10.2f, -5.0f, 1.1f)));  

    env->step(0.1f, *env);

    // Entitäten aus der Umgebung holen, um Ergebnis zu prüfen
    const auto& entities = env->getEntities();
    const std::string& targetName = entities[0]->getName();
    
    // entities[0] ist Target
    glm::vec3 targetPos = entities[0]->getPosition();

    // corrected expected position after 0.1s: (10 + 10.2*0.1, 0 - 5*0.1, 0 + 1.1*0.1) = (11.02, -0.5, 0.11)
    EXPECT_NEAR(targetPos.x, 11.02f, 1e-5f); //1e-5f is for floating point comparison tolerance 
    EXPECT_NEAR(targetPos.y, -0.5f, 1e-5f);
    EXPECT_NEAR(targetPos.z, 0.11f, 1e-5f);
    EXPECT_EQ(targetName, "Target");
}
