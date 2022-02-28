#pragma once
#include "Basalt/Utility/Math.h"

namespace Basalt
{
	class OrthographicCamera
	{
	public:
		/// <summary>
		/// Constructs an orthographic camera and calculates the view projection matrix
		/// </summary>
		/// <param name="left">The position of the left frustum plane</param>
		/// <param name="right">The position of the right frustum plane</param>
		/// <param name="bottom">The position of the bottom frustum plane</param>
		/// <param name="top">The position of the top frustum plane</param>
		OrthographicCamera(float left, float right, float bottom, float top);

		/// <summary>
		/// Sets the camera's position to the passed in value and recalculates the view projection matrix
		/// </summary>
		/// <param name="position">The new position of the camera</param>
		void SetPosition(const Vector3& position);

		/// <summary>
		/// Returns the current position of the camera
		/// </summary>
		/// <returns>Vector3 position of the camera</returns>
		Vector3 GetPosition() const;

		/// <summary>
		/// Returns the current rotation of the camera
		/// </summary>
		/// <returns>float rotation of the camera around the global Z axis</returns>
		float GetRotation() const;

		/// <summary>
		/// Sets the camera's z axis rotation to the passed in value and recalculates the view projection matrix
		/// </summary>
		/// <param name="zRotation">The new Z axis rotation of the camera</param>
		void SetRotation(float zRotation);

		/// <summary>
		/// Returns the camera's projection matrix
		/// </summary>
		/// <returns>the orthographic projection matrix</returns>
		const Mat4x4& GetProjectionMatrix() const;

		/// <summary>
		/// Returns the camera's view matrix
		/// </summary>
		/// <returns>the view matrix calculated with the camera's position and rotation</returns>
		const Mat4x4& GetViewMatrix() const;

		/// <summary>
		/// Returns the combined view projections matrix
		/// </summary>
		/// <returns>The cameras view matrix multiplied byt the projection matrix</returns>
		const Mat4x4& GetViewProjectionMatrix() const;
	private:
		/// <summary>
		/// Recalculates the view matrix and multiplies it with the camera's orthographic projection matrix
		/// </summary>
		void RecalculateViewProjectionMatrix();
	private:
		Mat4x4 projectionMatrix;
		Mat4x4 viewMatrix;
		Mat4x4 viewProjectionMatrix;

		Vector3 pos;
		float rotation = 0.0f;
	};
}
