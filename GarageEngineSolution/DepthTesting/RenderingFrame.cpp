#include "RenderingFrame.h"
#include <cstdio>

RenderingFrame::RenderingFrame(const int& version_major, const int& version_minor, const int& width, const int& height, OnRenderingFrameInitialized initializeCallback, OnRenderingFrameLoop loopCallback)
	: window_width(width), window_height(height), onRenderFrameInitialized(initializeCallback), onRenderFrameLoop(loopCallback)
{
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3");
		return;
	}

	window = create_window(version_major, version_minor);

	if (!window) {
		fprintf(stderr, "ERROR, could not open window with GLFW3\n");
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	printf("Render %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	if (onRenderFrameInitialized) {
		onRenderFrameInitialized();
	}
}

void RenderingFrame::StartLoop()
{
	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (onRenderFrameLoop) {
			onRenderFrameLoop(window);
		}

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}

GLFWwindow* RenderingFrame::create_window(int version_major, int version_minor)
{
	// Change opengl version here
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version_major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version_minor);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Debugging output
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	// Enable Anti-aliasing
	glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Global Illumination Project", NULL, NULL);
	
	return window;
}

void RenderingFrame::glfw_window_resize_callback(GLFWwindow* window, int width, int height)
{
	window_width = width;
	window_height = height;
}

void RenderingFrame::glfw_window_framebuffer_callback(GLFWwindow* window, int width, int height)
{
	frame_buffer_height = height;
	frame_buffer_width = width;
}
