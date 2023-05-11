#include <glad/glad.h>
#include <GLFW/glfw3.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3.lib")
#include <stdio.h>
#include <string.h>

const unsigned int WIN_W = 300;
const unsigned int WIN_H = 300;
const unsigned int WIN_X = 100;
const unsigned int WIN_Y = 100;

void refreshFunc(GLFWwindow* window) {
	printf("refresh called\n");
	fflush(stdout);
	glClear(GL_COLOR_BUFFER_BIT);
	glFinish();

	glfwSwapBuffers(window);
}
GLfloat color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

void colorPlusMinus(int plus, int index) {
	if (plus == 0) {
		color[index] += 0.1;
		if (color[index] >= 1.0f) color[index] = 1.0f;
	}
	else {
		color[index] -= 0.1;
		if (color[index] <= 0.0f) color[index] = 0.0f;
	}
}

void glClearColorByLocalColor() {
	glClearColor(color[0], color[1], color[2], color[3]);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	switch (key) {
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		break;

	case GLFW_KEY_Q:
		if (action == GLFW_PRESS) {
			colorPlusMinus(0, 0);
		}
		break;

	case GLFW_KEY_W:
		if (action == GLFW_PRESS) {
			colorPlusMinus(0, 1);
		}
		break;

	case GLFW_KEY_E:
		if (action == GLFW_PRESS) {
			colorPlusMinus(0, 2);
		}
		break;

	case GLFW_KEY_A:
		if (action == GLFW_PRESS) {
			colorPlusMinus(1, 0);
		}
		break;

	case GLFW_KEY_S:
		if (action == GLFW_PRESS) {
			colorPlusMinus(1, 1);
		}
		break;

	case GLFW_KEY_D:
		if (action == GLFW_PRESS) {
			colorPlusMinus(1, 2);
		}
		break;
	}
	glClearColorByLocalColor();
}

void mouseCallback(GLFWwindow* window, int button, int action, int mods) {
	switch (button) {
	case GLFW_MOUSE_BUTTON_LEFT:
		if (action == GLFW_PRESS) {
			printf("LEFT CLICK\n");
			fflush(stdout);
		}
	}
}

int main(int argc, char* argv[]) {
#if defined(_WIN32) || defined(_WIN64)
	char* win_name = (strrchr(argv[0], '\\') == NULL) ? argv[0] : (strrchr(argv[0], '\\') + 1);
#else // Unix, Linux, MacOS
	char* win_name = (strrchr(argv[0], '/') == NULL) ? argv[0] : (strrchr(argv[0], '/') + 1);
#endif
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(WIN_W, WIN_H, win_name, NULL, NULL);
	glfwSetWindowPos(window, WIN_X, WIN_Y);
	glfwMakeContextCurrent(window);
	glewInit();
	
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glfwSetWindowRefreshCallback(window, refreshFunc); 
	glfwSetKeyCallback(window, keyCallback);
	glfwSetMouseButtonCallback(window, mouseCallback);
	glClearColorByLocalColor();
	
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glFinish();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}