//
//  shader.cpp
//  OpenGL1
//
//  Created by Tim on 12/27/14.
//  Copyright (c) 2014 Tim. All rights reserved.
//
#include <fstream>
#include <stdexcept>

#include <GL/glew.h>

#include "shader.h"

using namespace std;

// Function to read external files into a string
string fileReader(const char * filePath) {
    string result = "";
    ifstream fileStream(filePath);
    if(fileStream.is_open()) {
        string line = "";
        while(getline(fileStream, line)) {
            result += (line + "\n");
        }
        fileStream.close();
    } else {
        throw runtime_error((string)"Cannot open file: " + (string)filePath + (string)"\n");
        return 0;
    }
    return result;
}

// Create, load, compile, and link shaders
GLuint LoadVertexShader(const char *vertexFilePath) {
    // Create
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    
    // Load
    string vertexShaderSource = fileReader(vertexFilePath);
    const GLchar * vertexShaderSourcePtr = vertexShaderSource.c_str(); // Convert to const char
    GLint length = (int)strlen(vertexShaderSourcePtr);
    
    // Compile
    glShaderSource(vertexShaderID, 1, &vertexShaderSourcePtr, &length);
    glCompileShader(vertexShaderID);
    
    // Check compilation result to make sure everything is good
    GLint Result = GL_FALSE;
    int InfoLogLength;
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    char errorMsg[InfoLogLength];
    glGetShaderInfoLog(vertexShaderID, InfoLogLength, NULL, &errorMsg[0]);
    fprintf(stdout, "%s\n", &errorMsg[0]);
    
    return vertexShaderID;
}

GLuint LoadFragmentShader(const char *fragmentShaderPath) {
    // Create
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    
    // Load
    string fragmentShaderSource = fileReader(fragmentShaderPath);
    const GLchar * fragmentShaderSourcePtr = fragmentShaderSource.c_str(); // Convert to const char
    GLint length = (int)strlen(fragmentShaderSourcePtr);
    
    // Compile
    glShaderSource(fragmentShaderID, 1, &fragmentShaderSourcePtr, &length);
    glCompileShader(fragmentShaderID);
    
    // Check compilation result to make sure everything is good
    GLint Result = GL_FALSE;
    int InfoLogLength;
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    char errorMsg[InfoLogLength];
    glGetShaderInfoLog(fragmentShaderID, InfoLogLength, NULL, &errorMsg[0]);
    fprintf(stdout, "%s\n", &errorMsg[0]);
    
    return fragmentShaderID;
}

GLuint GenerateProgram(const char *vertexFilePath, const char *fragmentShaderPath) {
    // Create and link program with shaders
    GLuint program = glCreateProgram();
    GLuint vertexShader = LoadVertexShader(vertexFilePath);
    GLuint fragmentShader = LoadFragmentShader(fragmentShaderPath);
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    
    glLinkProgram(program);
    
    // Check program
    GLint Result = GL_FALSE;
    int InfoLogLength;
    glGetProgramiv(program, GL_LINK_STATUS, &Result);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);
    char errorMsg[InfoLogLength];
    glGetProgramInfoLog(program, InfoLogLength, NULL, &errorMsg[0]);
    fprintf(stdout, "%s\n", &errorMsg[0]);
    
    // Delete shaders after they are linked with program
    // This clears up memory
    // Deletion is deferred till after detaching the shaders
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return program;
}