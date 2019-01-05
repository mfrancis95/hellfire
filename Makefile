all: surface_renderer texture_renderer

clean:
	rm -f *.o surface_renderer texture_renderer

hellfire.o: hellfire.cpp renderer.h
	g++ -c $(FLAGS) hellfire.cpp

software_renderer.o: renderer.h software_renderer.cpp software_renderer.h
	g++ -c $(FLAGS) software_renderer.cpp

surface_renderer: hellfire.o software_renderer.o surface_renderer.cpp
	g++ $(FLAGS) -o surface_renderer hellfire.o software_renderer.o surface_renderer.cpp -lSDL2

texture_renderer: hellfire.o software_renderer.o texture_renderer.cpp
	g++ $(FLAGS) -o texture_renderer hellfire.o software_renderer.o texture_renderer.cpp -lSDL2