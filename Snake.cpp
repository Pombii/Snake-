#include "SDL.h"
#include "SDL_image.h"
#include <SDL_timer.h> 
#include <iostream>
#include <ctime>
#include <vector>
using namespace std;

#include <algorithm>


int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {										//Starts the SDL library to 0
		cout << "error initializing SDL: %s\n" << SDL_GetError() << endl;
	}

	bool flag;
	int snekw = 15;
	int snekh = 15;
	int startx = 390;
	int starty = 390;
	int prev_x = 0;
	int prev_y = 0;
	int diflag = 0;
	int frameTime;
	const int FPS = 20;
	const int frameDelay = 1500 / FPS;
	int tailsize = 0;
	int count = 0;

	Uint32 framestart;
	SDL_Rect playerhead = { startx, starty, snekw, snekh };
	SDL_Rect fruit = { 435, 255, snekw, snekh };
	SDL_Window *mywin; 
	SDL_Renderer* rend;
	SDL_Event userevent;
	vector<SDL_Rect> tail_vec;
	

	int next = 0;


	mywin = SDL_CreateWindow("SNEK GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 512, SDL_WINDOW_RESIZABLE);
	rend = SDL_CreateRenderer(mywin, -1, SDL_RENDERER_ACCELERATED);
	
	tail_vec.push_back(playerhead);


	while (true) {
		
		framestart = SDL_GetTicks();

		SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);						//Sets the background arena color to black
		SDL_RenderClear(rend);

		SDL_SetRenderDrawColor(rend, 0, 0, 255, 255);					//Create the boundries of the arena
		SDL_RenderDrawLine(rend, 10, 10, 1010, 10);
		SDL_RenderDrawLine(rend, 10, 10, 10, 500);
		SDL_RenderDrawLine(rend, 1010, 10, 1010, 500);
		SDL_RenderDrawLine(rend, 10, 500, 1010, 500);

		SDL_SetRenderDrawColor(rend, fruit.x, fruit.y, rand() % 256, 255);			//Creates a fruit at a random location of random flashing color
		SDL_RenderFillRect(rend, &fruit);

		SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);								//Creates your snake
		SDL_RenderFillRect(rend, &tail_vec[0]);
	

		SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);								//Creates your tails

		
		if (SDL_HasIntersection(&tail_vec[0], &fruit)) {
			tail_vec.push_back(SDL_Rect());
			flag = true;
			next++;
			count = next;
			do {																					//at a random location that aline with the graphics of the snake	
				fruit.x = (rand() % 1009);
				fruit.y = (rand() % 485);

				if ((fruit.x % 15 == 0) && (fruit.y % 15 == 0)) {
					flag = false;
				}
			} while (flag == true);
		}
		

		
		if (SDL_PollEvent(&userevent)) {
			if (userevent.type == SDL_QUIT)
				exit(0);
			if (userevent.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				exit(0);
			if (userevent.type == SDL_KEYDOWN) {											//Funtions of the snake if arrow keys are pressed

				if ((userevent.key.keysym.scancode == SDL_SCANCODE_UP) && (diflag != 2)) {
					diflag = 1;
				}
				if ((userevent.key.keysym.scancode == SDL_SCANCODE_DOWN) && (diflag != 1)) {
					diflag = 2;
				}
				if ((userevent.key.keysym.scancode == SDL_SCANCODE_LEFT) && (diflag != 4)) {
					diflag = 3;
				}
				if ((userevent.key.keysym.scancode == SDL_SCANCODE_RIGHT) && (diflag != 3)) {
					diflag = 4;
				}
			}
		}


		switch (diflag)
		{
		case 1:
			tail_vec[0].y -= snekh;										//Up
			break;

		case 2:
			tail_vec[0].y += snekh;										//Down
			break;

		case 3:
			tail_vec[0].x -= snekw;										//Left
			break;

		case 4:
			tail_vec[0].x += snekw;										//Right
			break;

		default:
			tail_vec[0].x += snekw;										//Right
			break;
		}

		

		if (tail_vec.size() > 1){
			//count = next;
			tail_vec[count].x = tail_vec[count - 1].x;
			tail_vec[count].y = tail_vec[count - 1].y;
			tail_vec[count].h = 15;
			tail_vec[count].w = 15;
			SDL_RenderFillRect(rend, &tail_vec[count]);
			count--;


	
		}

		SDL_RenderPresent(rend);

			frameTime = SDL_GetTicks() - framestart;
			if (frameDelay > frameTime) {
				SDL_Delay(frameDelay - frameTime);
			}

	}

	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(mywin);
	SDL_Quit();

	return 0;
}
