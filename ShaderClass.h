#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <cerrno>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <glad/glad.h>

std::string get_file_contents(const char* filename);

class Shader
{
public:
  //ID of the Shader Program
  GLuint ID;
  // Shader Program from 2 different shaders
  Shader(const char* vertexFile, const char* fragmentFile);

  // Activating the shader program
  void Activate();
  // Delete the shader program
  void Delete();

private:
  // Checking Shaders compilation 
  void compileErrors(unsigned int shader, const char* type);
};

#endif