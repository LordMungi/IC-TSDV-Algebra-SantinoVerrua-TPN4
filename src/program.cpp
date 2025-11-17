#include "program.h"

#include "figure.h"

namespace program
{
	static void init();
	static void update();
	static void draw();

	void run()
	{
		init();

		while (!WindowShouldClose())
		{
			update();
			draw();
		}
	}


}