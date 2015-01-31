#version 410 core

// Input vertex data, different for all executions of this shader.
layout(location = 0)in vec3 vertexPosition_modelspace;
layout(location = 1)in vec2 vertexUV;
layout(location = 2)in vec3 vertexNormal;
layout(location = 3)in vec3 instancedPos;
out vec2 UV;
out vec3 lightDirection_world;
out vec3 eyeDirection_world;
out vec3 normal_world;
uniform mat4 MVPmat;
uniform mat4 Mmat;
uniform mat4 Vmat;
uniform mat4 Pmat;
uniform mat3 normalMmat;
uniform vec3 lightPos_world;
uniform vec3 cameraPos_world;

void main(){
    vec4 vPosWorldSpace = Mmat*vec4(vertexPosition_modelspace,1) + vec4(instancedPos, 0);
    gl_Position = Pmat*Vmat * vPosWorldSpace;
    
    //vec3 lightPos_rotated = normalMmat*lightPos_world;
    
    eyeDirection_world = cameraPos_world - vPosWorldSpace.xyz;
    normal_world = normalMmat * vertexNormal;
    lightDirection_world = lightPos_world - vPosWorldSpace.xyz;
    UV = vertexUV;
}
