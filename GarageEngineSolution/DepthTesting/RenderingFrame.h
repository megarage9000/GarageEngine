#ifndef RENDERING_FRAME
#define RENDERING_FRAME


#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Window Size
#define WINDOW_WIDTH = 1280;
#define WINDOW_HEIGHT = 720;

// Frame Buffer Size
#define FRAME_BUFFER_WIDTH = 1080;
#define FRAME_BUFFER_HEIGHT = 720;

class RenderingFrame {

	using OnRenderingFrameInitialized = void(*)();
	using OnRenderingFrameLoop = void(*)(GLFWwindow*);

public:
	RenderingFrame(const int& version_major, const int& version_minor, const int& width, const int& height, OnRenderingFrameInitialized initializeCallback, OnRenderingFrameLoop loopCallback);
	void StartLoop();
	virtual ~RenderingFrame() = default;
	GLFWwindow* window;

private:
	int window_width;
	int window_height;

	OnRenderingFrameInitialized onRenderFrameInitialized;
	OnRenderingFrameLoop onRenderFrameLoop;

	int frame_buffer_width = 1080;
	int frame_buffer_height = 720;

	GLFWwindow* create_window(int version_major, int version_minor);
	void glfw_window_resize_callback(GLFWwindow* window, int width, int height);
	void glfw_window_framebuffer_callback(GLFWwindow* window, int width, int height);
};



#endif