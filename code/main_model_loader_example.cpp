//
//  main.cpp
//  HCI 557 Final Project
//
//  By Adam K, Fei X, and Jiazhong Z.
//

// stl include
#include <iostream>
#include <string>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


// glfw includes
#include <GLFW/glfw3.h>


// include local files
#include "controls.h"
#include "HCI557Common.h"
#include "CoordSystem.h"
#include "Sphere3D.h"


//#include "GLObjectObj.h"

#include "GLObjectObjFl.h"

using namespace std;


// The handle to the window object
GLFWwindow*         window;

// Define some of the global variables we're using for this sample
GLuint program;

float  target1[3];
float  time0;
// this flag is initialized as 0; once we update the tee(after each move animation);
// set it to 1, so that the update only happens onces.
int update_flag=0;


/* A trackball to move and rotate the camera view */
extern Trackball trackball;


void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if((key == GLFW_KEY_F5 && action == GLFW_PRESS) ) // key w
    {
        target1[0] =10.0;
        target1[1] =17.33;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
    }
    if((key == GLFW_KEY_5 && action == GLFW_PRESS) ) // key Q
    {
        target1[0] =7.5;
        target1[1] =13;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
    }
    if((key == GLFW_KEY_6 && action == GLFW_PRESS) ) // key w
    {
        target1[0] =12.5;
        target1[1] =13;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
    }
    if((key == GLFW_KEY_R && action == GLFW_PRESS) ) // key Q
    {
        target1[0] =5.0;
        target1[1] =8.66;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
    }
    if((key == GLFW_KEY_T && action == GLFW_PRESS) ) // key w
    {
        target1[0] =10.0;
        target1[1] =8.66;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
    }
    if((key == GLFW_KEY_Y && action == GLFW_PRESS) ) // key Q
    {
        target1[0] =15.0;
        target1[1] =8.66;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
    }
    if((key == GLFW_KEY_D && action == GLFW_PRESS) ) // key w
    {
        target1[0] =2.5;
        target1[1] =4.33;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
    }
    if((key == GLFW_KEY_F && action == GLFW_PRESS) ) // key Q
    {
        target1[0] =7.5;
        target1[1] =4.33;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
    }
    if((key == GLFW_KEY_G && action == GLFW_PRESS) ) // key w
    {
        target1[0] =12.5;
        target1[1] =4.33;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
    }
    if((key == GLFW_KEY_H && action == GLFW_PRESS) ) // key Q
    {
        target1[0] =17.5;
        target1[1] =4.33;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
    }
    if((key == GLFW_KEY_X && action == GLFW_PRESS) ) // key w
    {
        target1[0] =0.0;
        target1[1] =0.0;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
    }
    if((key == GLFW_KEY_C && action == GLFW_PRESS) ) // key Q
    {
        target1[0] =5.0;
        target1[1] =0.0;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
    }
    if((key == GLFW_KEY_V && action == GLFW_PRESS) ) // key w
    {
        target1[0] =10.0;
        target1[1] =0.0;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
    }
    if((key == GLFW_KEY_B && action == GLFW_PRESS) ) // key Q
    {
        target1[0] =15.0;
        target1[1] =0.0;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
    }
    if((key == GLFW_KEY_N && action == GLFW_PRESS) ) // key Q
    {
        target1[0] =20.0;
        target1[1] =0.0;
        target1[2] =0.0;
        time0 = glfwGetTime();
        update_flag=0;
    }
    
}

GLfloat* vector_diff = 0;
GLfloat* vector_result = 0;

/*!
 @brief returns the time fraction for a given time and animation duration
 @param time - the current animation time, application runtime, etc. in seconds
 @param duration - the duration of the animation in seconds
 @return the time fraction in an interval between 0 and 1.
 */
float getTimeFraction(const float time, const float time0, const float duration)
{
    // we calculate the time difference
    float diff = time - time0;
    
    // return the fraction / position in our current timeline, with respect to the duration
    float fraction = diff / duration;
    //
    return fraction;
}



/*!
 This initializes the difference vector for the morphing operation
 */
void init_morphing(GLObjectObjFl* lm1, float xn, float yn,float zn)
{
    // allocate memory for the difference vector.
    vector_diff = (GLfloat*)malloc(sizeof(GLfloat) * 3 * lm1->size());
    
    int size = lm1->size();
    // calculate the difference vector
    for (int i=0; i<size; i++) {
        vector_diff[i*3+0] = xn - lm1->center[0];
        vector_diff[i*3+1] = yn - lm1->center[1];
        vector_diff[i*3+2] = zn - lm1->center[2];
    }
    
}


