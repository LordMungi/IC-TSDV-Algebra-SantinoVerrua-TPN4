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
	bool isSelected;

	void getLocalCenter();
	void applyTransform();

public:

	Figure();
	Figure(Model model);
	Figure(Model model, Vector3 position, Color color);

	void rotate(Vector3 angle, float delta);

	inline bool isColliding(Figure other) { return aabb.isColliding(other.aabb); };

	inline Vector3 getAABBMin() { return aabb.getMin(); };
	inline Vector3 getAABBMax() { return aabb.getMax(); };

	inline AABB getAABB() { return aabb; };
	inline Model getModel() { return model; };

	inline void setSelected(bool isSelected) { this->isSelected = isSelected; };

	void render();
};