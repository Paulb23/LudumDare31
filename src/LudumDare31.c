#include "SSL/SSL.h"
#include "SDL2/SDL_Image.h"
#include "SDL2/SDL_Mixer.h"
#include "ludumdare31/config.h"
#include "ludumdare31/ld31/game.h"

int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	Mix_Init(MIX_INIT_MP3);
	TTF_Init();

	Ld31_config *config = ld31_loadConfig();
	start_game(config);

	return 0;
}