/*!
 This function processes the morphing operation
 */
void my_morphing_callback(float duration, float time0, GLObjectObjFl* lm1, float xn, float yn,float zn)
{
    // get the current system time
    float time = glfwGetTime();
    
    // calcualte the time fraction
    float fraction = getTimeFraction(time, time0, duration);
    
    // get the number of vertices.
    int size = lm1->size();
    
    // init the vector the first time we call this function.
    if(vector_result == NULL)
    {
        vector_result = (GLfloat*)malloc(sizeof(GLfloat) * 3 * lm1->size());
    }
    float factor1 = 50.0;
    if (vector_diff[0] == 0.0 and vector_diff[1] == 0.0)
    {
        factor1 = 0.0;
    }
    
    float dx = xn-lm1->center[0];
    float dy = yn-lm1->center[1];
    float dz = zn-lm1->center[2];
    
    //    if (fraction <= 1.0)
    //    {
    //        cout<< fraction<<endl;
    //    }
    if (fraction >= 1.0 and update_flag==0)
    {
        
        // change the update flag so that we only update once
        update_flag = 1;
        // update the center and vertices, to where it should be
        lm1->updatecenter(dx,dy,dz);
        
        //        lm1->draw();
    }
    
    if (fraction <=1.0 )
    {
        for (int i=0; i<size; i++) {
            vector_result[i*3+0] = lm1->getVertices()[i].x + fraction * vector_diff[i*3+0];
            vector_result[i*3+1] = lm1->getVertices()[i].y + fraction * vector_diff[i*3+1];
            vector_result[i*3+2] = lm1->getVertices()[i].z + fraction * (1.0f-fraction) * factor1;
        }
    }
    else
    {
        for (int i=0; i<size; i++) {
            vector_result[i*3+0] = lm1->getVertices()[i].x;
            vector_result[i*3+1] = lm1->getVertices()[i].y;
            vector_result[i*3+2] = lm1->getVertices()[i].z;
        }
    }
    
    //---------------------------
    // Draw the output
    
    lm1->updateVertices(vector_result);
}



