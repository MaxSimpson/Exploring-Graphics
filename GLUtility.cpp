#include "GLUtility.h"

// GL
#include "GLInclude.h"

void build2DMipmaps(int _target, int _internalFormat,
                    unsigned int _width, unsigned int _height,
                    int _format, int _type,
                    const void* _data) {
  gluBuild2DMipmaps(_target, _internalFormat, _width, _height,
                    _format, _type, _data);
}
