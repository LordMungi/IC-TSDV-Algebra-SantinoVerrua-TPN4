#include "frustum.h"

#include <raymath.h>
#include <iostream>

Frustum::Frustum(Camera camera)
{
	update(camera);
}

void Frustum::update(Camera camera)
{
	Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
	Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, camera.up));
	Vector3 up = Vector3Normalize(Vector3CrossProduct(right, forward));
	float fov = camera.fovy * DEG2RAD;

	float nearDistance = 1;
	float farDistance = 100;

	Vector3 farCenter = Vector3Add(camera.position, Vector3Scale(forward, farDistance));
	Vector3 nearCenter = Vector3Add(camera.position, Vector3Scale(forward, nearDistance));

	float farHalfHeight = static_cast<float>(tan(fov / 2) * farDistance);
	float farHalfWidth = static_cast<float>(farHalfHeight * 4/3);

	float nearHalfHeight = static_cast<float>(tan(fov / 2) * nearDistance);
	float nearHalfWidth = static_cast<float>(nearHalfHeight * 4/3);

	farTopLeft = Vector3Add(farCenter, Vector3Add(Vector3Scale(right, -farHalfWidth), Vector3Scale(up, farHalfHeight)));
	farTopRight = Vector3Add(farCenter, Vector3Add(Vector3Scale(right, farHalfWidth), Vector3Scale(up, farHalfHeight)));
	farBottomLeft = Vector3Add(farCenter, Vector3Add(Vector3Scale(right, -farHalfWidth), Vector3Scale(up, -farHalfHeight)));
	farBottomRight = Vector3Add(farCenter, Vector3Add(Vector3Scale(right, farHalfWidth), Vector3Scale(up, -farHalfHeight)));
	
	nearTopLeft = Vector3Add(nearCenter, Vector3Add(Vector3Scale(right, -nearHalfWidth), Vector3Scale(up, nearHalfHeight)));
	nearTopRight = Vector3Add(nearCenter, Vector3Add(Vector3Scale(right, nearHalfWidth), Vector3Scale(up, nearHalfHeight)));
	nearBottomLeft = Vector3Add(nearCenter, Vector3Add(Vector3Scale(right, -nearHalfWidth), Vector3Scale(up, -nearHalfHeight)));
	nearBottomRight = Vector3Add(nearCenter, Vector3Add(Vector3Scale(right, nearHalfWidth), Vector3Scale(up, -nearHalfHeight)));

	center = Vector3Scale(Vector3Add(farCenter, nearCenter), 0.5f);

	farPlane = buildPlane(farTopRight, farTopLeft, farBottomRight);
	nearPlane = buildPlane(nearTopRight, nearTopLeft, nearBottomRight);
	rightPlane = buildPlane(nearTopRight, farTopRight, farBottomRight);
	leftPlane = buildPlane(nearTopLeft, farBottomLeft, farTopLeft);
	topPlane = buildPlane(nearTopLeft, nearTopRight, farTopRight);
	bottomPlane = buildPlane(nearBottomRight, nearBottomLeft, farBottomLeft);
}

Plane Frustum::buildPlane(Vector3 p1, Vector3 p2, Vector3 p3)
{
	Plane plane;
	plane.normal = Vector3Normalize(Vector3CrossProduct(Vector3Subtract(p2, p1), Vector3Subtract(p3, p1)));
	if (Vector3DotProduct(plane.normal, Vector3Subtract(center, p1)) < 0)
		plane.normal = Vector3Negate(plane.normal);
	plane.distance = -Vector3DotProduct(p1, plane.normal);
	return plane;
}

bool Frustum::isAABBinPlane(AABB aabb, Plane plane)
{
	Vector3 point;
	if (plane.normal.x > 0)
		point.x = aabb.getMax().x;
	else
		point.x = aabb.getMin().x;

	if (plane.normal.y > 0)
		point.y = aabb.getMax().y;
	else
		point.y = aabb.getMin().y;

	if (plane.normal.z > 0)
		point.z = aabb.getMax().z;
	else
		point.z = aabb.getMin().z;

	return Vector3DotProduct(plane.normal, point) + plane.distance >= 0;
}

bool Frustum::isInside(AABB aabb)
{
	return (isAABBinPlane(aabb, farPlane) && isAABBinPlane(aabb, nearPlane) &&
		isAABBinPlane(aabb, rightPlane) && isAABBinPlane(aabb, leftPlane) &&
		isAABBinPlane(aabb, topPlane) && isAABBinPlane(aabb, bottomPlane));
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