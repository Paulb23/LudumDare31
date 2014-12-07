#include "../../config.h"


int main_menu(Ld31_game *game) {
	int gamemode = 0;
	int running = 1;
	SDL_Event event;

	SSL_Image *image = SSL_Image_Load("../extras/resources/sprites/main_menu_back.png", 768, 768, game->window);

	SSL_Interface *interface = SSL_Interface_Create();

	SSL_Image_Button *exit_button = SSL_Image_Button_Create(SSL_Rectangle_Create(170,550, 384, 95), SSL_Image_Load("../extras/resources/sprites/exit_button.png", 384, 95, game->window) ,1,2,2);
	SSL_Interface_Add_Image_Button(interface, exit_button);

	while (running) {
		SDL_RenderPresent(game->window->renderer);
		SDL_RenderClear(game->window->renderer);

		SSL_Image_Draw(image, 0, 0, 0, 0 ,SDL_FLIP_NONE ,game->window);
		interface_draw(interface, game->window);

		while(SDL_PollEvent(&event)) {

			interface_update(interface, event);

			if (event.type == SDL_QUIT || exit_button->button_status->clicked) {
				exit(0);
				break;
			}
		}
	}

	return gamemode;
}
