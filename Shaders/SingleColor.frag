#version 330 core

in vec4 position;

out vec4 fragColor; // Fragment color

void
main() {
  if(position.x < 0)
    fragColor = vec4(1.0f, 0.0f, 0.0f, 0.0f);
  else
    fragColor = vec4(0.0f, 1.0f, 0.0f, 0.0f);
}
