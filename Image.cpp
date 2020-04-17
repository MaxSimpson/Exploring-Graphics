#include "Image.h"

// STL
#include <iostream>
using namespace std;

// Qt includes
#include <QtGui/QColor>
#include <QtGui/QImage>
#include <QtOpenGL/QGLWidget>

// Engine
#include "GLUtility.h"

Image::
Image(const std::string& _filename) {
  // Load image from file
  // cout << "        Texture filename: " << _filename << endl;
  m_textureData = new QImage(_filename.c_str());
  if(m_textureData->isNull()) {
    cerr << "        Cannot load texture '" << _filename << "'." << endl;
    exit(1);
  }
}

Image::
~Image() {
  delete m_textureData;
}

unsigned int
Image::
initialize() {
  QImage texture = QGLWidget::convertToGLFormat(*m_textureData);

  //Bring into GLContext
  GLuint texID = 0;
  glGenTextures(1, &texID);
  glBindTexture(GL_TEXTURE_2D, texID);
  build2DMipmaps(GL_TEXTURE_2D, GL_RGBA, texture.width(), texture.height(),
      GL_RGBA, GL_UNSIGNED_BYTE, texture.bits());

  glBindTexture(GL_TEXTURE_2D, 0);

  // TODO Adapt for more recent open gl.
  //GLuint samplerIndex =
  //  glGetUniformLocation(_program, (name + ".m_texSampler").c_str());
  ////glUniform1f(samplerIndex, m_sampler);
  //glUniform1i(samplerIndex, m_id);

  return texID;
}
