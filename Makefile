all: surface_renderer texture_renderer

clean:
	rm -f *.o surface_renderer texture_renderer

hellfire.o: hellfire.c renderer.h
	gcc -c $(FLAGS) hellfire.c

software_renderer.o: software_renderer.c software_renderer.h
	gcc -c $(FLAGS) software_renderer.c

surface_renderer: hellfire.o software_renderer.o surface_renderer.c
	gcc $(FLAGS) -o surface_renderer hellfire.o software_renderer.o surface_renderer.c -lSDL2

texture_renderer: hellfire.o software_renderer.o texture_renderer.c
	gcc $(FLAGS) -o texture_renderer hellfire.o software_renderer.o texture_renderer.c -lSDL2