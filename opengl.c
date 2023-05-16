#include <Windows.h>
#include <mmsystem.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib,"winmm.lib")
#pragma warning(disable: 4711 4710 4100)
#include <stdio.h>
#include <string.h>

#include "./common.c"

const unsigned int WIN_W = 300;
const unsigned int WIN_H = 300;
const unsigned int WIN_X = 100;
const unsigned int WIN_Y = 100;

GLfloat color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

void colorPlusMinus(int plus, int index) {
	if (plus == 0) {
		color[index] += 0.1f;
		if (color[index] >= 1.0f) color[index] = 1.0f;
	}
	else {
		color[index] -= 0.1f;
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
const char* vertSource =
"#version 330 core \n\
in vec4 vertexPos;\n\
void main(void) {\n\
	gl_Position=vertexPos;\n\
}";

const char* fragSource =
"#version 330 core \n\
out vec4 FragColor;\n\
void main(void) {\n\
	FragColor=vec4(1.0, 0.0, 0.0, 1.0);\n\
}";

GLuint vert = 0;
GLuint frag = 0;
GLuint prog = 0;

void initFunc(void) {
	vert = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert, 1, &vertSource, NULL);
	glCompileShader(vert);

	frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag, 1, &fragSource, NULL);
	glCompileShader(frag);

	prog = glCreateProgram();
	glAttachShader(prog, vert);
	glAttachShader(prog, frag);
	glLinkProgram(prog);

	glUseProgram(prog);
}

GLfloat vertPos[] = {
	-0.5F, -0.5F, 0.0F, 1.0F,
	+0.5F, -0.5F, 0.0F, 1.0F,
	-0.5F, +0.5F, 0.0F, 1.0F,
};

void drawFunc(void) {
	// clear in gray color
	glClear(GL_COLOR_BUFFER_BIT);
	// provide the vertex attributes
	GLuint loc = glGetAttribLocation(prog, "vertexPos");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0, vertPos);
	// draw a triangle
	glDrawArrays(GL_TRIANGLES, 0, 3);
	// done
	glFinish();
}

void refreshFunc(GLFWwindow* window) {
	// refresh
	drawFunc();
	// GLFW action
	glfwSwapBuffers(window);
}

int main(int argc, char* argv[]) {
	const char* basename = getBaseName(argv[0]);
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(WIN_W, WIN_H, basename, NULL, NULL);
	glfwSetWindowPos(window, WIN_X, WIN_Y);
	glfwMakeContextCurrent(window);
	glewInit();
	
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glfwSetWindowRefreshCallback(window, refreshFunc); 
	glfwSetKeyCallback(window, keyCallback);
	glfwSetMouseButtonCallback(window, mouseCallback);
	glClearColorByLocalColor();

	initFunc();
	//PlaySound(TEXT("https://ia601602.us.archive.org/3/items/tadupd04/tadupd04.wav"), NULL, SND_ASYNC);
	
	while (!glfwWindowShouldClose(window)) {
		// draw
		drawFunc();
		// GLFW actions
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}