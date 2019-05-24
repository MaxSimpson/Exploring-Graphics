#version 330 core

uniform mat4 view;
uniform vec3 color;

in vec4 position;
in vec3 normal;

out vec4 fragColor; // Fragment color

void
main() {

    // Ambient intensity
    vec4 I_a = vec4(0.2, 0.2, 0.2, 0.2);

    // Diffuse intensity
    vec4 I_d = vec4(0.8, 0.8, 0.8, 0.8); 

    // Light direction
    vec3 L = -(view * vec4(-1, -1, -1, 0)).xyz;

    //Color Value
    vec4 alphaColor = vec4(color, 1);

    float N_L = dot(normalize(L), normal);

    if(N_L < 0)
        fragColor = I_a;
    else{
        fragColor = (I_d * N_L + I_a);
    }

    fragColor *= alphaColor;
}