#pragma once

#define _CRT_SECURE_NO_DEPRECATE


#include <SDL.h>
#include <SDL_image.h>

void drawTexture(int x, int y, int w, int h, SDL_Texture* tex, SDL_Renderer* rend);

extern bool quit;

extern int rec_cl;
extern int rec_clb;
extern int rec_sp;
extern int rec_spb;

extern SDL_Texture* text_ball1;
extern SDL_Texture* text_ball2;
extern SDL_Texture* text_ball3;
extern SDL_Texture* text_ball4;
extern SDL_Texture* text_ball5;
extern SDL_Texture* text_ball6;
extern SDL_Texture* text_ball7;
extern SDL_Texture* text_ball8;
extern SDL_Texture* text_ball9;

extern SDL_Texture* text_cl;
extern SDL_Texture* text_clb;
extern SDL_Texture* text_sp;
extern SDL_Texture* text_spb;
extern SDL_Texture* text_modes;
extern SDL_Texture* text_records;
extern SDL_Texture* text_menu;
extern SDL_Texture* text_digits;
extern SDL_Texture* text_outline;

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern const int width;
extern const int height;