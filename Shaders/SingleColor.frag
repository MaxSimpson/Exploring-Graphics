#version 330 core

in vec4 position;

out vec4 fragColor; // Fragment color

void
main() {
  /*fragColor = vec4(3 * position.x, 0.2 * position.y, 
                   0.75 * sin(position.x), 0.0f);
  if(position.x < 0.1f){
    fragColor = vec4(sin(position.x)* 50, tan(position.x * 75), 0.0f, 0.0f);
    if(position.y < 0.075f){
      fragColor = vec4(position.x * 1.62214f, 0.0f, 0.0f, 0.0f);
    }
  }*/

  fragColor = vec4(1.f, 0.f, 0.f, 0.f);
}
