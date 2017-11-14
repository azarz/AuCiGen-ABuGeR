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


// ------------------------- PARAMETRES DU PROGRAMME -------------------------------------------------------------------------
// Dimensions de la fenêtre, par défaut 1280 et 720
GLuint screenWidth = 1280, screenHeight = 720;

//Angles de la lumière à partir duquel on est en phase de crépuscule ou d'aube
//A priori, à ne pas changer, valeurs par défaut 3*M_PI/5 et 4*M_PI/3
GLfloat ANGLE_CREPUSC(3*M_PI/5);
GLfloat ANGLE_AUBE(4*M_PI/3);

//Durée du cycle jour/nuit. Par défaut 240 secondes : 2 min de jour, 2 min de nuit
GLint DUREE_CYCLE(3600);

//---------------- FIN DES PARAMETRES DU PROGRAMME -------------------------------------------------------------------------


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
    // On recupere les dimensions de la fenetre creee plus haut
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);
    glfwSwapInterval(1);     //Enabling VSync to save ressources


    //On active le face culling pour une meilleure performance (cela permet de ne pas afficher les faces non
    //visibles des polygones, et donc de ne pas faire les calculs coûteux de shader sur ces faces)
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);


    Shader shader("shaders/default.vertexshader", "shaders/default.fragmentshader");

    GLuint VAO;

    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Camera camera(glm::vec3(0.0f, 1.0f, 0.0f), window);


    //On initialise notre frustum (cône) (classe FrustumG du tutoriel du site lighthouse3D) pour réaliser du view frustum culling,
    //C'est à dire que l'on évite de faire le rendu des objets qui ne sont pas à l'écran. Cela améliore grandement la performance.
    FrustumG frustum;
    frustum.setCamInternals(60.0f, (float)screenWidth/(float)screenHeight, 0.1f, 1000000.0f);


    // On charge les modèles, avec le rayon de la sphère à tester pour le frustum culling
    // Si cette sphère est dans le cône de vison ou l'intersecte, on dessine l'objet
    Model roads("2_models/roads.obj", 10000.0f);
    Model envelops("2_models/building.obj", 10000.0f);
    Model parcels("2_models/parcels.obj", 10000.0f);

    // Boucle principale
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        camera.Do_Movement();
        //Fonction permettant de changer de mode de caméra, appelée si la barre espace est enfoncée
        camera.Switch_Mode();

        //Après le mouvement, on met à jour le cône de vision
        frustum.setCamDef(Vec3(camera.Position.x, camera.Position.y, camera.Position.z),
                          Vec3(camera.Position.x + camera.Front.x ,camera.Position.y + camera.Front.y ,camera.Position.z + camera.Front.z),
                          Vec3(camera.Up.x, camera.Up.y, camera.Up.z));

        //Récupération de la position de la vue, pour la lumière spéculaire
        glUniform3f(glGetUniformLocation(shader.Program, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        // On récupère les identifiants des variables globales du shader
        GLint modelLoc = glGetUniformLocation(shader.Program, "model");

        glm::mat4 projection = glm::perspective(45.0f, (float)screenWidth/(float)screenHeight, 0.1f, 1000.0f);
        glm::mat4 view = camera.GetViewMatrix();


        glm::mat4 model;
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));


        glBindVertexArray(VAO);

        // Position et couleur de la lumiere du soleil
        GLint lightPos = glGetUniformLocation(shader.Program, "lightPos");
        GLint lightColor = glGetUniformLocation(shader.Program, "lightColor");
        GLint ambientStrength = glGetUniformLocation(shader.Program, "ambientStrength");
        GLint specularStrength = glGetUniformLocation(shader.Program, "specularStrength");
        GLfloat ambStr(0.05f);
        GLfloat specStr(0.3f);
        //On la positionne en relatif par rapport à la caméra, afin qu'elle "suive" l'utilisateur
        glm::vec4 lPos(camera.Position.x, camera.Position.y + 300.0f, camera.Position.z, 1.0f);
        glm::vec3 lColor(1.0f, 1.0f, 1.0f);

        //Matrice de rotation du soleil autour de l'axe Z (les Z négatifs correspondent au nord)
        glm::mat4 rot;
        GLfloat angle = glm::mod(2*M_PI*(glfwGetTime()/DUREE_CYCLE), 2*M_PI);
        rot = glm::rotate(rot, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        lPos = rot * lPos;

        glm::vec3 clearColor;
        //Si le 'soleil' est en-dessous de l'horizon, il ne fait plus de lumière, il fait nuit
        //La lumière ambiante est faible et de couleur bleue foncée
        if (angle > ANGLE_CREPUSC && angle < ANGLE_AUBE){
            lColor = glm::vec3(0.0f, 0.0f, 0.05f);

            //Couleur du ciel de nuit
            clearColor = glm::vec3(0.0f, 0.0f, 0.1f);

            //Lumière ambiante faible
            ambStr = 0.05f;

        //Lumière crépusculaire, orangée et diminuant au fil du temps
        } else if (angle > M_PI/4 && angle < ANGLE_CREPUSC){
            //Variable x utilisée : vaut 1 au début du crépuscule, et 0 à la fin
            double x = (ANGLE_CREPUSC - angle)/(ANGLE_CREPUSC - M_PI/4);

            //Lumière orangée, le + 0.05f en B permet la continuité avec la nuit
            lColor = glm::vec3(x * 1.0f, pow(x, 2) * 1.0f, pow(x, 4) * 1.0f + 0.05f);

            //Couleur du 'ciel', le polynôme en x utilisé pour le calcul de R est construit de telle sorte que R(0) = R(1) = 0 et R(0.5) = 0.5
            //Le + 0.1f en B permet la continuité avec la nuit
            clearColor = glm::vec3((-2*pow(x,2) + 2*x) * 1.0f, pow(x, 2) * 0.5f, pow(x, 4) * 1.0f + 0.1f);

            //Lumière ambiante décroissante et continue, cohérente avec les valeurs de jour et de nuit
            ambStr = x * 0.65f + 0.05f;


        //Lueur de l'aube
        } else if (angle > ANGLE_AUBE && angle < 5*M_PI/3){
            //Variable x utilisée : vaut 0 au début de l'aube, et 1 à la fin
            double x = (ANGLE_AUBE - angle)/(ANGLE_AUBE - 5*M_PI/3);

            //Lueur rosée-bleutée, le + 0.05f en B permet la continuité avec la nuit
            lColor = glm::vec3(pow(x,4) * 1.0f, pow(x, 2) * 1.0f, x * 1.0f + 0.05f);

            //Couleur du 'ciel', le polynôme en x utilisé pour le calcul de R est construit de telle sorte que R(0) = R(1) = 0 et R(0.5) = 0.5
            //Le + 0.1f en B permet la continuité avec la nuit
            clearColor = glm::vec3((-2*pow(x,2) + 2*x) * 1.0f, pow(x, 2) * 0.5f, pow(x, 4) * 1.0f + 0.1f);

            //Lumière ambiante croissante et continue, cohérente avec les valeurs de jour et de nuit
            ambStr = x * 0.65f + 0.05f;


        //Lumière de jour
        } else{
            //Lumière blanche
            lColor = glm::vec3(1.0f, 1.0f, 1.0f);

            //Ciel bleu
            clearColor = glm::vec3(0.0f, 0.5f, 1.0f);

            //Lumière ambiante forte
            ambStr = 0.7f;
        }

        //On colore le ciel et on met à jour les variables globales
        glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);
        glUniform3f(lightPos, lPos.x, lPos.y, lPos.z);
        glUniform3f(lightColor, lColor.x, lColor.y , lColor.z);
        glUniform1f(ambientStrength, ambStr);
        glUniform1f(specularStrength, specStr);

        // On met a jour les variables globales du shader
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


        //DESSIN


        //Dessin des modeles 3d -------------------------------------
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.005f));
        // On remet a jour la variable globale du shader
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        // On redessine l’objet
        roads.Draw(shader, frustum, 0.0f, 0.0f, 0.0f);
        envelops.Draw(shader, frustum, 0.0f, 0.0f, 0.0f);
        parcels.Draw(shader, frustum, 0.0f, 0.0f, 0.0f);

        glBindVertexArray(0);
        glfwSwapBuffers(window);
        }


    glfwTerminate();
    return 0;
}


#pragma endregion
