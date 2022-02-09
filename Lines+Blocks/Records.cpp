#pragma once

#include "Main.hpp"
#include "Records.hpp"
#include "Menu.hpp"
#include "Digits.hpp"

#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;

const string save = "save";

static bool isPressedMenu(int x, int y) {
	int x1 = 658;
	int y1 = 470;
	int x2 = 862;
	int y2 = 525;
	if ((x >= x1) && (x <= x2) && (y >= y1) && (y <= y2)) return true;
	return false;

}

void getRecords() {	
	FILE* f;
	f = fopen(save.c_str(), "r");
	if (f == NULL) {
		rec_cl = 0;
		rec_clb = 0;
		rec_sp = 0;
		rec_spb = 0;
		setRecords(0, 0, 0, 0);
	}
	else {
		fscanf(f, "%d %d %d %d", &rec_cl, &rec_clb, &rec_sp, &rec_spb);
	}
	fclose(f);
}

void setRecords(int rcl, int rclb, int rsp, int rspb) {
	FILE* f;
	f = fopen(save.c_str(), "w");
	fprintf(f, "%d %d %d %d", rcl, rclb, rsp, rspb);
	fclose(f);
}

void records() {
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
			}
		}
		SDL_RenderClear(renderer);
		drawTexture(0, 0, width, height, text_records, renderer);
		drawNumber(210, 165, 32, 18, rec_cl);
		drawNumber(210, 330, 32, 18, rec_sp);
		drawNumber(610, 165, 32, 18, rec_clb);
		drawNumber(613, 363, 32, 18, rec_spb);
		SDL_RenderPresent(renderer);
	}
}