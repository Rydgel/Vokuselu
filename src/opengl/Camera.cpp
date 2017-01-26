#include "Camera.hpp"

Camera::Camera(EventDispatcher &eventDispatcher, glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch)
: m_eventDispatcher(eventDispatcher)
, m_front(glm::vec3(0.0f, 0.0f, -1.0f))
, m_movementSpeed(SPEED)
, m_mouseSensitivity(SENSITIVITY)
, m_zoom(ZOOM)
{
    m_position = position;
    m_worldUp = up;
    m_yaw = yaw;
    m_pitch = pitch;

    updateCameraVectors();
    setupEvents();
}

Camera::Camera(EventDispatcher &eventDispatcher, GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY,
               GLfloat upZ, GLfloat yaw, GLfloat pitch)
: m_eventDispatcher(eventDispatcher)
, m_front(glm::vec3(0.0f, 0.0f, -1.0f))
, m_movementSpeed(SPEED)
, m_mouseSensitivity(SENSITIVITY)
, m_zoom(ZOOM)
{
    m_position = glm::vec3(posX, posY, posZ);
    m_worldUp = glm::vec3(upX, upY, upZ);
    m_yaw = yaw;
    m_pitch = pitch;

    updateCameraVectors();
    setupEvents();
}

void Camera::updatePosition(const float dt)
{
    GLfloat velocity = m_movementSpeed * dt;
    if (m_keyStates[GLFW_KEY_W])
        m_position += m_front * velocity;
    if (m_keyStates[GLFW_KEY_S])
        m_position -= m_front * velocity;
    if (m_keyStates[GLFW_KEY_A])
        m_position -= m_right * velocity;
    if (m_keyStates[GLFW_KEY_D])
        m_position += m_right * velocity;
    if (m_keyStates[GLFW_KEY_SPACE])
        m_position.y += velocity;
    if (m_keyStates[GLFW_KEY_LEFT_CONTROL])
        m_position.y -= velocity;
}

void Camera::updatePitch(const float dt)
{

}

void Camera::updateZoom(const float dt)
{

}

void Camera::update(const float dt)
{
    updatePosition(dt);
    // Update Front, Right and Up Vectors using the updated Eular angles
    updateCameraVectors();
}

void Camera::processMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch)
{
    xoffset *= m_mouseSensitivity;
    yoffset *= m_mouseSensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch) {
        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;
    }
}

void Camera::setupEvents()
{
    m_keyStates[GLFW_KEY_W] = false;
    m_keyStates[GLFW_KEY_S] = false;
    m_keyStates[GLFW_KEY_A] = false;
    m_keyStates[GLFW_KEY_S] = false;

    m_sigConnectionKeyboard = m_eventDispatcher.subscribe(
            [this](KeyboardEvent e) {
                if(e.m_action == GLFW_PRESS)
                    m_keyStates[e.m_key] = true;
                else if(e.m_action == GLFW_RELEASE)
                    m_keyStates[e.m_key] = false;
            }
    );

    m_sigConnectionMousePos = m_eventDispatcher.subscribe(
            [this](MousePositionEvent e) {
                if (m_firstMouseMove) {
                    m_lastX = (float) e.m_xpos;
                    m_lastY = (float) e.m_ypos;
                    m_firstMouseMove = false;
                }

                GLfloat xoffset = (float) e.m_xpos - m_lastX;
                // Reversed since y-coordinates go from bottom to left
                GLfloat yoffset = m_lastY - (float) e.m_ypos;

                m_lastX = (float) e.m_xpos;
                m_lastY = (float) e.m_ypos;

                processMouseMovement(xoffset, yoffset);
            }
    );
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::updateCameraVectors()
{
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cosf(glm::radians(m_yaw)) * cosf(glm::radians(m_pitch));
    front.y = sinf(glm::radians(m_pitch));
    front.z = sinf(glm::radians(m_yaw)) * cosf(glm::radians(m_pitch));
    m_front = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    // Normalize the vectors, because their length gets closer to 0
    // the more you look up or down which results in slower movement.
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}

Camera::~Camera()
{
    // unbinds events
    m_sigConnectionKeyboard.disconnect();
    m_sigConnectionMousePos.disconnect();
    m_sigConnectionMouseScroll.disconnect();
}
