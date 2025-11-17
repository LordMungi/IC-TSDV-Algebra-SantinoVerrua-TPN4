#include "frustum.h"

#include <raymath.h>

Frustum::Frustum(Camera camera)
{
	update(camera);
}

void Frustum::update(Camera camera)
{
	Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
	Vector3 right = Vector3Normalize(Vector3CrossProduct(camera.up, forward));
	Vector3 up = Vector3Normalize(Vector3CrossProduct(forward, right));
	float fov = camera.fovy * DEG2RAD;

	float nearDistance = 1;
	float farDistance = 20;

	Vector3 farCenter = Vector3Add(camera.position, Vector3Scale(forward, farDistance));
	Vector3 nearCenter = Vector3Add(camera.position, Vector3Scale(forward, nearDistance));

	float farHalfHeight = tan(fov / 2) * farDistance;
	float farHalfWidth = farHalfHeight * 4 / 3;

	float nearHalfHeight = tan(fov / 2) * nearDistance;
	float nearHalfWidth = nearHalfHeight * 4 / 3;

	farTopLeft = Vector3Add(farCenter, Vector3Add(Vector3Scale(right, -farHalfWidth), Vector3Scale(up, farHalfHeight)));
	farTopRight = Vector3Add(farCenter, Vector3Add(Vector3Scale(right, farHalfWidth), Vector3Scale(up, farHalfHeight)));
	farBottomLeft = Vector3Add(farCenter, Vector3Add(Vector3Scale(right, -farHalfWidth), Vector3Scale(up, -farHalfHeight)));
	farBottomRight = Vector3Add(farCenter, Vector3Add(Vector3Scale(right, farHalfWidth), Vector3Scale(up, -farHalfHeight)));
	
	nearTopLeft = Vector3Add(nearCenter, Vector3Add(Vector3Scale(right, -nearHalfWidth), Vector3Scale(up, nearHalfHeight)));
	nearTopRight = Vector3Add(nearCenter, Vector3Add(Vector3Scale(right, nearHalfWidth), Vector3Scale(up, nearHalfHeight)));
	nearBottomLeft = Vector3Add(nearCenter, Vector3Add(Vector3Scale(right, -nearHalfWidth), Vector3Scale(up, -nearHalfHeight)));
	nearBottomRight = Vector3Add(nearCenter, Vector3Add(Vector3Scale(right, nearHalfWidth), Vector3Scale(up, -nearHalfHeight)));

	farPlane.normal = Vector3Normalize(Vector3CrossProduct(Vector3Subtract(farTopLeft, farTopRight), Vector3Subtract(farBottomLeft, farTopRight)));
	farPlane.distance = -Vector3DotProduct(farTopLeft, farPlane.normal);
	
	nearPlane.normal = Vector3Normalize(Vector3CrossProduct(Vector3Subtract(nearTopRight, nearTopLeft), Vector3Subtract(nearBottomRight, nearTopLeft)));
	nearPlane.distance = -Vector3DotProduct(nearTopLeft, nearPlane.normal);
	
	rightPlane.normal = Vector3Normalize(Vector3CrossProduct(Vector3Subtract(farTopRight, nearTopRight), Vector3Subtract(farBottomRight, nearTopRight)));
	rightPlane.distance = -Vector3DotProduct(farTopRight, rightPlane.normal);
	
	leftPlane.normal = Vector3Normalize(Vector3CrossProduct(Vector3Subtract(farBottomLeft, nearTopLeft), Vector3Subtract(farTopLeft, nearTopLeft)));
	leftPlane.distance = -Vector3DotProduct(farTopLeft, leftPlane.normal);

	topPlane.normal = Vector3Normalize(Vector3CrossProduct(Vector3Subtract(nearTopRight, nearTopLeft), Vector3Subtract(farTopRight, nearTopLeft)));
	topPlane.distance = -Vector3DotProduct(farTopLeft, topPlane.normal);

	bottomPlane.normal = Vector3Normalize(Vector3CrossProduct(Vector3Subtract(nearBottomLeft, nearBottomRight), Vector3Subtract(farBottomLeft, nearBottomRight)));
	bottomPlane.distance = -Vector3DotProduct(farBottomLeft, bottomPlane.normal);

}

void Frustum::draw()
{
	DrawLine3D(nearTopLeft, farTopLeft, GREEN);
	DrawLine3D(nearTopRight, farTopRight, GREEN);
	DrawLine3D(nearBottomLeft, farBottomLeft, GREEN);
	DrawLine3D(nearBottomRight, farBottomRight, GREEN);

	DrawLine3D(nearTopLeft, nearTopRight, GREEN);
	DrawLine3D(nearTopLeft, nearBottomLeft, GREEN);
	DrawLine3D(nearBottomRight, nearTopRight, GREEN);
	DrawLine3D(nearBottomRight, nearBottomLeft, GREEN);

	DrawLine3D(farTopLeft, farTopRight, GREEN);
	DrawLine3D(farTopLeft, farBottomLeft, GREEN);
	DrawLine3D(farBottomRight, farTopRight, GREEN);
	DrawLine3D(farBottomRight, farBottomLeft, GREEN);
}