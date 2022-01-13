#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format,
                 GLenum pixelType)
{
  // Assign the type of the texture
  type = texType;

  // Store the width, height, and the number of color channels of the image
  int widthImg, heightImg, numColCh;
  // Flip the image to the right position
  stbi_set_flip_vertically_on_load(true);
  // Reads the image from a file and stores it in bytes
  unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

  // Generates an OpenGL texture object
  glGenTextures(1, &ID);
  // Assigns the texture to a Texture Unit
  glActiveTexture(slot);
  glBindTexture(texType, ID);

  // Configure the type of algorithm that is used to make the image size 
  glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // Configure the way the texture repeating
  glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

  // Assigns the image to the OpenGL Texture object
  glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType,
               bytes);
  // Generates MipMaps
  glGenerateMipmap(texType);

  // Delete the image data 
  stbi_image_free(bytes);

  // Unbind the OpenGL Texture object 
  glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
  // Get the location of the uniform
  GLuint texUni = glGetUniformLocation(shader.ID, uniform);
  // Shader activation
  shader.Activate();
  // Set the value of the uniform
  glUniform1i(texUni, unit);
}

void Texture::Bind()
{
  glBindTexture(type, ID);
}

void Texture::Unbind()
{
  glBindTexture(type, 0);
}

void Texture::Delete()
{
  glDeleteTextures(1, &ID);
}