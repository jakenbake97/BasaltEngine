#pragma once
#include "Basalt/Utility/Math.h"

namespace Basalt
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetPosition(const Vector3& position);
		Vector3 GetPosition() const;

		float GetRotation() const;
		void SetRotation(float zRotation);

		const Mat4x4& GetProjectionMatrix() const;
		const Mat4x4& GetViewMatrix() const;
		const Mat4x4& GetViewProjectionMatrix() const;
	private:
		void RecalculateViewProjectionMatrix();
	private:
		Mat4x4 projectionMatrix;
		Mat4x4 viewMatrix;
		Mat4x4 viewProjectionMatrix;

		Vector3 pos;
		float rotation = 0.0f;
	};
}