int main(int argc, const char * argv[])
{
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Init glfw, create a window, and init glew
    
    // Init the GLFW Window
    window = initWindow();
    
    
    // Init the glew api
    initGlew();
    SetCameraManipulator(CameraTypes::CAMERA_MANIPULATOR);
    
    target1[0] = 12.5;
    target1[1] = 4.33;
    target1[2] = 0.0;
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Create some models
    
    // coordinate system
    CoordSystem* cs = new CoordSystem(1000.0);
    
    
    // create an apperance object.
    GLAppearance* apperance_0 = new GLAppearance("../../data/shaders/multi_vertex_lights_ext.vs", "../../data/shaders/multi_vertex_lights_ext.fs");
    
    GLDirectLightSource  light_source;
    light_source._lightPos = glm::vec4(10.0, 10.0, 30.0, 0.0);
    light_source._ambient_intensity = 0.05;
    light_source._specular_intensity = 15.5;
    light_source._diffuse_intensity = 2.0;
    light_source._attenuation_coeff = 0.0;
    
    // add the light to this apperance object
    apperance_0->addLightSource(light_source);
    
    // Create a material object
    GLMaterial material_0;
    material_0._diffuse_material = glm::vec3(1.0, 0.0, 0.0);
    material_0._ambient_material = glm::vec3(1.0, 0.0, 0.0);
    material_0._specular_material = glm::vec3(0.0, 0.0, 0.0);
    material_0._shininess = 1.0;
    material_0._transparency = 1.0;
    
    // Add the material to the apperance object
    apperance_0->setMaterial(material_0);
    apperance_0->finalize();
    
    // create an apperance object.
    GLAppearance* apperance_1 = new GLAppearance("../../data/shaders/multi_vertex_lights_ext.vs", "../../data/shaders/multi_vertex_lights_ext.fs");
    
    GLDirectLightSource  light_source1;
    light_source1._lightPos = glm::vec4(10.0, 10.0, 10.0, 0.0);
    light_source1._ambient_intensity = 0.05;
    light_source1._specular_intensity = 15.5;
    light_source1._diffuse_intensity = 2.0;
    light_source1._attenuation_coeff = 0.0;
    
    // add the light to this apperance object
    apperance_1->addLightSource(light_source);
    
    // Create a material object
    GLMaterial material_1;
    material_1._diffuse_material = glm::vec3(0.0, 1.0, 0.0);
    material_1._ambient_material = glm::vec3(0.0, 1.0, 0.0);
    material_1._specular_material = glm::vec3(0.0, 0.0, 0.0);
    material_1._shininess = 1.0;
    material_1._transparency = 1.0;
    
    // Add the material to the apperance object
    apperance_1->setMaterial(material_1);
    apperance_1->finalize();
    
    // create an apperance object.
    GLAppearance* apperance_2 = new GLAppearance("../../data/shaders/multi_vertex_lights_ext.vs", "../../data/shaders/multi_vertex_lights_ext.fs");
    
    apperance_2->addLightSource(light_source);
    
    GLMaterial material_2;
    material_2._diffuse_material = glm::vec3(0.0, 0.0, 1.0);
    material_2._ambient_material = glm::vec3(0.0, 0.0, 1.0);
    material_2._specular_material = glm::vec3(0.0, 0.0, 0.0);
    material_2._shininess = 1.0;
    material_2._transparency = 1.0;
    
    // Add the material to the apperance object
    apperance_2->setMaterial(material_2);
    apperance_2->finalize();
    
    // create an apperance object.
    GLAppearance* apperance_3 = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");
    
    apperance_3->addLightSource(light_source1);
    
    GLMaterial material_3;
    material_3._diffuse_material = glm::vec3(1.0, 1.0, 1.0);
    material_3._ambient_material = glm::vec3(1.0, 1.0, 1.0);
    material_3._specular_material = glm::vec3(0.0, 0.0, 0.0);
    material_3._shininess = 1.0;
    material_3._transparency = 1.0;
    
    // Add the material to the apperance object
    apperance_3->setMaterial(material_3);
    apperance_3->finalize();
    
    // If you want to change appearance parameters after you init the object, call the update function
    apperance_0->updateLightSources();
    apperance_1->updateLightSources();
    apperance_2->updateLightSources();
    apperance_3->updateLightSources();
    
    
    GLObjectObjFl* tee1 = new GLObjectObjFl("../../data/Tee.obj", 0.0, 0.0, 0.0);
    tee1->setApperance(*apperance_0);
    tee1->init();
    
    GLObjectObjFl* tee2 = new GLObjectObjFl("../../data/Tee.obj", 5.0, 0.0, 0.0);
    tee2->setApperance(*apperance_0);
    tee2->init();
    
    GLObjectObjFl* tee3 = new GLObjectObjFl("../../data/Tee.obj", 10.0, 0.0, 0.0);
    tee3->setApperance(*apperance_0);
    tee3->init();
    
    GLObjectObjFl* tee4 = new GLObjectObjFl("../../data/Tee.obj", 15.0, 0.0, 0.0);
    tee4->setApperance(*apperance_0);
    tee4->init();
    
    GLObjectObjFl* tee5 = new GLObjectObjFl("../../data/Tee.obj", 20.0, 0.0, 0.0);
    tee5->setApperance(*apperance_1);
    tee5->init();
    
    GLObjectObjFl* tee6 = new GLObjectObjFl("../../data/Tee.obj", 2.5, 4.33, 0.0);
    tee6->setApperance(*apperance_1);
    tee6->init();
    
    GLObjectObjFl* tee7 = new GLObjectObjFl("../../data/Tee.obj", 7.5, 4.33, 0.0);
    tee7->setApperance(*apperance_1);
    tee7->init();
    
    GLObjectObjFl* tee8 = new GLObjectObjFl("../../data/Tee.obj", 12.5, 4.33, 0.0);
    tee8->setApperance(*apperance_2);
    tee8->init();
    
    GLObjectObjFl* tee9 = new GLObjectObjFl("../../data/Tee.obj", 17.5, 4.33, 0.0);
    tee9->setApperance(*apperance_1);
    tee9->init();
    
    
    GLObjectObjFl* tee10 = new GLObjectObjFl("../../data/Tee.obj", 5.0, 8.66, 0.0);
    tee10->setApperance(*apperance_0);
    tee10->init();
    
    GLObjectObjFl* tee11 = new GLObjectObjFl("../../data/Tee.obj", 10.0, 8.66, 0.0);
    tee11->setApperance(*apperance_2);
    tee11->init();
    
    GLObjectObjFl* tee12 = new GLObjectObjFl("../../data/Tee.obj", 15.0, 8.66, 0.0);
    tee12->setApperance(*apperance_2);
    tee12->init();
    
    GLObjectObjFl* tee13 = new GLObjectObjFl("../../data/Tee.obj", 7.5, 12.99, 0.0);
    tee13->setApperance(*apperance_2);
    tee13->init();
    
    GLObjectObjFl* tee14 = new GLObjectObjFl("../../data/Tee.obj", 12.5, 12.99, 0.0);
    tee14->setApperance(*apperance_0);
    tee14->init();
    
    GLObjectObjFl* tee15 = new GLObjectObjFl("../../data/Tee.obj", 10.0, 17.32, 0.0);
    tee15->setApperance(*apperance_1);
    tee15->init();
    
    GLObjectObjFl* pad = new GLObjectObjFl("../../data/pad.obj", 0.0, 0.0, 0.0);
    pad->setApperance(*apperance_3);
    pad->init();
    
    
    glm::mat4 tranform = glm::translate(glm::vec3(-10.0f, -5.7737f, 0.0f)) * glm::scale(glm::vec3(1.0, 1.0f, 1.0f)) ;
    glm::mat4 tranform1 = glm::scale(glm::vec3(0.1, 0.1f, 0.1f));
    tee1->setMatrix(tranform);
    tee2->setMatrix(tranform);
    tee3->setMatrix(tranform);
    tee4->setMatrix(tranform);
    tee5->setMatrix(tranform);
    tee6->setMatrix(tranform);
    tee7->setMatrix(tranform);
    tee8->setMatrix(tranform);
    tee9->setMatrix(tranform);
    tee10->setMatrix(tranform);
    tee11->setMatrix(tranform);
    tee12->setMatrix(tranform);
    tee13->setMatrix(tranform);
    tee14->setMatrix(tranform);
    tee15->setMatrix(tranform);
    
    pad->setMatrix(tranform);

    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Main render loop
    
    // Set up our green background color
    static const GLfloat clear_color[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    // This sets the camera to a new location
    // the first parameter is the eye position, the second the center location, and the third the up vector.
    SetViewAsLookAt(glm::vec3(20.0f, 20.0f, 45.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    
    
    // Enable depth test
    // ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
    glEnable(GL_DEPTH_TEST);
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Blending
    
    // Enable blending
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwSetKeyCallback(window, keyboard_callback);
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Main render loop
    double lastTime = glfwGetTime();
    int nbFrames = 0;
    
    // Fei's Work
    init_morphing(tee8,target1[0],target1[1],target1[2]);
    
    // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
    while(!glfwWindowShouldClose(window))
    {
        
        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR , 0, clear_color);
        glClearBufferfv(GL_DEPTH , 0, clear_depth);
        
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// This renders the objects
        
        // Set the trackball locatiom
        SetTrackballLocation(GetCurrentCameraMatrix(), GetCurrentCameraTranslation());
        
        // draw the objects
        cs->draw();
  
       
        
        my_morphing_callback(1.0, time0, tee8,target1[0],target1[1],target1[2]);
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// This renders the objects
        //        cout <<tee8->center[0]<<endl;
        // Set the trackball locatiom
        //        SetTrackballLocation(GetCurrentCameraMatrix(), GetCurrentCameraTranslation());
        SetTrackballLocation(GetCurrentCameraMatrix(),GetCurrentCameraTranslation());
        // draw the objects
        //        cs->draw();
        
        tee1->draw();
        
        tee2->draw();
        tee3->draw();
        tee4->draw();
        tee5->draw();
        tee6->draw();
        tee7->draw();
        
        tee8->draw();
        tee9->draw();
        tee10->draw();
        tee11->draw();
        tee12->draw();
        
        //                tee13->draw();
        tee14->draw();
        tee15->draw();
        
////
        //pad->draw();
        
        
        //// This renders the objects
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        
        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        //Calculate frame rate
        double currentTime = glfwGetTime();
        nbFrames++;
        if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
            // printf and reset timer
                printf("%f ms/frame\n", 1000.0/double(nbFrames));
                nbFrames = 0;
                lastTime += 1.0;
            }
    }
    
    
    delete cs;
    
    
}

