all: hellfire.c renderer.h surface_renderer.c
	gcc hellfire.c surface_renderer.c -lSDL2