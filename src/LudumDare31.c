#include "SSL/SSL.h"
#include "SDL2/SDL_Image.h"
#include "SDL2/SDL_Mixer.h"
#include "ludumdare31/config.h"
#include "ludumdare31/ld31/game.h"
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG);
	TTF_Init();
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
	Mix_VolumeMusic(50);
	Mix_Volume(-1, 30);


	srand(time(NULL));

	mute = 0;
	Ld31_config *config = ld31_loadConfig();
	Ld31_game *game = ld31_loadgame(config);
	SSL_Window_Set_Icon(game->window, "../extras/resources/sprites/icon.png");

	SDL_ShowCursor(0);
	cursor = SSL_Image_Load("../extras/resources/sprites/cursor.png", 24, 24, game->window);

	start_game(game);

	return 0;
}


