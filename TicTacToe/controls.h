//
//  controls.h
//  OpenGL
//
//  Created by Tim on 1/2/15.
//  Copyright (c) 2015 Tim. All rights reserved.
//

#ifndef __OpenGL__controls__
#define __OpenGL__controls__

void computeMVP(glm::mat4* model, GLFWwindow* window,
                glm::mat4 &viewOut, glm::mat4 &MVPout);

glm::vec3 getCameraPosition();

#endif /* defined(__OpenGL__controls__) */
