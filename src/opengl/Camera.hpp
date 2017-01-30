#ifndef VOXELS_CAMERA_HPP
#define VOXELS_CAMERA_HPP

#include <unordered_map>
#include <vector>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../EventDispatcher.hpp"


// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 6.0f;
const GLfloat SENSITIVITY = 0.25f;
const GLfloat ZOOM = 45.0f;

class Camera
{
private:
    bool m_firstMouseMove = true;
    GLfloat m_lastX = 400, m_lastY = 300;
    std::unordered_map<int, bool> m_keyStates;

    // Events handling
    EventDispatcher &m_eventDispatcher;
    boost::signals2::connection m_sigConnectionKeyboard;
    boost::signals2::connection m_sigConnectionMousePos;
    boost::signals2::connection m_sigConnectionMouseScroll;

    // Calculates the front vector from the Camera's (updated) Eular Angles
    void updateCameraVectors();
    void updatePosition(const float dt);
    void updatePitch(const float dt);
    void updateZoom(const float dt);
public:
    // Camera Attributes
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;
    // Eular Angles
    GLfloat m_yaw;
    GLfloat m_pitch;
    // Camera options
    GLfloat m_movementSpeed;
    GLfloat m_mouseSensitivity;
    GLfloat m_zoom;


    Camera(EventDispatcher &eventDispatcher, glm::vec3 position = glm::vec3(0.0f, 60.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);
    Camera(EventDispatcher &eventDispatcher, GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY,
           GLfloat upZ, GLfloat yaw, GLfloat pitch);
    void update(const float dt);
    void processMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = (GLboolean) true);
    void setupEvents();
    glm::mat4 getViewMatrix();
    ~Camera();
};


#endif //VOXELS_CAMERA_HPP
