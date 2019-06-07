#version 330 core

// struct MyStruct {
//   vec4 stuff;
//   int x;
// };

// const int MAX_MY_STRUCTS
// uniform MyStruct myStructs[MAX_MY_STRUCTS];

// myStructs[0].x;


uniform mat4 view;

// Model Color
uniform vec3 color;

// Light Data
uniform vec4 light;
uniform vec3 diffuse;
uniform vec3 ambient;
uniform vec3 specular;

// Material Data
uniform vec3 ka;
uniform vec3 kd;
uniform vec3 ks;

uniform sampler2D textureSampler;

in vec4 position;
in vec3 normal;
in vec2 textureCoord;

out vec4 fragColor; // Fragment color

void
main() {

    // Ambient intensity
    vec4 I_a = vec4(ambient, 1);
    // Ambient material
    I_a = I_a * vec4(ka, 1);

    // Diffuse intensity
    vec4 I_d = vec4(diffuse, 1);
    // Diffuse material
    I_d = I_d * vec4(kd, 1);

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

    float N_L = dot(normalize(L), normal);

    if(N_L < 0)
      // Away from light
      fragColor = I_a;
    else{
      // Facing light
      fragColor = (I_d * N_L + I_a);
    }

    // Object color
    fragColor *= alphaColor;
    fragColor *= texture(textureSampler, textureCoord);
}
