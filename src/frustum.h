#pragma once
#include "plane.h"

class Frustum
{
private:

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

public:

	Frustum() = default;
	Frustum(Camera camera);

	void update(Camera camera);

	void draw();
};
