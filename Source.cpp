#include <iostream>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb.h"

#include "Camera.h"
#include "EBO.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "shaderClass.h"

const unsigned int width = 800;
const unsigned int height = 800;

// Vertices coordinates
GLfloat
  vertices[] = { //     COORDINATES     /        COLORS      /   TexCoord  //
    -0.5f, 0.0f,  0.5f,  0.83f, 0.70f, 0.44f, 0.0f,  0.0f,  -0.5f, 0.0f,
    -0.5f, 0.83f, 0.70f, 0.44f, 5.0f,  0.0f,  0.5f,  0.0f,  -0.5f, 0.83f,
    0.70f, 0.44f, 0.0f,  0.0f,  0.5f,  0.0f,  0.5f,  0.83f, 0.70f, 0.44f,
    5.0f,  0.0f,  0.0f,  0.8f,  0.0f,  0.92f, 0.86f, 0.76f, 2.5f,  5.0f
  };

// Indices for vertices order
GLuint indices[] = { 0, 1, 2, 0, 2, 3, 0, 1, 4, 1, 2, 4, 2, 3, 4, 3, 0, 4 };

int main()
{
  // Initialize GLFW
  glfwInit();

  // GLFW OPENGL connection
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a GLFWwindow object of 800 by 800 pixels
  GLFWwindow* window =
    glfwCreateWindow(width, height, "Homework 3", NULL, NULL);

  // Error check if the window fails to create
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  // Introduce the window into the current context
  glfwMakeContextCurrent(window);

  // Load GLAD so it configures OpenGL
  gladLoadGL();

  // Specify the viewport of OpenGL in the Window
  glViewport(0, 0, width, height);

  // Generates Shader object using shaders default.vert and default.frag
  Shader shaderProgram("default.vert", "default.frag");

  // Generates Vertex Array Object and binds it
  VAO VAO1;
  VAO1.Bind();

  // Generates Vertex Buffer Object and links it to vertices
  VBO VBO1(vertices, sizeof(vertices));

  // Generates Element Buffer Object and links it to indices
  EBO EBO1(indices, sizeof(indices));

  // Links VBO attributes such as coordinates and colors to VAO
  VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
  VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float),
                  (void*)(3 * sizeof(float)));
  VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float),
                  (void*)(6 * sizeof(float)));

  // Unbind all to prevent accidentally modifying them
  VAO1.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();



  Texture brickTex("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA,
  GL_UNSIGNED_BYTE); brickTex.texUnit(shaderProgram, "tex0", 0);

  // Enable the Depth Buffer
  glEnable(GL_DEPTH_TEST);

  // Create camera object
  Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

  // Main while loop
  while (!glfwWindowShouldClose(window)) {

    // Background color
    glClearColor(0, 0, 0, 1);

    // Clean the back buffer and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Tell OpenGL which shader program we want to use
    shaderProgram.Activate();

    // Handles camera inputs
    camera.Inputs(window);

    // Camera matrix to the vertex shader
    camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

    // Bind texture 
    brickTex.Bind();

    // Bind the VAO 
    VAO1.Bind();

    // Draw primitives
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int),
                   GL_UNSIGNED_INT, 0);

    // Swap the back buffer with the front buffer
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Delete all the objects we've created
  VAO1.Delete();
  VBO1.Delete();
  EBO1.Delete();
  brickTex.Delete();
  shaderProgram.Delete();

  // Delete window 
  glfwDestroyWindow(window);

  // Terminate GLFW 
  glfwTerminate();
  return 0;
}