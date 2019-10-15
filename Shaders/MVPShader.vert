#version 330 core

uniform mat4 mv;
uniform mat4 itmv;
uniform mat4 mvp;

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexture;
in int textureNumberin;

out vec4 position;
out vec3 normal;
out vec2 textureCoord;
out int textureNumber;

void
main() {
  position = mv * vec4(vPosition, 1.0f);
  normal = normalize((itmv * vec4(vNormal, 0.f)).xyz);
  textureCoord = vTexture;

  gl_Position = mvp * vec4(vPosition, 1.0f);
}
