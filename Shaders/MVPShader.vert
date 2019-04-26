#version 330 core

uniform mat4 mvp;

in vec3 vPosition;

out vec4 position;

void
main() {
  position = gl_Position = mvp * vec4(vPosition, 1.0f);
}
