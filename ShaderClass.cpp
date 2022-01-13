#include "ShaderClass.h"

// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
  std::ifstream in(filename, std::ios::binary);
  if (in) {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return (contents);
  }
  throw(errno);
}

//Shader program from 2 different shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
  // Read vertexFile and fragmentFile and store the strings
  std::string vertexCode = get_file_contents(vertexFile);
  std::string fragmentCode = get_file_contents(fragmentFile);

  // Convert the shader source strings into character arrays
  const char* vertexSource = vertexCode.c_str();
  const char* fragmentSource = fragmentCode.c_str();

  // Create vertex shader object, reference
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

  // Attach vertex shader source to the vertex shader object
  glShaderSource(vertexShader, 1, &vertexSource, NULL);

  // Compile the vertex shader into machine code
  glCompileShader(vertexShader);

  // Check shader compiation
  compileErrors(vertexShader, "VERTEX");

  // Create fragment shader object, reference
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  // Attach fragment shader source to the fragment shader object
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

  // Compile the vertex shader into machine code
  glCompileShader(fragmentShader);

  // Checks if shader compiled succesfully
  compileErrors(fragmentShader, "FRAGMENT");

  // Create shader program object, reference
  ID = glCreateProgram();

  // Attach to the shader program
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);

  // Link all the shaders together into the shader program
  glLinkProgram(ID);

  // Check shaders
  compileErrors(ID, "PROGRAM");

  // Delete 
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

// Activate Shader Program
void Shader::Activate()
{
  glUseProgram(ID);
}

// Delete Shader Program
void Shader::Delete()
{
  glDeleteProgram(ID);
}

// Shader compilation
void Shader::compileErrors(unsigned int shader, const char* type)
{
  // Stores status of compilation
  GLint hasCompiled;

  // Error message storage
  char infoLog[1024];
  if (type != "PROGRAM") {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
    if (hasCompiled == GL_FALSE) {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n"
                << infoLog << std::endl;
    }
  } else {
    glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
    if (hasCompiled == GL_FALSE) {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      std::cout << "SHADER_LINKING_ERROR for:" << type << "\n"
                << infoLog << std::endl;
    }
  }
}