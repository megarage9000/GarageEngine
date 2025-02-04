#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GarageShaders.h"
#include "GarageEngineObject.h"
#include "DebugOutput.h"
#include "Model.h"
#include "RenderingFrame.h"

// Time
double previous_time = 0.0f;
double elapsed_seconds = 0.0f;

// Movement parameters
float camera_rotation_sensitivity = 40.0f;
float camera_movement_speed = 10.0f;

#pragma region Camera Object
GarageEngine::CameraObject cameraObject;
// Define positions and models here

vector<GarageEngine::RenderableObject> renderableObjects;
vector<GarageEngine::EngineObject> engineObjects;
vector<Shader> shaders;
vector<Model> models;
Mat4 projection;
#pragma endregion

#pragma endregion

#pragma region Function declarations
void input_continuous_callback(GLFWwindow* window);
Mat4 set_up_projection_matrix();

void onInitialize();
void onLoop(GLFWwindow * window);

#pragma endregion
 
int main() {	
	RenderingFrame renderingContext{ 3, 2, 1280, 720, onInitialize, onLoop };
	renderingContext.StartLoop();
}

Mat4 set_up_projection_matrix() {
	float near = 0.1f;
	float far = 100.0f;
	float fov = 67.0f * DEG_TO_RAD;
	float aspect = (float)1280/ (float)720;
	Mat4 perspective = projection_matrix(near, far, fov, aspect);
	return perspective;
}

void onInitialize()
{
	setup_debug();

	// Define Shader here
	Shader MeshShader = Shader(
		"mesh.vert",
		"mesh.frag");

	shaders.push_back(MeshShader);

	// Define Models here
	Model model{ "..\\testMeshes\\backpack\\backpack.obj" };
	Model floor{ "..\\testMeshes\\floor\\floor.fbx" };

	models.push_back(model);
	models.push_back(floor);

	// Defining objects to use scene
	GarageEngine::EngineObject floorObject = GarageEngine::EngineObject{ Vec3{0.0f, -2.0f, 0.0f}, Versor {1.0f, 0.0f, 0.0f, 90.0f} };
	floorObject.ApplyScale(Vec3{ 5.0f, 5.0f, 1.0f });
	engineObjects.push_back(floorObject);

	renderableObjects.push_back(
		GarageEngine::RenderableObject{ floorObject, &floor, &MeshShader }
	);

	for (int i = 0; i < 10; i++) {
		GarageEngine::EngineObject transform{ Vec3 {-10.0f + (i * 2), 0.0f, 0.0f}, Versor {0.0f, 0.0f, 0.0f, 0.0f} };
		engineObjects.push_back(transform);
		GarageEngine::RenderableObject renderable{ transform, &model, &MeshShader };
		renderableObjects.push_back(renderable);
	}

	// Define projection matrix
	projection = set_up_projection_matrix();

	previous_time = glfwGetTime();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);
}

void onLoop(GLFWwindow* window)
{
	// loop
	for (GarageEngine::RenderableObject& renderable : renderableObjects) {
		renderable.engine_object.ApplyTranslation(Vec3{ 0.0f, 1.0f * (float)elapsed_seconds, 0.0f });
		renderable.Update(cameraObject, projection);
	}
}

void input_continuous_callback(GLFWwindow* window)
{
	Vec3 translationChanges{ 0.0f, 0.0f, 0.0f };
	float pitch = 0.0f;
	float yaw = 0.0f;

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
	
	// Rotation
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		pitch += camera_rotation_sensitivity * elapsed_seconds;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		pitch -= camera_rotation_sensitivity * elapsed_seconds;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		yaw += camera_rotation_sensitivity * elapsed_seconds;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		yaw -= camera_rotation_sensitivity * elapsed_seconds;
	}
	
	cameraObject.ApplyTranslation(translationChanges * 5.0f * elapsed_seconds);
	cameraObject.RealignGaze(yaw, pitch);
}
