//
//  FiliCraft.cpp
//  FiliCraft
//
//  Created by Filip Huser on 07.12.2023.
//

#include "FiliCraft.hpp"

void print_info()
{
    // get version info
    printf("OpenGL Version: %s\n",glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);
}

void FiliCraft::GLFW_init()
{
    if (!glfwInit()) 
    {
       fprintf(stderr, "ERROR: could not start GLFW3\n");
       exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE,
    GLFW_OPENGL_CORE_PROFILE);
}

void FiliCraft::GLEW_init()
{
    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();
}

void FiliCraft::create_window(int width, int height, const char* title)
{
    this->window = glfwCreateWindow(width, height, title , NULL, NULL);
    
    if (!window)
    {
       glfwTerminate();
       exit(EXIT_FAILURE);
    }
    
    glfwGetFramebufferSize(window, &this->frameBuffer_width, &this->frameBuffer_height);
 
    glViewport(0, 0, this->frameBuffer_width, this->frameBuffer_height);
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
}

void FiliCraft::run()
{
    ShaderLoader sl;
    
    
    GLint vertexID = sl.loadShader("/Users/filiphuser/Desktop/FiliCraft/FiliCraft/Shaders/B_Shader/B_Vertex.glsl" , GL_VERTEX_SHADER);
    
    GLint fragmentID = sl.loadShader("/Users/filiphuser/Desktop/FiliCraft/FiliCraft/Shaders/B_Shader/B_Fragment.glsl" , GL_FRAGMENT_SHADER);
    ShaderProgram b_sp(vertexID , fragmentID);
    
    std::vector vertices = {
        -0.7f,  0.5f, 0.0f,  // Top Left
        -0.5f, -0.1f, 0.0f,  // Bottom Left
         0.5f, -0.4f, 0.0f,  // Bottom Right
         0.6f,  0.5f, 0.0f   // Top Right
    };
    
    Mesh m = Mesh(vertices , xyz , GL_TRIANGLE_FAN);
    
    DrawableObj triangle(m, b_sp);
    
    
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        triangle.display();
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

     glfwDestroyWindow(window);
     glfwTerminate();
     exit(EXIT_SUCCESS);
}
