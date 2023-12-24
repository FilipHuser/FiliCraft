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

FiliCraft::FiliCraft() : window(nullptr) , frameBuffer_width(-1) , frameBuffer_height(-1)
{
    this->cam = std::make_unique<Camera>();
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
    
    
    GLint vertexID = sl.loadShader("/Users/filiphuser/Desktop/FiliCraft/FiliCraft/Shaders/Lambert/LamVer.glsl" , GL_VERTEX_SHADER);
    
    GLint fragmentID = sl.loadShader("/Users/filiphuser/Desktop/FiliCraft/FiliCraft/Shaders/Lambert/LamFra.glsl" , GL_FRAGMENT_SHADER);
    ShaderProgram* b_sp = new ShaderProgram(vertexID , fragmentID);

    Mesh m = Mesh("/Users/filiphuser/Desktop/FiliCraft/FiliCraft/Models/cube.obj");
    Material matR(RED , 0.0);
    Material matG(GREEN , 0.0);
    
    DrawableObj cube(m , b_sp , matR);
    DrawableObj cube2(m , b_sp , matG);
    
    Observer* camObs = new CamObserver(b_sp);
    
    this->cam->attach(camObs);
    this->cam->notify(this->cam.get());
    
    
    
    glEnable(GL_DEPTH_TEST);
    
    double lastX = 0.0 , lastY = 0.0;
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            this->cam->moveLeft();
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            this->cam->moveRight();
        }
        
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            this->cam->moveForward();
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            this->cam->moveBack();
        }
        
        // Get the current mouse position
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        // Calculate the delta since the last update
        double deltaX = xpos - lastX;
        double deltaY = lastY - ypos; // Reversed since y-coordinates go from bottom to top

        // Update last mouse position
        lastX = xpos;
        lastY = ypos;
        
        this->cam->lookAround(-deltaX, -deltaY);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
        cube.display();
        cube2.display();
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
     glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
     glfwDestroyWindow(window);
     glfwTerminate();
     exit(EXIT_SUCCESS);
}
