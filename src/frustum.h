#pragma once
#include "plane.h"
#include "aabb.h"

class Frustum
{
private:

	Vector3 center;

	Vector3 farTopLeft;
	Vector3 farTopRight;
	Vector3 farBottomLeft;
	Vector3 farBottomRight;

	Vector3 nearTopLeft;
	Vector3 nearTopRight;
	Vector3 nearBottomLeft;
	Vector3 nearBottomRight;

	Plane farPlane;
	Plane nearPlane;

	Plane rightPlane;
	Plane leftPlane;

	Plane topPlane;
	Plane bottomPlane;

	bool isAABBinPlane(AABB aabb, Plane plane);
	Plane buildPlane(Vector3 p1, Vector3 p2, Vector3 p3);

public:

	Frustum() = default;
	Frustum(Camera camera);

	void update(Camera camera);
	bool isInside(AABB aabb);

	void draw();
};
