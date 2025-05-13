#pragma once

#include "GarageMathLibrary.h"
#include "Model.h"
#include "GarageShaders.h"
#include <iostream>
#include <vector>

namespace GarageEngine {

	using namespace GarageLinearAlgebra;

#pragma region EngineObject
	class EngineObject {

	private:
		Vec3 position;
		Vec3 scale_dimensions;
		Versor orientation;

		void ApplyDirections() {
			const Mat4 orientation_matrix = orientation.to_matrix();
			up = orientation_matrix * Vec4(0.0f, 1.0f, 0.0f, 0.0f);
			forward = orientation_matrix * Vec4(0.0f, 0.0f, 1.0f, 0.0f);
			right = orientation_matrix * Vec4(1.0f, 0.0f, 0.0f, 0.0f);
		}

	public:

		EngineObject(const EngineObject& other) noexcept {

		}

		// Move semantics 
		EngineObject(const EngineObject&& other) noexcept : 
			position(other.position),
			scale_dimensions(other.scale_dimensions),
			orientation(other.orientation),
			forward(other.forward),
			up(other.up) {	}



		Vec3 forward;
		Vec3 up;
		Vec3 right;
		EngineObject();
		EngineObject(Vec3 position, Versor orientation);
		void SetPosition(Vec3 position);
		void SetForward(Vec3 forward);
		void SetRight(Vec3 right);
		void SetUp(Vec3 up);
		Vec3 Position();
		Mat4 OrientationMatrix();
		Mat4 TranslationMatrix();
		Mat4 ApplyRotations(std::vector<Versor> versors);
		Mat4 ApplyTranslation(Vec3 translation_changes);
		Mat4 ApplyScale(Vec3 scale_changes);
		Mat4 GetTransformationMatrix();
		Vec3 GetForward();
		Vec3 GetUp();
		Vec3 GetRight();
	};
#pragma endregion EngineObject

#pragma region CameraObject
	class CameraObject {
	private:
		Vec3 position;

		Vec3 camera_front;
		Vec3 camera_up;
		Vec3 camera_right;

		Versor orientation;

		float yaw; 
		float pitch;

		void GetNewDirectionsOrientation() {
			Mat4 orientation_matrix = orientation.to_matrix();
			camera_front = orientation_matrix * Vec3{ 0.0f, 0.0f, -1.0f };
			camera_right = orientation_matrix * Vec3{ 1.0f, 0.0f, 0.0f };
			camera_up = orientation_matrix * Vec3{ 0.0f, 1.0f, 0.0f };
		}

		void InitializeAxes() {
			camera_up = Vec3{ 0.0, 1.0f, 0.0f };
			camera_right = Vec3{ 1.0f, 0.0f, 0.0f };
			camera_front = Vec3{ 0.0f, 0.0f, -1.0f };
			yaw = 0.0f;
			pitch = 0.0f;
		}

	public:
		CameraObject();
		CameraObject(Vec3 position);
		CameraObject(Vec3 position, Versor orientation);
		void RealignGaze(float x, float y);
		void UpdateYawAndPitch(float yaw, float pitch);
		void ApplyTranslation(Vec3 translation_changes);
		Mat4 GetViewMatrix();
		Vec3 GetCameraPos();
		Vec3 GetFront();
		Vec3 GetRight();
		Vec3 GetUp();
	};
#pragma endregion CameraObject

#pragma region RenderableObject
	class RenderableObject {
	public:
		Model* model;
		Shader* shader;
		EngineObject engine_object;

		RenderableObject(EngineObject& engine_object, Model* model, Shader* shader) 
			: engine_object(engine_object), model(model), shader(shader) {}

		virtual void Update(CameraObject& camera_object, const Mat4& projection_matrix);
		virtual ~RenderableObject() = default;
		
	};

#pragma endregion RenderableObject
};




