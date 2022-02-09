#include "Main.hpp"
#include "Menu.hpp"
#include "Records.hpp"
#include <string>

using namespace std;

bool quit = false;

int rec_cl;
int rec_clb;
int rec_sp;
int rec_spb;

const int width = 896;
const int height = 576;

SDL_Window* window;
SDL_Renderer* renderer;

const string src_dir = "sprites/";

const string src_ball1 = "b1.png";			SDL_Surface* surf_ball1;	SDL_Texture* text_ball1;
const string src_ball2 = "b2.png";			SDL_Surface* surf_ball2;	SDL_Texture* text_ball2;
const string src_ball3 = "b3.png";			SDL_Surface* surf_ball3;	SDL_Texture* text_ball3;
const string src_ball4 = "b4.png";			SDL_Surface* surf_ball4;	SDL_Texture* text_ball4;
const string src_ball5 = "b5.png";			SDL_Surface* surf_ball5;	SDL_Texture* text_ball5;
const string src_ball6 = "b6.png";			SDL_Surface* surf_ball6;	SDL_Texture* text_ball6;
const string src_ball7 = "b7.png";			SDL_Surface* surf_ball7;	SDL_Texture* text_ball7;
const string src_ball8 = "b8.png";			SDL_Surface* surf_ball8;	SDL_Texture* text_ball8;
const string src_ball9 = "b9.png";			SDL_Surface* surf_ball9;	SDL_Texture* text_ball9;

const string src_menu		= "menu.png";		SDL_Surface* surf_menu;			SDL_Texture* text_menu;
const string src_cl			= "cl.png";			SDL_Surface* surf_cl;			SDL_Texture* text_cl;
const string src_clb		= "clb.png";		SDL_Surface* surf_clb;			SDL_Texture* text_clb;
const string src_sp			= "sp.png";			SDL_Surface* surf_sp;			SDL_Texture* text_sp;
const string src_spb		= "spb.png";		SDL_Surface* surf_spb;			SDL_Texture* text_spb;
const string src_modes		= "modes.png";		SDL_Surface* surf_modes;		SDL_Texture* text_modes;
const string src_records	= "records.png";	SDL_Surface* surf_records;		SDL_Texture* text_records;
const string src_digits		= "digits.png";		SDL_Surface* surf_digits;		SDL_Texture* text_digits;
const string src_outline	= "outline.png";	SDL_Surface* surf_outline;		SDL_Texture* text_outline;

void drawTexture(int x, int y, int w, int h, SDL_Texture* tex, SDL_Renderer* rend) {
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	pos.w = w;
	pos.h = h;
	SDL_RenderCopy(rend, tex, NULL, &pos);
}

int main(int argc, char* argv[])
{

	SDL_Init(SDL_INIT_EVERYTHING); 
	window = SDL_CreateWindow("Lines + Blocks!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	IMG_Init(IMG_INIT_JPG);
	
	surf_ball1 = IMG_Load((src_dir + src_ball1).c_str()); text_ball1 = SDL_CreateTextureFromSurface(renderer, surf_ball1);
	surf_ball2 = IMG_Load((src_dir + src_ball2).c_str()); text_ball2 = SDL_CreateTextureFromSurface(renderer, surf_ball2);
	surf_ball3 = IMG_Load((src_dir + src_ball3).c_str()); text_ball3 = SDL_CreateTextureFromSurface(renderer, surf_ball3);
	surf_ball4 = IMG_Load((src_dir + src_ball4).c_str()); text_ball4 = SDL_CreateTextureFromSurface(renderer, surf_ball4);
	surf_ball5 = IMG_Load((src_dir + src_ball5).c_str()); text_ball5 = SDL_CreateTextureFromSurface(renderer, surf_ball5);
	surf_ball6 = IMG_Load((src_dir + src_ball6).c_str()); text_ball6 = SDL_CreateTextureFromSurface(renderer, surf_ball6);
	surf_ball7 = IMG_Load((src_dir + src_ball7).c_str()); text_ball7 = SDL_CreateTextureFromSurface(renderer, surf_ball7);
	surf_ball8 = IMG_Load((src_dir + src_ball8).c_str()); text_ball8 = SDL_CreateTextureFromSurface(renderer, surf_ball8);
	surf_ball9 = IMG_Load((src_dir + src_ball9).c_str()); text_ball9 = SDL_CreateTextureFromSurface(renderer, surf_ball9);

	surf_menu		= IMG_Load((src_dir + src_menu).c_str());		text_menu		= SDL_CreateTextureFromSurface(renderer, surf_menu);
	surf_cl			= IMG_Load((src_dir + src_cl).c_str());			text_cl			= SDL_CreateTextureFromSurface(renderer, surf_cl);
	surf_clb		= IMG_Load((src_dir + src_clb).c_str());		text_clb		= SDL_CreateTextureFromSurface(renderer, surf_clb);
	surf_sp			= IMG_Load((src_dir + src_sp).c_str());			text_sp			= SDL_CreateTextureFromSurface(renderer, surf_sp);
	surf_spb		= IMG_Load((src_dir + src_spb).c_str());		text_spb		= SDL_CreateTextureFromSurface(renderer, surf_spb);
	surf_modes		= IMG_Load((src_dir + src_modes).c_str());		text_modes		= SDL_CreateTextureFromSurface(renderer, surf_modes);
	surf_records	= IMG_Load((src_dir + src_records).c_str());	text_records	= SDL_CreateTextureFromSurface(renderer, surf_records);
	surf_digits		= IMG_Load((src_dir + src_digits).c_str());		text_digits		= SDL_CreateTextureFromSurface(renderer, surf_digits);
	surf_outline	= IMG_Load((src_dir + src_outline).c_str());	text_outline	= SDL_CreateTextureFromSurface(renderer, surf_outline);

	getRecords();

	menu();

	return 0;
	
}

