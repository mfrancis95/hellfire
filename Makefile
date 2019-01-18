all: mapped_renderer subdata_renderer surface_renderer texture_renderer

clean:
	rm -f *.o mapped_renderer subdata_renderer surface_renderer texture_renderer

hellfire.o: hellfire.cpp renderer.h
	g++ -c $(FLAGS) hellfire.cpp

mapped_renderer: hellfire.o mapped_renderer.cpp opengl_renderer.o
	g++ $(FLAGS) -o mapped_renderer hellfire.o mapped_renderer.cpp renderer.o software_renderer.o opengl_renderer.o -lGL -lSDL2

opengl_renderer.o: opengl_renderer.cpp opengl_renderer.h renderer.o software_renderer.o
	g++ -c $(FLAGS) opengl_renderer.cpp

renderer.o: renderer.cpp renderer.h
	g++ -c $(FLAGS) renderer.cpp

software_renderer.o: renderer.o software_renderer.cpp software_renderer.h
	g++ -c $(FLAGS) software_renderer.cpp

subdata_renderer: hellfire.o subdata_renderer.cpp opengl_renderer.o
	g++ $(FLAGS) -o subdata_renderer hellfire.o renderer.o software_renderer.o subdata_renderer.cpp opengl_renderer.o -lGL -lSDL2

surface_renderer: hellfire.o software_renderer.o surface_renderer.cpp
	g++ $(FLAGS) -o surface_renderer hellfire.o renderer.o software_renderer.o surface_renderer.cpp -lSDL2

texture_renderer: hellfire.o software_renderer.o texture_renderer.cpp
	g++ $(FLAGS) -o texture_renderer hellfire.o renderer.o software_renderer.o texture_renderer.cpp -lSDL2