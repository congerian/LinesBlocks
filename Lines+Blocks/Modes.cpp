#include "Main.hpp"
#include "Menu.hpp"
#include "cl.hpp"
#include "clb.hpp"
#include "sp.hpp"
#include "spb.hpp"

static bool isPressedMenu(int x, int y) {
	int x1 = 558;
	int y1 = 457;
	int x2 = 762;
	int y2 = 512;
	if ((x >= x1) && (x <= x2) && (y >= y1) && (y <= y2)) return true;
	return false;

}

static bool isPressedCl(int x, int y) {
	int x1 = 75;
	int y1 = 220;
	int x2 = 235;
	int y2 = 263;
	if ((x >= x1) && (x <= x2) && (y >= y1) && (y <= y2)) return true;
	return false;

}

static bool isPressedClb(int x, int y) {
	int x1 = 382;
	int y1 = 255;
	int x2 = 542;
	int y2 = 298;
	if ((x >= x1) && (x <= x2) && (y >= y1) && (y <= y2)) return true;
	return false;

}

static bool isPressedSp(int x, int y) {
	int x1 = 75;
	int y1 = 485;
	int x2 = 235;
	int y2 = 528;
	if ((x >= x1) && (x <= x2) && (y >= y1) && (y <= y2)) return true;
	return false;

}

static bool isPressedSpb(int x, int y) {
	int x1 = 653;
	int y1 = 260;
	int x2 = 813;
	int y2 = 303;
	if ((x >= x1) && (x <= x2) && (y >= y1) && (y <= y2)) return true;
	return false;

}

void modes() {
	SDL_Event e;

	while (1) {
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				exit(0);
			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (isPressedMenu(e.button.x, e.button.y)) menu();
				if (isPressedCl(e.button.x, e.button.y)) cl();
				if (isPressedClb(e.button.x, e.button.y)) clb();
				if (isPressedSp(e.button.x, e.button.y)) sp();
				if (isPressedSpb(e.button.x, e.button.y)) spb();
			}
		}
		SDL_RenderClear(renderer);
		drawTexture(0, 0, width, height, text_modes, renderer);
		SDL_RenderPresent(renderer);
	}
}