#include "EBO.h"

//To create elements buffer object and linking it to indices
EBO::EBO(GLuint* indices, GLsizeiptr size)
{
  glGenBuffers(1, &ID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

// Bind EBO
void EBO::Bind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Unbind EBO
void EBO::Unbind()
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Delete EBO
void EBO::Delete()
{
  glDeleteBuffers(1, &ID);
}