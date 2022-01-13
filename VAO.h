#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>

#include "VBO.h"

class VAO
{
public:
  // ID for the vertex array object
  GLuint ID;
  // Generating VAO ID
  VAO();

  // Linking VBO attribute to VAO
  void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type,
                  GLsizeiptr stride, void* offset);
  // Bind VAO
  void Bind();
  // Unbind VAO
  void Unbind();
  // DeleteVAO
  void Delete();
};

#endif