#include <gtest/gtest.h>
#include "SimulationEnvironment.hpp"
#include "Target.hpp"
#include "Interceptor.hpp"
#include <glm/glm.hpp>
#include <cmath>

// define new class for testing SimulationEnvironment, using Google Test's TEST_F for fixture-based testing
class SimulationEnvironmentTest : public ::testing::Test { // inherit all public and protected functions from ::testing::Test
protected:
    void SetUp() override {
        // Create fresh environment for each test
        env = std::make_unique<SimulationEnvironment>("test_log.csv", 10.0f);
    }
    
    std::unique_ptr<SimulationEnvironment> env;
};

// Test 1: Initialization
TEST_F(SimulationEnvironmentTest, InitializesWithZeroTime) {
    EXPECT_EQ(env->getCurrentTime(), 0.0f);
}

// Test 2: Adding entities
TEST_F(SimulationEnvironmentTest, AddsEntityCorrectly) {
    env->addEntity(std::make_unique<Target>("Target", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 5.0, glm::vec3(1.0f, 0.0f, 0.0f)));
    
    const auto& entities = env->getEntities();
    EXPECT_EQ(entities.size(), 1);
    EXPECT_EQ(entities[0]->getName(), "Target");
}

// Test 3: Time increment after step
TEST_F(SimulationEnvironmentTest, IncrementsTimeOnStep) {
    env->addEntity(std::make_unique<Target>("Target", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 5.0, glm::vec3(1.0f, 0.0f, 0.0f)));
    
    env->step(0.5f, *env);
    EXPECT_NEAR(env->getCurrentTime(), 0.5f, 1e-6f);
    
    env->step(0.3f, *env);
    EXPECT_NEAR(env->getCurrentTime(), 0.8f, 1e-6f);
}

// Test 4: Multiple entities
TEST_F(SimulationEnvironmentTest, HandlesMultipleEntities) {
    env->addEntity(std::make_unique<Target>("Target", glm::vec3(100.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 5.0, glm::vec3(0.0f, 0.0f, 0.0f)));
    env->addEntity(std::make_unique<Interceptor>("Interceptor", glm::vec3(0.0f, 0.0f, 0.0f), 10.0f, 1.0f, 0.0f));
    
    const auto& entities = env->getEntities();
    EXPECT_EQ(entities.size(), 2);
}

// Test 5: getClosestTargetPosition
TEST_F(SimulationEnvironmentTest, ReturnsClosestTargetPosition) {
    env->addEntity(std::make_unique<Target>("Target", glm::vec3(50.0f, 20.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 5.0, glm::vec3(100.0f, 100.0f, 100.0f)));
    env->step(0.1f, *env);
    glm::vec3 targetPos = env->getClosestTargetPosition();
    EXPECT_EQ(targetPos.x, 51.0f);
    EXPECT_EQ(targetPos.y, 21.0f);
    EXPECT_EQ(targetPos.z, 1.0f);
}

// Test 6: Entities update during step
TEST_F(SimulationEnvironmentTest, UpdatesEntitiesDuringStep) {
    env->addEntity(std::make_unique<Target>("Target", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(5.0f, 10.0f, 0.0f), 5.0, glm::vec3(1.0f, 1.0f, 1.0f)));
    
    env->step(1.0f, *env);
    
    const auto& entities = env->getEntities();
    glm::vec3 updatedPos = entities[0]->getPosition();
    
    // Target should have moved: (0 + 5*1.0, 0 + 10*1.0, 0)
    EXPECT_NEAR(updatedPos.x, 6.0f, 1e-5f);
    EXPECT_NEAR(updatedPos.y, 11.0f, 1e-5f);
    EXPECT_NEAR(updatedPos.z, 1.0f, 1e-5f);
}