#include "GarageEngineObject.h"

namespace GarageEngine {

#pragma region EngineObject Methods

	EngineObject::EngineObject() {
		forward = Vec3{ 0.0, 0.0, 1.0f };
		right = Vec3{ 1.0f, 0.0f, 0.0f };
		up = Vec3{ 0.0f, 1.0f, 0.0f };
		position = Vec3{ 0.0f, 0.0f, 0.0f };
		orientation = Versor{ 0.0f, 1.0f, 0.0f, 0.0f };
	}

	EngineObject::EngineObject(Vec3 position, Versor orientation) : position(position), orientation(orientation) {
		forward = Vec3{ 0.0, 0.0, 1.0f };
		right = Vec3{ 1.0f, 0.0f, 0.0f };
		up = Vec3{ 0.0f, 1.0f, 0.0f };
		ApplyDirections();
	}

	void EngineObject::SetPosition(Vec3 position) {
		this->position = position;
	}
	void EngineObject::SetScale(Vec3 scale)
	{
		this->scale_dimensions = scale;
	}
	void EngineObject::SetRotation(Versor rotation)
	{
		this->orientation = rotation;
	}
	void EngineObject::SetForward(Vec3 forward) {
		this->forward = forward;
	}
	void EngineObject::SetRight(Vec3 right) {
		this->right = right;
	}
	void EngineObject::SetUp(Vec3 up) {
		this->up = up;
	}

	Vec3 EngineObject::Position() {
		return position;
	}
	Mat4 EngineObject::OrientationMatrix() {
		return orientation.to_matrix();
	}

	Mat4 EngineObject::TranslationMatrix() {
		return translate(position);
	}

	Mat4 EngineObject::ApplyRotations(std::vector<Versor> versors) {
		for (auto versor : versors) {
			orientation = versor * orientation;
		}
		ApplyDirections();
		return orientation.to_matrix();
	}

	Mat4 EngineObject::ApplyTranslation(Vec3 translation_changes) {
		Vec3 right_move = right * translation_changes[0];
		Vec3 up_move = up * translation_changes[1];
		Vec3 forward_move = forward * translation_changes[2];

		position = position + right_move + up_move + forward_move;
		return translate(position);
	}

	Mat4 EngineObject::ApplyScale(Vec3 scale_changes) {
		scale_dimensions = scale_changes;
		return scale(scale_dimensions);
	}

	Mat4 EngineObject::GetTransformationMatrix() {
		return translate(position) * orientation.to_matrix() * scale(scale_dimensions);
	}
	Vec3 EngineObject::GetForward() {
		return forward;
	}

	Vec3 EngineObject::GetUp() {
		return up;
	}

	Vec3 EngineObject::GetRight() {
		return right;
	}

#pragma endregion EngineObject Methods

#pragma region CameraObject Methods
	CameraObject::CameraObject() {
		position = Vec3(0.0f, 0.0f, 5.0f);
		orientation = Versor(Vec3{ 0.0, 1.0, 0.0 }, 0.0f);
		InitializeAxes();
		GetNewDirectionsOrientation();
	}
	CameraObject::CameraObject(Vec3 position) : position(position) {
		orientation = Versor(Vec3{ 0.0, 1.0, 0.0 }, 0.0f);
		InitializeAxes();
		GetNewDirectionsOrientation();
	}

	CameraObject::CameraObject(Vec3 position, Versor orientation) : position(position), orientation(orientation) {
		InitializeAxes();
		GetNewDirectionsOrientation();
	}

	void CameraObject::RealignGaze(float x, float y) {

		// Use Global Up axis for horizontal rotation to 
		// prevent unwanted z-axis rotation/roll
		Versor horizontal_rotation{ Vec3{0.0f, 1.0f, 0.0f}, x };
		Versor vertical_rotation{ camera_right, y };

		orientation = horizontal_rotation * vertical_rotation * orientation;
		GetNewDirectionsOrientation();
	}

	void CameraObject::UpdateYawAndPitch(float yaw, float pitch)
	{
	}

	void CameraObject::ApplyTranslation(Vec3 translation_changes) {
		position = position -
			camera_right * translation_changes[0] +
			camera_up * translation_changes[1] +
			camera_front * translation_changes[2];
	}

	Mat4 CameraObject::GetViewMatrix() {
		return orientation.to_matrix().inverse() * translate(position).inverse();
	}

	Vec3 CameraObject::GetCameraPos() {
		return Vec3(position);
	}

	Vec3 CameraObject::GetFront() {
		return camera_front;
	}

	Vec3 CameraObject::GetRight() {
		return camera_right;
	}

	Vec3 CameraObject::GetUp() {
		return camera_up;
	}
#pragma endregion CameraObject Methods

#pragma region RenderableObject Methods

#pragma endregion RenderableObject Methods

	void RenderableObject::Update(CameraObject& camera_object, const Mat4& projection_matrix)
	{
		if (shader == nullptr || model == nullptr) {
			return;
		}

		shader->SetMatrix4("transform_matrix", engine_object.GetTransformationMatrix(), GL_TRUE);
		shader->SetMatrix4("projection", projection_matrix, GL_TRUE);
		shader->SetMatrix4("view", camera_object.GetViewMatrix(), GL_TRUE);
		model->Draw(*shader);
		
	}

	void RenderableObject::UpdateInstances(CameraObject& camera_object, const Mat4& projection_matrix, unsigned int instances) {
		if (shader == nullptr || model == nullptr) {
			return;
		}

		shader->SetMatrix4("transform_matrix", engine_object.GetTransformationMatrix(), GL_TRUE);
		shader->SetMatrix4("projection", projection_matrix, GL_TRUE);
		shader->SetMatrix4("view", camera_object.GetViewMatrix(), GL_TRUE);
		model->DrawInstanced(*shader, instances);
	}

};