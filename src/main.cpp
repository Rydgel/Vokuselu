#include "Game.hpp"
using namespace std;


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    // When a user presses the escape key, we set the WindowShouldClose property to true,
    // closing the application
    // could also use
    // glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main(int argc, char **argv) {
    Game game;
    game.gameLoop();
}