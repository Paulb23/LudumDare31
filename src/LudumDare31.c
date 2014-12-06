#include "SSL/SSL.h"
#include "SDL2/SDL_Image.h"
#include "SDL2/SDL_Mixer.h"
#include "ludumdare31/config.h"

int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	Mix_Init(MIX_INIT_MP3);
	TTF_Init();

	ld31_loadConfig();

	SSL_Window *window = SSL_Window_Create(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED ,window_width, window_height, window_res_width, window_res_height, 0);

	int running = 1;
	SDL_Event event;
	while (running) {
		while(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = 0;
			}
		}
	}

	return 0;
}


