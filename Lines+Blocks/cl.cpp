#include "cl.hpp"
#include "Main.hpp"
#include "Menu.hpp"
#include "Records.hpp"
#include "Digits.hpp"

#include <Windows.h>
#include <chrono>
#include <cstdlib>
#include <cstdio>
#include <stdio.h>
#include <iostream>

static struct ball {
	int x;
	int y;
};

struct way {
	int moves[80];
};

static ball selectedBall;

static int field[9][9];
static int points;

static void destroyLines() {

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 9; j++) {
			int lenght = 1;
			int color = field[i][j];
			if (color == 0) continue;
			while (i + lenght != 9 && field[i + lenght][j] == color) {
				lenght++;
			}
			if (lenght >= 5) {
				for (int k = i; k < i + lenght; k++) {
					field[k][j] = 0;
				}
				switch (lenght)
				{
				case 5: points += 10; break;
				case 6: points += 12; break;
				case 7: points += 18; break;
				case 8: points += 28; break;
				case 9: points += 42; break;
				}
			}
		}
	}

	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < 9; i++) {
			int lenght = 1;
			int color = field[i][j];
			if (color == 0) continue;
			while (j + lenght != 9 && field[i][j + lenght] == color) {
				lenght++;
			}
			if (lenght >= 5) {
				for (int k = j; k < j + lenght; k++) {
					field[i][k] = 0;
				}
				switch (lenght)
				{
				case 5: points += 10; break;
				case 6: points += 12; break;
				case 7: points += 18; break;
				case 8: points += 28; break;
				case 9: points += 42; break;
				}
			}
		}
	}
}

static void drawOutline() {
	if (selectedBall.x != -1) drawTexture(selectedBall.x * 64, selectedBall.y * 64, 64, 64, text_outline, renderer);
}


static void drawBalls() {
	SDL_Texture* t = NULL;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (field[j][i] == 0)continue;
			switch (field[j][i]) {
			case 1:  t = text_ball1; break;
			case 2:  t = text_ball2; break;
			case 3:  t = text_ball3; break;
			case 4:  t = text_ball4; break;
			case 5:  t = text_ball5; break;
			case 6:  t = text_ball6; break;
			case 7:  t = text_ball7; break;
			case 8:  t = text_ball8; break;
			case 9:  t = text_ball9; break;
			}
			drawTexture(64 * j, 64 * i, 64, 64, t, renderer);
		}
	}
}


static bool isClearWay(int x1, int y1, int x2, int y2) {
	if (field[x2][y2] != 0) return false;
	int array[9][9];
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (field[i][j] != 0)array[i][j] = -1;
			else array[i][j] = 0;
		}
	}
	array[x1][y1] = 1;
	int iter = 1;
	while (array[x2][y2] == 0) {
		int k = 0;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (array[i][j] == iter) {
					if ((i != 0) && (array[i - 1][j] == 0)) { array[i - 1][j] = iter + 1; k++; }
					if ((j != 0) && (array[i][j - 1] == 0)) { array[i][j - 1] = iter + 1; k++; }
					if ((i != 8) && (array[i + 1][j] == 0)) { array[i + 1][j] = iter + 1; k++; }
					if ((j != 8) && (array[i][j + 1] == 0)) { array[i][j + 1] = iter + 1; k++; }
				}
			}
		}
		if (k == 0) return false;
		iter++;
	};
	return true;
}

static void moveBall(int x1, int y1, int x2, int y2, int color) {
	const long long moveTime = 150;
	long long ts1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() < ts1 + moveTime) {
		
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				exit(0);
			}
		}
		
		SDL_RenderClear(renderer);
		drawTexture(0, 0, width, height, text_cl, renderer);

		SDL_Texture* t = NULL;
		switch (color) {
			case 1:  t = text_ball1; break;
			case 2:  t = text_ball2; break;
			case 3:  t = text_ball3; break;
			case 4:  t = text_ball4; break;
			case 5:  t = text_ball5; break;
			case 6:  t = text_ball6; break;
			case 7:  t = text_ball7; break;
			case 8:  t = text_ball8; break;
			case 9:  t = text_ball9; break;
		}
		drawTexture(
			64 * ((long double)x1 + ((long double)x2 - x1) * (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - ts1) / moveTime),
			64 * ((long double)y1 + ((long double)y2 - y1) * (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - ts1) / moveTime),
			64, 64, t, renderer);

		drawNumber(662, 447, 16, 9, points);
		drawNumber(692, 474, 16, 9, rec_cl);
		drawBalls();
		//drawOutline();
		SDL_RenderPresent(renderer);
	}
}

