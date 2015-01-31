//
//  opengl.cpp
//  TicTacToe
//
//  Created by Tim on 1/23/15.
//  Copyright (c) 2015 Tim. All rights reserved.
//

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

// Include GLEW headers
#include <GL/glew.h>
// Include GLFW headers
#include <GLFW/glfw3.h>
// Include GLM headers
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
// Include Shader Helpers
#include "shader.h"
// Include texture helpers
#include "texture.h"
// Include camera control helpers
#include "controls.h"
// Include constants
#include "constants.h"
// Include object loader
#include "objloader.h"

#include "opengl.h"

using namespace std;

int opengl(void)
{
    GLFWwindow* window;
    
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    /* Setup GLFW and OpenGL */
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_SAMPLES,4); //4x AA
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Textured Cube", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    /* Enable mouse controls */
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    /* Setup GLEW */
    glewExperimental = true;
    if(glewInit() != GLEW_OK)
        throw runtime_error("glewInit failed");
    
    /* Print out some info about the graphics drivers */
    cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
    cout << "Vendor: " << glGetString(GL_VENDOR) << endl;
    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    
    // Blue background
    glClearColor(0.0f, 0.0f, 0.5f, 0.0f);
    
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    // Enable face culling
    glEnable(GL_CULL_FACE);
    // Enable multisample anti aliasing
    glEnable(GL_MULTISAMPLE);
    
    // Create the vertex array object needed for all the VBOs
    GLuint VertexArrayID = 0;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    // Read our .obj file
    vector< glm::vec3 > vertices;
    vector< glm::vec2 > uvs;
    vector< glm::vec3 > normals;
    vector<unsigned int> indices;
    loadObjIndexed("cube.obj", indices, vertices, uvs, normals);
    
    // This will identify our vertex buffer
    GLuint vertexbuffer;
    
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    
    // Do the same for the UV buffer
    GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size()*sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
    
    // Again for normal buffer
    GLuint normalbuffer;
    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
    
    // Again for index buffer
    GLuint indexbuffer;
    glGenBuffers(1, &indexbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    
    // Load and create the texture
    //GLuint textureId = loadBmp("uvtemplate2.bmp");
    GLuint textureId = loadDDS("uvmapcube.DDS");
    
    // Create program
    GLuint programID = GenerateProgram("vertex.glsl", "fragment.glsl");
    
    // Create MVP matrices
    GLuint MVPmatrix = glGetUniformLocation(programID, "MVPmat");
    GLuint Mmatrix = glGetUniformLocation(programID, "Mmat");
    GLuint Vmatrix = glGetUniformLocation(programID, "Vmat");
    GLuint Pmatrix = glGetUniformLocation(programID, "Pmat");
    GLuint normalMmatrix = glGetUniformLocation(programID, "normalMmat");
    float rotation = 0.0f;
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,0));
    glm::mat4 rotate = glm::rotate(rotation, glm::vec3(0,1,0));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
    glm::mat4 model = translate*rotate*scale;
    glm::mat3 normalModelMat = glm::mat3(rotate);
    // The normals only need rotations to be applied
    glm::mat4 view = glm::lookAt(glm::vec3(4,3,-3), glm::vec3(0,0,0), glm::vec3(0,1,0));
    glm::mat4 projection = glm::perspective(45.0f, 640.0f/480.0f, 0.1f, 100.0f);
    glm::mat4 MVP = projection*view*model;
    
    // Get texture sampler uniform
    GLuint texSampler = glGetUniformLocation(programID, "texSampler");
    
    // Set up lighting and shading
    glm::vec3 lightColor(1,1,1);
    glm::float_t lightPower = 75.0f;
    glm::vec3 lightPos(0,0,10);
    glm::float_t specularPower = 5;
    GLuint lightColor_fs = glGetUniformLocation(programID, "lightColor");
    GLuint lightPower_fs = glGetUniformLocation(programID, "lightPower");
    GLuint lightPos_world = glGetUniformLocation(programID, "lightPos_world");
    GLuint cameraPos_world = glGetUniformLocation(programID, "cameraPos_world");
    GLuint specularPower_fs = glGetUniformLocation(programID, "specularPower");
    
    // 1st attribute buffer : vertices
    int id = glGetAttribLocation(programID, "vertexPosition_modelspace");
    glEnableVertexAttribArray(id);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
                          id,           // attribute 0.
                          3,           // size
                          GL_FLOAT,    // type
                          GL_FALSE,    // normalized?
                          0,           // stride
                          (void*)0     // array buffer offset
                          );
    
    // 2nd attribute buffer : uv coord
    id = glGetAttribLocation(programID, "vertexUV");
    glEnableVertexAttribArray(id);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glVertexAttribPointer(id, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    // 3rd attribute buffer : uv coord
    id = glGetAttribLocation(programID, "vertexNormal");
    glEnableVertexAttribArray(id);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glVertexAttribPointer(id, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    
    // Set up instancing
    GLuint size = 20;
    vector< glm::vec3 > instancePos;
    for(int x = 0; x < size; x++) {
        for(int y = 0; y<size; y++) {
            for(int z = 0; z<size; z++)
                instancePos.push_back(glm::vec3(-2.0*size+x*4, -2.0*size+y*4, -2.0*size+z*4));
        }
    }
    GLuint instancePosBuffer;
    glGenBuffers(1, &instancePosBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, instancePosBuffer);
    glBufferData(GL_ARRAY_BUFFER, instancePos.size()*sizeof(glm::vec3), &instancePos[0], GL_STATIC_DRAW);
    id = glGetAttribLocation(programID, "instancedPos");
    glEnableVertexAttribArray(id);
    glVertexAttribPointer(id, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glVertexAttribDivisor(id, 1);
    
    glfwSetCursorPos(window, 0, 0);
    /* Loop until the user closes the window */
    while (glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && !glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        /* Render here */
        // Use our shader
        glUseProgram(programID);
        
        // Set up model movements (rotation and etc)
        if(rotation < 360.0f) {
            rotation += 0.05f;
        } else {
            rotation = 0;
        }
        rotate = glm::rotate(rotation, glm::vec3(0,1,0));
        model = translate*rotate*scale;
        normalModelMat = glm::mat3(rotate);
        computeMVP(&model, window, view, projection);
        MVP = projection*view*model;
        glUniformMatrix4fv(MVPmatrix, 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(Mmatrix, 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(Vmatrix, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(Pmatrix, 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix3fv(normalMmatrix, 1, GL_FALSE, &normalModelMat[0][0]);
        
        // Bind and setup texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureId);
        // Set our "texSampler" sampler to user Texture Unit 0
        glUniform1i(texSampler, 0);
        
        // Lighting and shading
        glUniform3fv(lightPos_world, 1, &lightPos[0]);
        glUniform3fv(lightColor_fs, 1, &lightColor[0]);
        glUniform1f(lightPower_fs, lightPower);
        glUniform1f(specularPower_fs, specularPower);
        glUniform3fv(cameraPos_world, 1, &getCameraPosition()[0]);
        
        // Bind the vertex array objects
        glBindVertexArray(VertexArrayID);
        
        // Draw the triangle !
        //glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glDrawElementsInstanced(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0, pow(size, 3));
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        
        /* Poll for and process events */
        glfwPollEvents();
    }
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glfwTerminate();
    return 0;
}
