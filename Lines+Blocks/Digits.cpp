#include "Main.hpp"
#include "Digits.hpp"
#include <math.h>

void drawDigit(int x, int y, int h, int w, int digit) {
	SDL_Rect imgPartRect;
	imgPartRect.x = 9*digit;
	imgPartRect.y = 0;
	imgPartRect.w = 9;
	imgPartRect.h = 16;

	SDL_Rect target;
	target.x = x;
	target.y = y;
	target.w = w;
	target.h = h;
	SDL_RenderCopy(renderer, text_digits, &imgPartRect, &target);
}

void drawNumber(int x, int y, int h, int w, int num) {
	if (num == 0) {
		drawDigit(x, y, h, w, 0);
	}
	int n = log10(num);
	while (num != 0) {
		drawDigit(x + w * n, y, h, w, num % 10);
		num /= 10;
		n--;
	}
}