#version 330 core

uniform mat4 view;

//Model Color
uniform vec3 color;

//Light Data
uniform vec4 light;
uniform vec3 diffuse;
uniform vec3 ambient;
uniform vec3 specular;

in vec4 position;
in vec3 normal;

out vec4 fragColor; // Fragment color

void
main() {

    // Ambient intensity
    vec4 I_a = vec4(ambient, 1);
    //vec4 I_a = vec4(0.2, 0.2, 0.2, 0.2);

    // Diffuse intensity
    vec4 I_d = vec4(diffuse, 1);
    //vec4 I_d = vec4(0.8, 0.8, 0.8, 0.8); 

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
        fragColor = I_a;
    else{
        fragColor = (I_d * N_L + I_a);
    }

    fragColor *= alphaColor;
    //fragColor = light;
}
