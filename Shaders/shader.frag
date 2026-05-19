#version 330 core

in vec4 vCol;
in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;
in vec4 directionalLightSpacePos;

out vec4 colour;

const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHTS = 3;

struct Light {
    vec3 colour;
    float ambientIntensity;
    float diffuseIntensity;
};

struct DirectionalLight {
    Light base;
    vec3 direction;
};

struct PointLight {
    Light base;
    vec3 position;
    float constant;
    float linear;
    float exponent;
};

struct SpotLight {
    PointLight base;
    vec3 direction;
    float edge;
};

struct Material {
    float specularIntensity;
    float shininess;
    float albedoMap;
};

uniform int pointLightCount;
uniform int spotLightCount;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

uniform sampler2D theTexture;
uniform sampler2D directionalShadowMap;

uniform Material material;

uniform vec3 eyePosition;

float calcDirectionalShadowFactor (DirectionalLight light) {
vec3 projCoords = directionalLightSpacePos.xyz / directionalLightSpacePos.w;
    projCoords = projCoords * 0.5 + 0.5;

    float currentDepth = projCoords.z;

    vec3 pointNormal = normalize(normal);
    vec3 lightDir = normalize(light.direction);
    float bias = max(0.05 * (1.0 - dot(pointNormal, lightDir)), 0.005);

    float shadow = 0.0;

    vec2 texelSize = 1.0 / textureSize(directionalShadowMap, 0);
    for(int x = -1; x <= 1; x++) {
        for(int y = -1; y <= 1; y++) {
            float pcfDepth = texture(directionalShadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }

    shadow /= 9.0;

    if (projCoords.z > 1.0) {
        shadow = 0.0;
    }

    return shadow;
}

vec4 calcLightByDirection(Light light, vec3 direction, float shadowFactor) {
    vec4 ambientColour = vec4(light.colour, 1.0) * light.ambientIntensity;

    float diffuseFactor = max(dot(normalize(normal), -normalize(direction)), 0.0);
    vec4 diffuseColour = vec4(light.colour, 1.0) * light.diffuseIntensity * diffuseFactor;

    vec4 specularColour = vec4(0, 0, 0, 0);

    if (diffuseFactor > 0.0) {
        vec3 fragToEye = normalize(eyePosition - fragPos);
        vec3 reflectedVertex = normalize(reflect(direction, normalize(normal)));

        float specularFactor = dot(fragToEye, reflectedVertex);
        if (specularFactor > 0.0) {
            specularFactor = pow(specularFactor, material.shininess);
            specularColour = vec4(light.colour * material.specularIntensity * specularFactor, 1.0);
        }
    }

    return (ambientColour + (1 - shadowFactor) * (diffuseColour + specularColour));
}

vec4 calcDirectionalLight() {
    float shadowFactor = calcDirectionalShadowFactor(directionalLight);
    return calcLightByDirection(directionalLight.base, directionalLight.direction, shadowFactor);
}

vec4 calcPointLight(PointLight pLight) {
    vec3 direction = fragPos - pLight.position;
    float distance = length(direction);
    direction = normalize(direction);

    vec4 colour = calcLightByDirection(pLight.base, direction, 0.0);
    float attenuation = pLight.exponent * distance * distance +
                        pLight.linear * distance +
                        pLight.constant;

    return (colour / attenuation);
}

vec4 calcSpotLight(SpotLight sLight) {
    vec3 rayDirection = normalize(fragPos - sLight.base.position);
    float slFactor = dot(rayDirection, sLight.direction);

    if (slFactor > sLight.edge) {
        vec4 colour = calcPointLight(sLight.base);
        float slEffect = (1.0 - (1.0 - slFactor) * (1.0 / (1.0 - sLight.edge)));
        return (colour * slEffect);
    } else {
        return vec4(0, 0, 0, 0);
    }
}

vec4 calcPointLights() {
    vec4 totalColour = vec4(0, 0, 0, 0);

    for (int i = 0; i < pointLightCount; i++) {
        totalColour += calcPointLight(pointLights[i]);
    }
    return totalColour;
}

vec4 calcSpotLights() {
    vec4 totalColour = vec4(0, 0, 0, 0);

    for (int i = 0; i < spotLightCount; i++) {
        totalColour += calcSpotLight(spotLights[i]);
    }
    return totalColour;
}

    void main() {
        vec4 finalColour = calcDirectionalLight();
        finalColour += calcPointLights();
        finalColour += calcSpotLights();

        colour = texture(theTexture, texCoord) * finalColour;
    }
    