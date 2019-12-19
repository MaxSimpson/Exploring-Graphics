#version 330 core

// Material Data
struct material {
  sampler2D tex;
  vec3 ks;
};

uniform material materials[50];

//View model
uniform mat4 view;

// Model Color
uniform vec3 color;

// Light Data
uniform vec4 light;
uniform vec3 diffuse;
uniform vec3 ambient;
uniform vec3 specular;

in vec4 position;
in vec3 normal;
in vec2 textureCoord;

flat in int textureNumber;

out vec4 fragColor; // Fragment color

void
main() {

    // Ambient intensity
    vec4 I_a = vec4(ambient, 1);
    // Ambient material
    // I_a = I_a * vec4(materials[0].ka, 1);

    // Diffuse intensity
    vec4 I_d = vec4(diffuse, 1);
    // Diffuse material
    // I_d = I_d * vec4(materials[0].tex, 1);

    // Light direction
    vec4 lightTransformed = view * light;
    vec3 L;
    if(light.w == 0.f)
      L = -normalize(lightTransformed).xyz;
    else {
      L = normalize(lightTransformed - position).xyz;
    }
    //vec3 L = -(view * vec4(-1, -1, -1, 0)).xyz;

    //Color Value
    vec4 alphaColor = vec4(color, 1);

    float N_L = max(dot(normalize(L), normal), 0.f);

    // vec4 ka;
    vec3 texColor = vec3(texture(materials[1].tex, textureCoord));

    //fragColor = I_a * ka + I_d * N_L;

    // Object color
    //fragColor *= alphaColor;

    fragColor = vec4(texColor, 1.0f);

    // fragColor = vec4(255, 0, 0, 0);
}
