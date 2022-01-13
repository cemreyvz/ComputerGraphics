#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO
{
public:
  // ID  of elements buffer object
  GLuint ID;

  // To create elements buffer object and linking it to indices
  EBO(GLuint* indices, GLsizeiptr size);

  // Bind EBO
  void Bind();

  // Unbind EBO
  void Unbind();

  // Delete EBO
  void Delete();
};

#endif