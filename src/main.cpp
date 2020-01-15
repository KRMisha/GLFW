#include <iostream>
#include <GLFW/glfw3.h>

namespace
{
    void errorCallback(int error, const char* description)
    {
        std::cerr << description << '\n';
    }

    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }
} // namespace

int main()
{
    glfwSetErrorCallback(errorCallback);

    if (!glfwInit())
    {
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Test", nullptr, nullptr);
    if (window == nullptr)
    {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, keyCallback);

    while (!glfwWindowShouldClose(window))
    {
        // Get window characteristics
        int width;
        int height;
        glfwGetFramebufferSize(window, &width, &height);
        float ratio = static_cast<float>(width) / height;

        // Set viewport and clear buffer
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        // Set projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.0, 1.0, 1.0, -1.0);

        // Set current matrix stack to modelview
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Draw triangle
        glRotatef(static_cast<float>(glfwGetTime()) * 50.0, 0.0, 0.0, 1.0);
        glBegin(GL_TRIANGLES);
        {
            glColor3f(1.0, 0.0, 0.0);
            glVertex3f(-0.6, -0.4, 0.0);
            glColor3f(0.0, 1.0, 0.0);
            glVertex3f(0.6, -0.4, 0.0);
            glColor3f(0.0, 0.0, 1.0);
            glVertex3f(0.0, 0.6, 0.0);
        }
        glEnd();

        // Swap buffers and poll window events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
}
