#version 330 core

in vec3 vPosition;

out vec4 position;

void
main() {
  position = gl_Position = vec4(vPosition, 1.0f);
}
