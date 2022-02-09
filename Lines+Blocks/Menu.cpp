#include "Main.hpp"
#include "Menu.hpp"
#include "Records.hpp"
#include "Modes.hpp"

static bool isPressedModes(int x, int y) {
	int x1 = 349; 
	int y1 = 191;
	int x2 = 553;
	int y2 = 246;
	if ((x >= x1) && (x <= x2) && (y >= y1) && (y <= y2)) return true;
	return false;
}

static bool isPressedRecords(int x, int y) {
	int x1 = 349;
	int y1 = 267;
	int x2 = 553;
	int y2 = 322;
	if ((x >= x1) && (x <= x2) && (y >= y1) && (y <= y2)) return true;
	return false;

}

static bool isPressedExit(int x, int y) {
	int x1 = 349;
	int y1 = 343;
	int x2 = 553;
	int y2 = 398;
	if ((x >= x1) && (x <= x2) && (y >= y1) && (y <= y2)) return true;
	return false;
}

void menu() {

	SDL_Event e;


	while(1){
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				exit(0);
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if(isPressedExit(e.button.x, e.button.y))exit(0);
				if (isPressedRecords(e.button.x, e.button.y)) records();
				if (isPressedModes(e.button.x, e.button.y)) modes();
			}
		}
		SDL_RenderClear(renderer);
		drawTexture(0, 0, width, height, text_menu, renderer);
		SDL_RenderPresent(renderer);
	}

}
