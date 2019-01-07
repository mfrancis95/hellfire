#include "renderer.h"

Renderer::Renderer(
	SDL_Window *window, const unsigned width, const unsigned height
) : height{height}, width{width}, window{window} {}