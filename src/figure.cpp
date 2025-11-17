#include "figure.h"

Figure::Figure()
{
	position = { 0,0,0 };
	rotation = { 0,0,0 };
	size = { 1,1,1 };
	color = RED;

	isSelected = false;
}

Figure::Figure(Model model)
{
	this->model = model;

	position = { 0,0,0 };
	rotation = { 0,0,0 };
	size = { 1,1,1 };
	color = RED;

	getLocalCenter();
	aabb.setAABB(model.meshes[0]);
	aabb.update(model.transform);

	isSelected = false;
}

Figure::Figure(Model model, Vector3 position, Color color)
{
	this->model = model;

	this->position = position;
	rotation = { 0,0,0 };
	size = { 1,1,1 };
	this->color = color;

	getLocalCenter();
	aabb.setAABB(model.meshes[0]);
	aabb.update(model.transform);

	isSelected = false;
	applyTransform();
}

void Figure::getLocalCenter()
{
	Vector3 min = { _FMAX,  _FMAX,  _FMAX };
	Vector3 max = { -_FMAX, -_FMAX, -_FMAX };

	for (int i = 0; i < model.meshes[0].vertexCount * 3; i += 3)
	{
		min = Vector3Min(min, { model.meshes[0].vertices[i], model.meshes[0].vertices[i + 1], model.meshes[0].vertices[i + 2] });
		max = Vector3Max(max, { model.meshes[0].vertices[i], model.meshes[0].vertices[i + 1], model.meshes[0].vertices[i + 2] });
	}

	center = Vector3Scale(Vector3Add(max, min), 0.5f);
}

void Figure::applyTransform()
{
	Matrix translate = MatrixTranslate(position.x, position.y, position.z);
	Matrix rotX = MatrixRotateX(rotation.x * DEG2RAD);
	Matrix rotY = MatrixRotateY(rotation.y * DEG2RAD);
	Matrix rotZ = MatrixRotateZ(rotation.z * DEG2RAD);
	Matrix scale = MatrixScale(size.x, size.y, size.z);

	Matrix rotate(MatrixMultiply(MatrixMultiply(rotZ, rotY), rotX));

	Matrix pivot = MatrixTranslate(center.x, center.y, center.z);
	Matrix negPivot = MatrixTranslate(-center.x, -center.y, -center.z);

	model.transform = MatrixMultiply(MatrixMultiply(MatrixMultiply(pivot, MatrixMultiply(rotate, scale)), negPivot), translate);
	aabb.update(model.transform);
}

void Figure::render()
{
	/*
	if (isSelected)
		DrawModel(model, { 0,0,0 }, 1.0f, RED);
	else
		DrawModel(model, { 0,0,0 }, 1.0f, LIGHTGRAY);
	aabb.render();
	*/
}