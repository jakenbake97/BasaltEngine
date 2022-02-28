#include "BEpch.h"
#include "OrthographicCamera.h"

namespace Basalt
{
	/// <summary>
	/// Constructs an orthographic camera and calculates the view projection matrix
	/// </summary>
	/// <param name="left">The position of the left frustum plane</param>
	/// <param name="right">The position of the right frustum plane</param>
	/// <param name="bottom">The position of the bottom frustum plane</param>
	/// <param name="top">The position of the top frustum plane</param>
	OrthographicCamera::OrthographicCamera(const float left, const float right, const float bottom, const float top)
		: projectionMatrix(glm::orthoLH_ZO(left, right, bottom, top, 0.01f, 10.0f)), viewMatrix(1.0f), viewProjectionMatrix(), pos{}
	{
		RecalculateViewProjectionMatrix();
	}

	/// <summary>
	/// Sets the camera's position to the passed in value and recalculates the view projection matrix
	/// </summary>
	/// <param name="position">The new position of the camera</param>
	void OrthographicCamera::SetPosition(const Vector3& position)
	{
		pos = position;
		RecalculateViewProjectionMatrix();
	}

	/// <summary>
	/// Returns the current position of the camera
	/// </summary>
	/// <returns>Vector3 position of the camera</returns>
	Vector3 OrthographicCamera::GetPosition() const
	{
		return pos;
	}

	/// <summary>
	/// Returns the current rotation of the camera
	/// </summary>
	/// <returns>float rotation of the camera around the global Z axis</returns>
	float OrthographicCamera::GetRotation() const
	{
		return rotation;
	}

	/// <summary>
	/// Sets the camera's z axis rotation to the passed in value and recalculates the view projection matrix
	/// </summary>
	/// <param name="zRotation">The new Z axis rotation of the camera</param>
	void OrthographicCamera::SetRotation(const float zRotation)
	{
		rotation = zRotation;
		RecalculateViewProjectionMatrix();
	}

	/// <summary>
	/// Returns the camera's projection matrix
	/// </summary>
	/// <returns>the orthographic projection matrix</returns>
	const Mat4x4& OrthographicCamera::GetProjectionMatrix() const
	{
		return projectionMatrix;
	}

	/// <summary>
	/// Returns the camera's view matrix
	/// </summary>
	/// <returns>the view matrix calculated with the camera's position and rotation</returns>
	const Mat4x4& OrthographicCamera::GetViewMatrix() const
	{
		return viewMatrix;
	}

	/// <summary>
	/// Returns the combined view projections matrix
	/// </summary>
	/// <returns>The cameras view matrix multiplied byt the projection matrix</returns>
	const Mat4x4& OrthographicCamera::GetViewProjectionMatrix() const
	{
		return viewProjectionMatrix;
	}

	/// <summary>
	/// Recalculates the view matrix and multiplies it with the camera's orthographic projection matrix
	/// </summary>
	void OrthographicCamera::RecalculateViewProjectionMatrix()
	{
		const Mat4x4 transform = glm::translate(Mat4x4(1.0f), pos) * 
			glm::rotate(Mat4x4(1.0f), glm::radians(rotation), Vector3(0,0,1));

		viewMatrix = glm::inverse(transform);
		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}
}
