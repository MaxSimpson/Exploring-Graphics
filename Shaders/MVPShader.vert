#version 330 core

uniform mat4 mvp;

in vec3 vPosition;
in vec3 vNormal;

out vec4 position;
out vec3 normal;

void
main() {
  position = gl_Position = mvp * vec4(vPosition, 1.0f);
  normal = vNormal;
}