static void animateAndMove(int x1, int y1, int x2, int y2) {

	int array[9][9];
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (field[i][j] != 0)array[i][j] = -1;
			else array[i][j] = 0;
		}
	}
	array[x2][y2] = 1;
	array[x1][y1] = 0;
	int iter = 1;
	while (array[x1][y1] == 0) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (array[i][j] == iter) {
					if ((i != 0) && (array[i - 1][j] == 0)) { array[i - 1][j] = iter + 1;}
					if ((j != 0) && (array[i][j - 1] == 0)) { array[i][j - 1] = iter + 1;}
					if ((i != 8) && (array[i + 1][j] == 0)) { array[i + 1][j] = iter + 1;}
					if ((j != 8) && (array[i][j + 1] == 0)) { array[i][j + 1] = iter + 1;}
				}
			}
		}
		iter++;
	};

	int i = x1;
	int j = y1;
	while (iter != 1) {
		if (i != 0 && (array[i - 1][j] == iter - 1)){
			int color = field[i][j];
			field[i][j] = 0;
			moveBall(i, j, i - 1, j, color);
			field[i - 1][j] = color;
			i--;
			iter--;
		}
		else if (j != 0 && (array[i][j - 1] == iter - 1)) {
			int color = field[i][j];
			field[i][j] = 0;
			moveBall(i, j, i, j - 1, color);
			field[i][j - 1] = color;
			j--;
			iter--;
		}
		else if (i != 8 && (array[i + 1][j] == iter - 1)) {
			
			
			int color = field[i][j];
			field[i][j] = 0;
			moveBall(i, j, i + 1, j, color);
			field[i + 1][j] = color;
			i++;
			iter--;
		}
		else if (j != 8 && (array[i][j + 1] == iter - 1)) {


			int color = field[i][j];
			field[i][j] = 0;
			moveBall(i, j, i, j + 1, color);
			field[i][j + 1] = color;
			j++;
			iter--;

		}
	}
}

static void spawnBalls() {
	int k = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (field[i][j] == 0)k++;
		}
	}
	if (k < 3)return;
	srand(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
	int x, y;
	for (int i = 0; i < 3; i++) {
		x = rand() % 9;
		y = rand() % 9;
		if (field[x][y] == 0) {
			field[x][y] = rand()%9+1;
		}
		else {
			i--;
		}
		
	}
}


static bool isTurn(int x, int y) {
	int x1 = 0;
	int y1 = 0;
	int x2 = 575;
	int y2 = 575;
	if ((x >= x1) && (x <= x2) && (y >= y1) && (y <= y2)) return true;
	return false;
}

static bool isPressedMenu(int x, int y) {
	int x1 = 638;
	int y1 = 180;
	int x2 = 842;
	int y2 = 235;
	if ((x >= x1) && (x <= x2) && (y >= y1) && (y <= y2)) return true;
	return false;

}

static bool isPressedRestart(int x, int y) {
	int x1 = 638;
	int y1 = 260;
	int x2 = 842;
	int y2 = 315;
	if ((x >= x1) && (x <= x2) && (y >= y1) && (y <= y2)) return true;
	return false;
}

void cl() {
	selectedBall.x = -1;
	selectedBall.y = -1;
	points = 0;

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			field[i][j] = 0;
		}
	}

	spawnBalls();




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
				int tx = e.button.x, ty = e.button.y;
				if (isPressedMenu(tx, ty))menu();
				else if (isPressedRestart(tx, ty)) {
					
					points = 0;
					for (int i = 0; i < 9; i++) {
						for (int j = 0; j < 9; j++) {
							field[i][j] = 0;
						}
					}
					selectedBall.x = -1;
					selectedBall.y = -1;
					spawnBalls();
				}
				else if (isTurn(tx, ty)) {
					if (selectedBall.x == -1) {
						if (field[tx / 64][ty / 64] != 0) {
							selectedBall.x = tx / 64;
							selectedBall.y = ty / 64;
						}
					}
					else if ((selectedBall.x == tx / 64) && (selectedBall.y == ty / 64)) {
						selectedBall.x = -1;
						selectedBall.y = -1;
					}
					else if (isClearWay(selectedBall.x, selectedBall.y, tx / 64, ty / 64)) {
						animateAndMove(selectedBall.x, selectedBall.y, tx / 64, ty / 64);
						selectedBall.x = -1;
						selectedBall.y = -1;
						spawnBalls();
					}
				}
			}
		}

		destroyLines();
		if (points > rec_cl) { rec_cl = points; setRecords(rec_cl, rec_clb, rec_sp, rec_spb); }

		SDL_RenderClear(renderer);
		drawTexture(0, 0, width, height, text_cl, renderer);
		drawNumber(662, 447, 16, 9, points);
		drawNumber(692, 474, 16, 9, rec_cl);

		drawBalls();

		drawOutline();

		SDL_RenderPresent(renderer);
	}

}