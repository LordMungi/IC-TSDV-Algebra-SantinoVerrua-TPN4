#pragma once
#include <raylib.h>
#include <raymath.h>

class AABB
{
private:

	Vector3 localMin;
	Vector3 localMax;

	Vector3 min;
	Vector3 max;

	Vector3 points[8] = {};

	void calculateSize(Mesh mesh);
	void applyTransform(Matrix transform);
public:

	AABB();

	void setAABB(Mesh mesh);
	void update(Matrix transform);

	bool isColliding(AABB other);

	inline Vector3 getMin() { return min; };
	inline Vector3 getMax() { return max; };
	inline Vector3 getPoint(int i) { return points[i]; };

	void render();
};