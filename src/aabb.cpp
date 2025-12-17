#include "aabb.h"

AABB::AABB()
{
	localMin = { 0,0,0 };
	localMax = { 0,0,0 };
}

void AABB::calculateSize(Mesh mesh)
{
	localMin = { _FMAX,  _FMAX,  _FMAX };
	localMax = { -_FMAX, -_FMAX, -_FMAX };
	
	for (int i = 0; i < mesh.vertexCount * 3; i += 3)
	{
		localMin = Vector3Min(localMin, { mesh.vertices[i], mesh.vertices[i + 1], mesh.vertices[i + 2] });
		localMax = Vector3Max(localMax, { mesh.vertices[i], mesh.vertices[i + 1], mesh.vertices[i + 2] });
	}
}

void AABB::update(Matrix transform)
{
	Vector3 corners[8] =
	{
		{localMin.x, localMin.y, localMin.z},
		{localMax.x, localMin.y, localMin.z},
		{localMin.x, localMax.y, localMin.z},
		{localMin.x, localMin.y, localMax.z},
		{localMax.x, localMax.y, localMax.z},
		{localMin.x, localMax.y, localMax.z},
		{localMax.x, localMin.y, localMax.z},
		{localMax.x, localMax.y, localMin.z},
	};

	for (int i = 0; i < 8; i++)
		points[i] = Vector3Transform(corners[i], transform);
}

void AABB::setAABB(Mesh mesh)
{
	calculateSize(mesh);
}

bool AABB::isColliding(AABB other)
{
	if (max.x < other.min.x || min.x > other.max.x) return false;
	if (max.y < other.min.y || min.y > other.max.y) return false;
	if (max.z < other.min.z || min.z > other.max.z) return false;
	return true;
}

void AABB::render()
{
	DrawLine3D(points[0], points[1], RED);
	DrawLine3D(points[0], points[2], RED);
	DrawLine3D(points[0], points[3], RED);
	DrawLine3D(points[2], points[5], RED);
	DrawLine3D(points[5], points[3], RED);
	DrawLine3D(points[3], points[6], RED);
	DrawLine3D(points[4], points[5], RED);
	DrawLine3D(points[4], points[6], RED);
	DrawLine3D(points[4], points[7], RED);
	DrawLine3D(points[6], points[1], RED);
	DrawLine3D(points[1], points[7], RED);
	DrawLine3D(points[7], points[2], RED);
}