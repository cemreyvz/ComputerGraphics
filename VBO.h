#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO
{
public:
  // ID of the vertex buffer object
  GLuint ID;
  // Generating a vertex buffer object and linking it to vertices
  VBO(GLfloat* vertices, GLsizeiptr size);

  // Bind VBO
  void Bind();
  // Unbind VBO
  void Unbind();
  // Delete VBO
  void Delete();
};

#endif
