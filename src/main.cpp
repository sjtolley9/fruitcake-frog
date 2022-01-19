/*	This example was sourced from:
	https://trenki2.github.io/blog/2017/06/02/using-sdl2-with-cmake/
	
	This was used to confirm that SDL2 was configured properly with CMake
*/

#include "Application.hpp"

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	Application app;
	app.init();
	app.run();

	return 0;
}
