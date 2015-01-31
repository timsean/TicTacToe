#version 410 core

in vec2 UV;
in vec3 lightDirection_world;
in vec3 eyeDirection_world;
in vec3 normal_world;
out vec3 finalColor;
uniform sampler2D texSampler;
uniform vec3 lightColor;
uniform float lightPower;
uniform float specularPower;

void main()
{
    vec3 materialDiffuse = texture(texSampler, UV).rgb;
    vec3 materialAmbient = vec3(0.1,0.1,0.1)*materialDiffuse;
    vec3 materialSpecular = vec3(0.3,0.3,0.3);
    
    vec3 l = normalize(lightDirection_world);
    float cosTheta = max(0.0,dot(normal_world,l));
    float lightDist = length(lightDirection_world);
    
    vec3 lightAdjusted = cosTheta*lightPower*lightColor;
    
    // Calculate specular only if surface is facing light
    vec3 specularLight = vec3(0,0,0);
    if(cosTheta > 0.0f) {
        vec3 reflectedLight = normalize(reflect(-lightDirection_world, normal_world));
        float cosAOR = max(0.0, dot(normalize(eyeDirection_world), reflectedLight));
        specularLight = pow(cosAOR, specularPower)*lightColor*lightPower*materialSpecular;
    }
    
    vec3 linearColor = materialAmbient+
        (lightAdjusted*materialDiffuse+specularLight)/(1+lightDist*lightDist);
    // Gamme correction
    /*
    finalColor = vec3(pow(linearColor.r, 1.0/2.2),
                      pow(linearColor.g, 1.0/2.2),
                      pow(linearColor.b, 1.0/2.2));*/
    finalColor = linearColor;
}