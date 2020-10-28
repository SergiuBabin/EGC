#include <iostream>
#include <string.h>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <defines/errors.hpp>

#define RADIANS(angle)		(angle * 0.0174532925194444f)

/* Window dimensions */
const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = 3.14159265f / 180.0f;

GLuint VAO, VBO, IBO, shader;
GLint uniformModel, uniformProjection;

bool direction = true, sizeDirection = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.005f;

float curAngle = 0.0f;
float curSize = 0.4f;
float maxSize = 0.8f;
float minSize = 0.1f;

/* Vertex shader */
static const char* vShader = "                   \n\
#version 330                                     \n\
                                                 \n\
layout (location = 0) in vec3 pos;               \n\
out vec4 vColor;                                 \n\
                                                 \n\
uniform mat4 model;                              \n\
uniform mat4 projection;                         \n\
void main()                                      \n\
{                                                \n\
    gl_Position = projection * model * vec4(pos, 1.0);        \n\
    vColor = vec4(clamp(gl_Position, 0.0f, 1.0f));            \n\
}                                                             \n\
";

/* Fragment shader */
static const char* fShader = "                   \n\
#version 330                                     \n\
                                                 \n\
in vec4 vColor;                                  \n\
out vec4 color;                                  \n\
void main()                                      \n\
{                                                \n\
    color = vColor;                              \n\
}                                                \n\
";


void create_triangle()
{
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }
}

void add_shader(GLuint the_program, const char* shader_code, GLenum shader_type)
{
    GLuint the_shader = glCreateShader(shader_type);

    const GLchar* the_code[1];
    the_code[0] = shader_code;

    GLint code_length[1];
    code_length[0] = strlen(shader_code);

    glShaderSource(the_shader, 1, the_code, code_length);
    glCompileShader(the_shader);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glGetShaderiv(the_shader, GL_COMPILE_STATUS, &result);

    if (!result) {
        glGetShaderInfoLog(the_shader, sizeof(eLog), NULL, eLog);
        std::cout << "Error compiling shader:" << eLog << "\n";

        return;
    }

    glAttachShader(the_program, the_shader);
}

void compile_shaders()
{
    shader = glCreateProgram();

    if (!shader) {
        std::cout << "Error creating shader program.\n";
        return;
    }

    add_shader(shader, vShader, GL_VERTEX_SHADER);
    add_shader(shader, fShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);

    if (!result) {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        std::cout << "Error linking program:" << eLog << "\n";

        return;
    }

    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);

    if (!result) {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        std::cout << "Error validating program:" << eLog << "\n";

        return;
    }

    uniformModel = glGetUniformLocation(shader, "model");
    uniformProjection = glGetUniformLocation(shader, "projection");
}

int main()
{
    float i = 0.0f;
    glm::mat4 model = glm::mat4(1.0f), projection;
    /* Initialize GLFW */
    if (!glfwInit()) {
        std::cout << "Initialization failed.\n";
        glfwTerminate();

        return GLFW_INIT_ERROR;
    }

    /* Setup GLFW window properties */
    /* OpenGL version */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    /* Core profile = No backwords compatibility */
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Allow forward compatibility*/
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Lab", NULL, NULL);

    if (!mainWindow) {
        std::cout << "GLFW window creation failed.\n";
        glfwTerminate();

        return GLFW_WIND_ERROR;
    }

    /* Get buffer size information */
    int bufferWidth, bufferHeight;

    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    /* Set context for GLEW to use */
    glfwMakeContextCurrent(mainWindow);

    /* Allow modern extension features */
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW initialization failed.\n";
        glfwDestroyWindow(mainWindow);
        glfwTerminate();

        return GLEW_INIT_ERROR;
    }

    /* Setup Viewport size */
    glViewport(0, 0, bufferWidth, bufferHeight);

    glEnable(GL_DEPTH_TEST);

    create_triangle();
    compile_shaders();

    projection = glm::perspective(45.0f, (GLfloat) bufferWidth/(GLfloat)bufferHeight, 0.1f, 100.0f);

    /* Loop until window closed */
    while (!glfwWindowShouldClose(mainWindow)) {
        i += 0.05f;
        /* Get and handle user input events */
        glfwPollEvents();

        if (direction) {
            triOffset += triIncrement;
        } else {
            triOffset -= triIncrement;

        }
        
        if (abs(triOffset) >= triMaxOffset) {
            direction = !direction;
        }

        curAngle += 5.0f;

        if (i >= 1.0f)
            i = 0.05f;
        
        if (curAngle >= 360)
            curAngle -= 360;

        if (sizeDirection)
            curSize += 0.01f;
        else
            curSize -= 0.01f;
    
        if (curSize >= maxSize || curSize <= minSize)
            sizeDirection = !sizeDirection;

        /* Clear the window */
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(triOffset, 0.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 1.0f));
        model = glm::rotate(model, RADIANS(curAngle), glm::vec3(0.0f, i, 0.0f));

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        

        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glUseProgram(0);

        glfwSwapBuffers(mainWindow);
    }

    return 0;
}