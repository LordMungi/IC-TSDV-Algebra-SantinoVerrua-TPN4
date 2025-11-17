#include "program.h"

#include "figure.h"

namespace program
{
	static void init();
	static void update();
	static void draw();
	static void end();

	Camera3D camera;

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
		camera.fovy = 45.0f;
		camera.projection = CAMERA_PERSPECTIVE;

		figures[0] = Figure(LoadModel("resource/cube.obj"), { 0, 0, 0 }, BROWN);
		figures[1] = Figure(LoadModel("resource/decahedron.obj"), { 2, -1, 2 }, BLUE);
		figures[2] = Figure(LoadModel("resource/dodecahedron.obj"), { -2, 0, 2 }, GREEN);
		figures[3] = Figure(LoadModel("resource/icosahedron.obj"), { 2, 0, -2 }, YELLOW);
		figures[4] = Figure(LoadModel("resource/octahedron.obj"), { -2, 0, -2 }, MAGENTA);
		figures[5] = Figure(LoadModel("resource/tetrahedron.obj"), { 0, 2, 0 }, BLACK);

		DisableCursor();
	}

	static void update()
	{
		float delta = GetFrameTime();
		UpdateCamera(&camera, CAMERA_FREE);
	}

	static void draw()
	{
		BeginDrawing();

		ClearBackground(RAYWHITE);

		BeginMode3D(camera);

		for (int i = 0; i < maxFigures; i++)
			figures[i].render();

		DrawGrid(10, 1);

		EndMode3D();

		EndDrawing();
	}

	static void end()
	{
		CloseWindow();
	}
}