#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include "stb.h"

#include "shaderClass.h"

class Texture
{
public:
  GLuint ID;
  GLenum type;
  Texture(const char* image, GLenum texType, GLenum slot, GLenum format,
          GLenum pixelType);

  // Assign a texture unit to a texture
  void texUnit(Shader& shader, const char* uniform, GLuint unit);
  // Bind texture
  void Bind();
  // Unbind texture
  void Unbind();
  // Delete texture
  void Delete();
};
#endif