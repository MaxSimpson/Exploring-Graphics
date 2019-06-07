////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Wrappers to the GLU (GL Utility) library to avoid Qt/open GL include
///        conflict.
////////////////////////////////////////////////////////////////////////////////

#ifndef _GL_UTILITY_H_
#define _GL_UTILITY_H_

////////////////////////////////////////////////////////////////////////////////
/// @brief Wrapper to invoke gluBuild2DMipmaps
/// @param _target Target texture.
/// @param _internalFormat Internal format storage.
/// @param _width Width in pixels.
/// @param _height Height in pixels.
/// @param _format Format of pixel data.
/// @param _type Type of the data.
/// @param _data Data.
///
/// Note, cannot use GLenum, GLint, GLsizei because of Qt/open GL include
/// conflict.
void build2DMipmaps(int _target, int _internalFormat,
                    unsigned int _width, unsigned int _height,
                    int _format, int _type,
                    const void* _data);

#endif
