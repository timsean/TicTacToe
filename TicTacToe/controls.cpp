//
//  controls.cpp
//  OpenGL
//
//  Created by Tim on 1/2/15.
//  Copyright (c) 2015 Tim. All rights reserved.
//

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include "controls.h"
#include "constants.h"

// deltatime
float deltaTime = 0;
double lastTime;
// position
glm::vec3 position = glm::vec3(INITIAL_CAMERA_X, INITIAL_CAMERA_Y, INITIAL_CAMERA_Z);
// direction
glm::vec3 direction;
glm::vec3 right;
glm::vec3 up;
// horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// vertical angle : 0, look at the horizon
float verticalAngle = 0.0f;
// Field of View
float FoV = 45.0f;

float regularSpeed = 5.0f;
float speed = 5.0f; // 3 units / second
float mouseSpeed = 0.05f;
double xpos, ypos;

void getDirection(GLFWwindow* window) {
    glfwGetCursorPos(window, &xpos, &ypos);
    glfwSetCursorPos(window, 0, 0);
    
    // Compute new orientation
    horizontalAngle += mouseSpeed * deltaTime * float(-xpos);
    verticalAngle   += mouseSpeed * deltaTime * float(-ypos);
    
    // Compute new direction
    direction.x = cos(verticalAngle)*sin(horizontalAngle);
    direction.y = sin(verticalAngle);
    direction.z = cos(verticalAngle)*cos(horizontalAngle);
    
    // Compute right
    right.x = sin(horizontalAngle-1.57f);
    right.y = 0;
    right.z = cos(horizontalAngle-1.57f);
    
    // Compute up
    up = glm::cross(right, direction);
}

void getPosition(GLFWwindow* window) {
    // Increase speed if shift key is held down
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        speed = 5*regularSpeed;
    } else {
        speed = regularSpeed;
    }
    // Move forward
    if (glfwGetKey(window, GLFW_KEY_W ) == GLFW_PRESS){
        position += direction * deltaTime * speed;
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_S ) == GLFW_PRESS){
        position -= direction * deltaTime * speed;
    }
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_D ) == GLFW_PRESS){
        position += right * deltaTime * speed;
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_A ) == GLFW_PRESS){
        position -= right * deltaTime * speed;
    }
    // Move up
    if (glfwGetKey(window, GLFW_KEY_R ) == GLFW_PRESS){
        position += up * deltaTime * speed;
    }
    // Move down
    if (glfwGetKey(window, GLFW_KEY_F ) == GLFW_PRESS){
        position -= up * deltaTime * speed;
    }
}

glm::vec3 getCameraPosition() {
    return position;
}

void computeMVP(glm::mat4* model, GLFWwindow* window,
                     glm::mat4 &viewOut, glm::mat4 &projOut) {
    // This runs only once, setting the initial lastTime
    // Static variable
    static double lastTime = glfwGetTime();
    
    double time = glfwGetTime();
    deltaTime = float(time - lastTime);
    // Display render time (placed here for simplicity)
    char renderTime[20];
    sprintf(renderTime, "%.2f ms, %.2f fps", deltaTime*1000, 1/deltaTime);
    glfwSetWindowTitle(window, renderTime);
    
    getDirection(window);
    getPosition(window);
    viewOut = glm::lookAt(position, position+direction, up);
    projOut = glm::perspective(FoV, 4.0f/3.0f, 0.1f, 500.0f);
    // For the next frame, the "last time" will be "now"
    lastTime = time;
}