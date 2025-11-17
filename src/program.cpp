#include "program.h"

#include "figure.h"
#include "frustum.h"

namespace program
{
	static void init();
	static void update();
	static void draw();
	static void end();

	Camera3D camera;
	Camera3D camera2;

	Frustum frustum;

	bool firstPerson;
	const int maxFigures = 6;

	Figure figures[maxFigures];
	Figure figure;

	void run()
	{
		init();
		while (!WindowShouldClose())
		{
			update();
			draw();
		}
		end();
	}

	static void init()
	{
		InitWindow(1024, 768, "Frustum Culling");

		camera.position = { 0, 5, 7 };
		camera.target = { 0, 0, 0 };
		camera.up = { 0, 1, 0 };
		camera.fovy = 30.0f;
		camera.projection = CAMERA_PERSPECTIVE;

		frustum = Frustum(camera);

		camera2.position = { 0, 10, 10 };
		camera2.target = { 0, 0, 0 };
		camera2.up = { 0, 1, 0 };
		camera2.fovy = 45.0f;
		camera2.projection = CAMERA_PERSPECTIVE;

		figures[0] = Figure(LoadModel("resource/cube.obj"), { 0, 0, 0 }, BROWN);
		figures[1] = Figure(LoadModel("resource/decahedron.obj"), { 2, -1, 2 }, BLUE);
		figures[2] = Figure(LoadModel("resource/dodecahedron.obj"), { -2, 0, 2 }, GREEN);
		figures[3] = Figure(LoadModel("resource/icosahedron.obj"), { 2, 0, -2 }, YELLOW);
		figures[4] = Figure(LoadModel("resource/octahedron.obj"), { -2, 0, -2 }, MAGENTA);
		figures[5] = Figure(LoadModel("resource/tetrahedron.obj"), { 0, 2, 0 }, BLACK);

		firstPerson = true;
		DisableCursor();
	}

	static void update()
	{
		float delta = GetFrameTime();

		UpdateCamera(&camera, CAMERA_FREE);
		frustum.update(camera);

		float fovAddSpeed = 20;

		if (IsKeyPressed(KEY_TAB))
			firstPerson = !firstPerson;
		if (IsKeyDown(KEY_TWO))
			camera.fovy = fmaxf(camera.fovy - fovAddSpeed * delta, 15);
		if (IsKeyDown(KEY_ONE))
			camera.fovy = fminf(camera.fovy + fovAddSpeed * delta, 180);
	}

	static void draw()
	{
		BeginDrawing();

		ClearBackground(RAYWHITE);

		if (firstPerson)
			BeginMode3D(camera);
		else 
			BeginMode3D(camera2);

		for (int i = 0; i < maxFigures; i++)
		{
			if (frustum.isInside(figures[i].getAABB()))
				figures[i].render();
		}


		if (!firstPerson)
			frustum.draw();

		DrawGrid(10, 1);

		EndMode3D();

		EndDrawing();
	}

	static void end()
	{
		CloseWindow();
	}
}