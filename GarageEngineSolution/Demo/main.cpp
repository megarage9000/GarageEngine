#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GarageShaders.h"
#include "Model.h"
#include "GarageEngineObject.h"
#include "DebugOutput.h"

// Window Size
int WINDOW_WIDTH = 1280;
int WINDOW_HEIGHT = 720;

// Frame Buffer Size
int FRAME_BUFFER_WIDTH = 1080;
int FRAME_BUFFER_HEIGHT = 720;

// Time
double previous_time = 0.0f;
double elapsed_seconds = 0.0f;

// Movement parameters
float camera_rotation_sensitivity = 10.0f;
float camera_movement_speed = 10.0f;
float prev_mouse_y_pos = 0.0f;
float prev_mouse_x_pos = 0.0f;

// Toggle mouse locks
bool mouse_lock = false;

#pragma region Callbacks
void glfw_window_resize_callback(GLFWwindow* window, int width, int height);
void glfw_window_framebuffer_callback(GLFWwindow* window, int width, int height);
#pragma endregion

#pragma region Camera Object
GarageEngine::CameraObject cameraObject = GarageEngine::CameraObject{ Vec3 {0.0f, 0.0f, 0.0f}, Versor {0.0f, 0.0f, 0.0f, 0.0f} };
#pragma endregion

#pragma region Function declarations
GLFWwindow* create_window(int version_major, int version_minor);
void setup_debug();
Mat4 set_up_projection_matrix();
void input_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void input_continuous_callback(GLFWwindow* window);
void mouse_input_callback(GLFWwindow* window, double xpos, double ypos);
void toggle_mouse_lock(GLFWwindow* window);
#pragma endregion

int main() {	

	if (!restart_gl_log()) {
		return -1;
	}

	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3");
		return -1;
	}

	GLFWwindow* window = create_window(3, 2);

	if (!window) {
		fprintf(stderr, "ERROR, could not open window with GLFW3\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();

	setup_debug();

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	printf("Render %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	// Define Shader here
	Shader MeshShader = Shader(
		"mesh.vert", 
		"mesh.frag");

	// Define Model here
	Model model{ "..\\testMeshes\\backpack\\backpack.obj", &MeshShader };

	// Define positions and models here
	vector<GarageEngine::RenderableObject> renderableObjects;

	for (int i = 0; i < 10; i++) {
		GarageEngine::EngineObject transform{ Vec3 {-10.0f + (i * 2), 0.0f, 0.0f}, Versor {0.0f, 0.0f, 0.0f, 0.0f}};
		GarageEngine::RenderableObject renderable{ transform, &model, &MeshShader };
		renderableObjects.push_back(renderable);
	}


	// Define projection matrix
	Mat4 projection = set_up_projection_matrix();

	// Input handle
	glfwSetKeyCallback(window, input_callback);
	glfwSetCursorPosCallback(window, mouse_input_callback);

	// TODO: Add transforms and such:

	previous_time = glfwGetTime();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		input_continuous_callback(window);

		double current_time = glfwGetTime();
		elapsed_seconds = current_time - previous_time;
		previous_time = current_time;
		
		for (GarageEngine::RenderableObject& renderable : renderableObjects) {

			// renderable.engine_object.ApplyTranslation(Vec3{ 0.0f, 1.0f * (float)elapsed_seconds, 0.0f });
			renderable.Update(cameraObject, projection);
		}

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}

void setup_debug() {
	
	// Grabbing GL bits and checking if debugging is enabled
	int flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
		std::cout << "Enabling Debug" << std::endl;
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}
}

GLFWwindow* create_window(int version_major, int version_minor) {
	// Change opengl version here
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version_major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version_minor);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Debugging output
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	// Enable Anti-aliasing
	glfwWindowHint(GLFW_SAMPLES, 4);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Demo Window", NULL, NULL);

	glfwSetWindowSizeCallback(window, glfw_window_resize_callback);
	glfwSetFramebufferSizeCallback(window, glfw_window_framebuffer_callback);

	return window;
}

void glfw_window_resize_callback(GLFWwindow* window, int width, int height) {
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;
}

void glfw_window_framebuffer_callback(GLFWwindow* window, int width, int height) {
	FRAME_BUFFER_WIDTH = width;
	FRAME_BUFFER_HEIGHT = height;
}

Mat4 set_up_projection_matrix() {
	float near = 0.1f;
	float far = 100.0f;
	float fov = 67.0f * DEG_TO_RAD;
	float aspect = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
	Mat4 perspective = projection_matrix(near, far, fov, aspect);
	return perspective;
}

void input_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {

		switch (key) {

			// Toggle Cursor Hide
			case GLFW_KEY_1:
				toggle_mouse_lock(window);
				break;
		}
	}
}

void input_continuous_callback(GLFWwindow* window)
{
	Vec3 translationChanges{ 0.0f, 0.0f, 0.0f };

	// Movement
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		translationChanges[2] += 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		translationChanges[2] += -1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		translationChanges[0] += 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		translationChanges[0] += -1.0f;
	}

	// Up and Down
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		translationChanges[1] += 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		translationChanges[1] += -1.0f;
	}
	
	cameraObject.ApplyTranslation(translationChanges * 5.0f * elapsed_seconds);
}

void mouse_input_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (mouse_lock) {
		float pitch = -(ypos - prev_mouse_y_pos) * camera_rotation_sensitivity * elapsed_seconds;
		float yaw = -(xpos - prev_mouse_x_pos) * camera_rotation_sensitivity * elapsed_seconds;

		cameraObject.RealignGaze(yaw, pitch);
		prev_mouse_x_pos = xpos;
		prev_mouse_y_pos = ypos;
	}
}

void toggle_mouse_lock(GLFWwindow * window)
{
	mouse_lock = !mouse_lock;

	if (mouse_lock) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	double x_pos, y_pos;
	glfwGetCursorPos(window, &x_pos, &y_pos);
	prev_mouse_x_pos = x_pos;
	prev_mouse_y_pos = y_pos;
}
