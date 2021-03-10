#define _CRT_SECURE_NO_WARNINGS
#include <glm.hpp>
#include <iostream>
#include <reactphysics3d/reactphysics3d.h>

// ReactPhysics3D namespace 
using namespace reactphysics3d;

// Main function 
void main() {

    // First you need to create the PhysicsCommon object. 
    // This is a factory module that you can use to create physics 
    // world and other objects. It is also responsible for 
    // logging and memory management 
    PhysicsCommon physicsCommon;
    glm::vec3 rs = glm::vec3(1.0f, 2.4, 2.f);
    glm::mat4 rss = glm::mat4(1.f);
    std::cout << rs.x << rs.y << rs.z << "\n";
    // Create a physics world 
    PhysicsWorld* world = physicsCommon.createPhysicsWorld();

    // Create a rigid body in the world 
    Vector3 position(0, 20, 0);
    Quaternion orientation = Quaternion::identity();
    Transform transform(position, orientation);
    RigidBody* body = world->createRigidBody(transform);
    int r = world->getNbCollisionBodies();
    const decimal timeStep = 1.0f / 60.0f;

    // Step the simulation a few steps 
    for (int i = 0; i < 144; i++) {

        world->update(timeStep);

        // Get the updated position of the body 
        const Transform& transform = body->getTransform();
        const Vector3& position = transform.getPosition();
        const Vector3& vel = body->getLinearVelocity();

        // Display the position of the body 
        std::cout << "Body Position: (" << position.x << ", " <<
            position.y << ", " << position.z << ")  ";
        std::cout << "Body Velocity: (" << vel.x << ", " <<
            vel.y << ", " << vel.z << ")" << std::endl;
    }
    world->destroyRigidBody(body);
    body = NULL;
    if (!body)
        std::cout << "body gone \n";
}