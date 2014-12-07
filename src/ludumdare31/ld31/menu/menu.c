#include "menu.h"
#include "../../config.h"
#include "SDL2/SDL_Mixer.h"

int main_menu(Ld31_game *game) {
	printf("%s", Mix_GetError());
	Mix_Music *music = Mix_LoadMUS("../extras/resources/sound/Phat_Sketch.wav");
	Mix_PlayMusic(music, -1);

	int gamemode = -1;
	int running = 1;
	SDL_Event event;

	SSL_Image *image = SSL_Image_Load("../extras/resources/sprites/main_menu_back.png", 768, 768, game->window);

	SSL_Image *inst_suv_back = SSL_Image_Load("../extras/resources/sprites/inst_suv_back.png", 768, 768, game->window);

	SSL_Interface *interface = SSL_Interface_Create();

	SSL_Image_Button *exit_button = SSL_Image_Button_Create(SSL_Rectangle_Create(170,250, 384, 95), SSL_Image_Load("../extras/resources/sprites/exit_button.png", 384, 95, game->window) ,1,2,2);
	SSL_Interface_Add_Image_Button(interface, exit_button);

	SSL_Image_Button *survival_button = SSL_Image_Button_Create(SSL_Rectangle_Create(170,130, 384, 95), SSL_Image_Load("../extras/resources/sprites/survival_button.png", 384, 95, game->window) ,1,2,2);
	SSL_Interface_Add_Image_Button(interface, survival_button);

	SSL_Interface *interface_istr = SSL_Interface_Create();

	SSL_Image_Button *continue_button = SSL_Image_Button_Create(SSL_Rectangle_Create(400,650, 384, 95), SSL_Image_Load("../extras/resources/sprites/continue_button.png", 384, 95, game->window) ,1,2,2);
	SSL_Interface_Add_Image_Button(interface_istr, continue_button);

	SSL_Font *calibri = SSL_Font_Load("../extras/resources/font/Calibri.ttf", 44);
	SSL_Font *calibri_small = SSL_Font_Load("../extras/resources/font/Calibri.ttf", 22);

	while (running) {
		SDL_RenderPresent(game->window->renderer);
		SDL_RenderClear(game->window->renderer);

		SSL_Image_Draw(image, 0, 0, 0, 0 ,SDL_FLIP_NONE ,game->window);
		interface_draw(interface, game->window);
		SSL_Font_Draw(100, 375, 0 ,SDL_FLIP_NONE, "Press: ", calibri, SSL_Color_Create(255,255,255,0), game->window);
		SSL_Font_Draw(220, 375, 0 ,SDL_FLIP_NONE, game->config->mute, calibri, SSL_Color_Create(255,255,255,0), game->window);
		SSL_Font_Draw(85, 420, 0 ,SDL_FLIP_NONE, " To Toggle Mute at any time. ", calibri, SSL_Color_Create(255,255,255,0), game->window);

		while(SDL_PollEvent(&event)) {

			interface_update(interface, event);

			if (survival_button->button_status->clicked) {
				while(!continue_button->button_status->clicked) {
					SDL_RenderPresent(game->window->renderer);
					SDL_RenderClear(game->window->renderer);

					SSL_Image_Draw(inst_suv_back, 0, 0, 0, 0 ,SDL_FLIP_NONE ,game->window);
					interface_draw(interface_istr, game->window);

					SSL_Font_Draw(10, 100, 0 ,SDL_FLIP_NONE, "Controls: ", calibri, SSL_Color_Create(255,255,255,0), game->window);
						SSL_Font_Draw(150, 150, 0 ,SDL_FLIP_NONE, "Up: ", calibri_small, SSL_Color_Create(255,255,255,0), game->window);
						SSL_Font_Draw(190, 150, 0 ,SDL_FLIP_NONE, game->config->snowman_keys.up, calibri_small, SSL_Color_Create(255,255,255,0), game->window);

						SSL_Font_Draw(150, 175, 0 ,SDL_FLIP_NONE, "Down: ", calibri_small, SSL_Color_Create(255,255,255,0), game->window);
						SSL_Font_Draw(210, 175, 0 ,SDL_FLIP_NONE, game->config->snowman_keys.down, calibri_small, SSL_Color_Create(255,255,255,0), game->window);

						SSL_Font_Draw(150, 200, 0 ,SDL_FLIP_NONE, "Left: ", calibri_small, SSL_Color_Create(255,255,255,0), game->window);
						SSL_Font_Draw(210, 200, 0 ,SDL_FLIP_NONE, game->config->snowman_keys.left, calibri_small, SSL_Color_Create(255,255,255,0), game->window);

						SSL_Font_Draw(150, 225, 0 ,SDL_FLIP_NONE, "Right: ", calibri_small, SSL_Color_Create(255,255,255,0), game->window);
						SSL_Font_Draw(210, 225, 0 ,SDL_FLIP_NONE, game->config->snowman_keys.right, calibri_small, SSL_Color_Create(255,255,255,0), game->window);

						SSL_Font_Draw(150, 250, 0 ,SDL_FLIP_NONE, "Shop: ", calibri_small, SSL_Color_Create(255,255,255,0), game->window);
						SSL_Font_Draw(210, 250, 0 ,SDL_FLIP_NONE, game->config->open_shop, calibri_small, SSL_Color_Create(255,255,255,0), game->window);

						SSL_Font_Draw(150, 275, 0 ,SDL_FLIP_NONE, "Fire: ", calibri_small, SSL_Color_Create(255,255,255,0), game->window);
						SSL_Font_Draw(210, 275, 0 ,SDL_FLIP_NONE, "Left Click", calibri_small, SSL_Color_Create(255,255,255,0), game->window);

					while(SDL_PollEvent(&event)) {

						interface_update(interface_istr, event);

						if (SSL_Keybord_Keyname_Pressed(game->config->mute, event)) {
							if (!mute) {
								Mix_VolumeMusic(0);
								Mix_Volume(-1, 0);
								mute = 1;
							} else {
								Mix_VolumeMusic(50);
								Mix_Volume(-1, 30);
								mute = 0;
							}
						}

						if (event.type == SDL_QUIT) {
							exit(0);
							break;
						}
					}
				}

				gamemode = 0;
				running = 0;
			}

			if (SSL_Keybord_Keyname_Pressed(game->config->mute, event)) {
				if (!mute) {
					Mix_VolumeMusic(0);
					Mix_Volume(-1, 0);
					mute = 1;
				} else {
					Mix_VolumeMusic(50);
					Mix_Volume(-1, 30);
					mute = 0;
				}
			}

			if (event.type == SDL_QUIT || exit_button->button_status->clicked) {
				exit(0);
				break;
			}
		}
	}

	SSL_Image_Destroy(image);
	free(image);
	SSL_Image_Destroy(inst_suv_back);
	free(inst_suv_back);
	SSL_Interface_Destroy(interface);
	free(interface);
	free(exit_button);
	free(survival_button);
	SSL_Interface_Destroy(interface_istr);
	free(interface_istr);
	free(continue_button);
	SSL_Font_Destroy(calibri);
	free(calibri);
	SSL_Font_Destroy(calibri_small);
	free(calibri_small);

	Mix_PauseMusic();
	Mix_FreeMusic( music );

	return gamemode;
}
