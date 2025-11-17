#pragma once
#include "aabb.h"

class Figure
{
private:

	Model model;
	AABB aabb;

	Vector3 position;
	Vector3 rotation;
	Vector3 size;

	Vector3 center;

	Color color;

	void applyTransform();
	void getLocalCenter();

public:

	Figure();
	Figure(Model model);
	Figure(Model model, Vector3 position, Color color);

	inline bool isColliding(Figure other) { return aabb.isColliding(other.aabb); };

	inline Vector3 getAABBMin() { return aabb.getMin(); };
	inline Vector3 getAABBMax() { return aabb.getMax(); };

	void render();
};