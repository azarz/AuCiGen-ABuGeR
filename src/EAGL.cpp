// Std. Includes
#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include <map>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Vec3.h"
#include "FrustumG.h"


// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include <SOIL/SOIL.h>


// ------------------------- EAGL PARAMETERS -------------------------------------------------------------------------
// Window dimensions, par défaut 1280 et 720
GLuint screenWidth = 1280, screenHeight = 720;

//Angles of the sun to change lightning color
//Default 3*M_PI/5 et 4*M_PI/3
GLfloat ANGLE_CREPUSC(3*M_PI/5);
GLfloat ANGLE_AUBE(4*M_PI/3);

//Length of the day/night cycle. Default 3600 secs : 30 min day 30 min night
GLint DUREE_CYCLE(3600);

//---------------- END OF PARAMETES -------------------------------------------------------------------------


int EAGL()
{
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "EAGL viewer for AuCiGen", nullptr, nullptr); // Windowed
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    // Define the viewport dimensions
    int width, height;
    // Fetching the window dimentions
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);
    glfwSwapInterval(1);     //Enabling VSync to save ressources


    // Enabling face culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);


    Shader shader("shaders/default.vertexshader", "shaders/default.fragmentshader");

    GLuint VAO;

    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Camera camera(glm::vec3(0.0f, 1.0f, 0.0f), window);


    // Optimisation for view frustrum culling (not used in AuCiGen)
    FrustumG frustum;
    frustum.setCamInternals(60.0f, (float)screenWidth/(float)screenHeight, 0.1f, 1000000.0f);


    // Loading the models
    Model roads("2_models/roads.obj", 10000.0f);
    Model envelops("2_models/building.obj", 10000.0f);
    Model parcels("2_models/parcels.obj", 10000.0f);

    // Main loop
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        camera.Do_Movement();
        // Switching the camera mode using the spacebar
        camera.Switch_Mode();

        // Updating the view frustrum
        frustum.setCamDef(Vec3(camera.Position.x, camera.Position.y, camera.Position.z),
                          Vec3(camera.Position.x + camera.Front.x ,camera.Position.y + camera.Front.y ,camera.Position.z + camera.Front.z),
                          Vec3(camera.Up.x, camera.Up.y, camera.Up.z));

        // Fetching the camera postion for specular light
        glUniform3f(glGetUniformLocation(shader.Program, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        // Fetching the shader variables
        GLint modelLoc = glGetUniformLocation(shader.Program, "model");

        glm::mat4 projection = glm::perspective(45.0f, (float)screenWidth/(float)screenHeight, 0.1f, 1000.0f);
        glm::mat4 view = camera.GetViewMatrix();


        glm::mat4 model;
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));


        glBindVertexArray(VAO);

        // Position and color of the sunlight
        GLint lightPos = glGetUniformLocation(shader.Program, "lightPos");
        GLint lightColor = glGetUniformLocation(shader.Program, "lightColor");
        GLint ambientStrength = glGetUniformLocation(shader.Program, "ambientStrength");
        GLint specularStrength = glGetUniformLocation(shader.Program, "specularStrength");
        GLfloat ambStr(0.05f);
        GLfloat specStr(0.3f);
        // Placed relatively to the camera
        glm::vec4 lPos(camera.Position.x, camera.Position.y + 300.0f, camera.Position.z, 1.0f);
        glm::vec3 lColor(1.0f, 1.0f, 1.0f);

        // Rotation of the sun
        glm::mat4 rot;
        GLfloat angle = glm::mod(2*M_PI*(glfwGetTime()/DUREE_CYCLE), 2*M_PI);
        rot = glm::rotate(rot, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        lPos = rot * lPos;

        glm::vec3 clearColor;
        // Defining the light colors and strength
        if (angle > ANGLE_CREPUSC && angle < ANGLE_AUBE){
            lColor = glm::vec3(0.0f, 0.0f, 0.05f);

            clearColor = glm::vec3(0.0f, 0.0f, 0.1f);

            ambStr = 0.05f;

        } else if (angle > M_PI/4 && angle < ANGLE_CREPUSC){
            double x = (ANGLE_CREPUSC - angle)/(ANGLE_CREPUSC - M_PI/4);

            lColor = glm::vec3(x * 1.0f, pow(x, 2) * 1.0f, pow(x, 4) * 1.0f + 0.05f);

            clearColor = glm::vec3((-2*pow(x,2) + 2*x) * 1.0f, pow(x, 2) * 0.5f, pow(x, 4) * 1.0f + 0.1f);

            ambStr = x * 0.65f + 0.05f;


        } else if (angle > ANGLE_AUBE && angle < 5*M_PI/3){
            double x = (ANGLE_AUBE - angle)/(ANGLE_AUBE - 5*M_PI/3);

            lColor = glm::vec3(pow(x,4) * 1.0f, pow(x, 2) * 1.0f, x * 1.0f + 0.05f);

            clearColor = glm::vec3((-2*pow(x,2) + 2*x) * 1.0f, pow(x, 2) * 0.5f, pow(x, 4) * 1.0f + 0.1f);
            ambStr = x * 0.65f + 0.05f;

        } else{
            lColor = glm::vec3(1.0f, 1.0f, 1.0f);

            clearColor = glm::vec3(0.0f, 0.5f, 1.0f);

            ambStr = 0.7f;
        }

        // Sky color
        glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);
        glUniform3f(lightPos, lPos.x, lPos.y, lPos.z);
        glUniform3f(lightColor, lColor.x, lColor.y , lColor.z);
        glUniform1f(ambientStrength, ambStr);
        glUniform1f(specularStrength, specStr);

        // Updating the shader variables
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


        //DRAWING THE OBJECTS

        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.007f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        roads.Draw(shader, frustum, 0.0f, 0.0f, 0.0f);
        envelops.Draw(shader, frustum, 0.0f, 0.0f, 0.0f);
        parcels.Draw(shader, frustum, 0.0f, 0.0f, 0.0f);

        glBindVertexArray(0);
        glfwSwapBuffers(window);
        }


    glfwTerminate();
    return 0;
}

