#include "BEpch.h"
#include "OrthographicCamera.h"

namespace Basalt
{
	OrthographicCamera::OrthographicCamera(const float left, const float right, const float bottom, const float top)
		: projectionMatrix(glm::orthoLH_ZO(left, right, bottom, top, 0.01f, 10.0f)), viewMatrix(1.0f), viewProjectionMatrix(), pos{}
	{
		RecalculateViewMatrix();
	}

	void OrthographicCamera::SetPosition(const Vector3& position)
	{
		pos = position;
		RecalculateViewMatrix();
	}

	Vector3 OrthographicCamera::GetPosition() const
	{
		return pos;
	}

	float OrthographicCamera::GetRotation() const
	{
		return rotation;
	}

	void OrthographicCamera::SetRotation(const float zRotation)
	{
		rotation = zRotation;
		RecalculateViewMatrix();
	}

	const Mat4x4& OrthographicCamera::GetProjectionMatrix() const
	{
		return projectionMatrix;
	}

	const Mat4x4& OrthographicCamera::GetViewMatrix() const
	{
		return viewMatrix;
	}

	const Mat4x4& OrthographicCamera::GetViewProjectionMatrix() const
	{
		return viewProjectionMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		const Mat4x4 transform = glm::translate(Mat4x4(1.0f), pos) * 
			glm::rotate(Mat4x4(1.0f), glm::radians(rotation), Vector3(0,0,1));

		viewMatrix = glm::inverse(transform);
		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}
}
