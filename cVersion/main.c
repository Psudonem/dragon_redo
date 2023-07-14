#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <inttypes.h>
#include <SDL2/SDL_ttf.h>
// Normally SDL2 will redefine the main entry point of the program for Windows applications
// this doesn't seem to play nice with TCC, so we just undefine the redefinition
#ifdef __TINYC__
    #undef main
#endif



struct enemy{
	int ttl;
	int alive;
};

struct flame{
	int xdir;
    int ydir;
    int status;
    int ttl;
    int power;
};

struct gameType{
	int state;
	int money;
	int enemies;
	int power;
	int hp;
	int keys;
	int level;
};

//struct enemy E;

int map[50][50];

struct gameType game;

struct enemy enemies[50][50];
struct flame flames[50][50]; 
struct flame projectiles[50][50];
struct flame flamespikes[50][50] ;


int camx,camy, px, py, dx, dy;/**/

int x,y;

void kill_all_enemies();
void load_all_sounds();
void load_all_graphics();
void gameLoop();
int randInt(int rmin, int rmax);

// Get a random number from 0 to 255
int randInt(int rmin, int rmax) {
    return rand() % rmax + rmin;
}

// Window dimensions
static const int width = 800;
static const int height = 600;

const int SCREEN_FPS = 60;


float floor();


int main(){
	// this is the C port of the dragon savior engine

	TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);

	SDL_Window *window = SDL_CreateWindow("Hello, SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);    
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);


	kill_all_enemies();
	load_all_sounds();
	load_all_graphics();
	
	game.state = 0;/**/

	bool running = true;

	SDL_Event event;

    while(running) {
    	while(SDL_PollEvent(&event)) {
    		if(event.type == SDL_QUIT) {
                running = false;
            }
    	}    

    	Uint64 start = SDL_GetPerformanceCounter();	
    	gameLoop();
    	SDL_RenderClear(renderer);
    	SDL_RenderPresent(renderer);
    	Uint64 end = SDL_GetPerformanceCounter();

    	float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
    	SDL_Delay(floor(16.666f - elapsedMS));
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();




	return 0;
}

void renderTitle(){

}
void runTitle(){
	renderTitle();
	//renderTitle
	//getInputAndHandleState_Title
}

void gameLoop(){

	/*
		game state function structure
			- render screen
				- sometimes it is perferrable to handle events in this stage
			- get input (if needed)
			- handle events (if needed)
	*/
	switch(game.state){
		case 0:
			printf("title\n\n");
			runTitle();
			break;
		case 1:
			printf("setting up game\n\n");
			game.state++;
			break;
		case 2:
			printf("game play\n\n");
			break;
		case 3:
			printf("switching levels....\n\n");
			game.state--;
			break;
		case 4:
			printf("game over\n\n");
			break;
		case 5:
			printf("you win\n\n");
			break;
		case 6:
			printf("returing to title\n\n");
			game.state = 0;
			break;
		case 7:
			printf("restarting game\n\n");
			game.state = 1;
			break;
		case 8:
			printf("pause menu\n\n");
			game.state = 1;
			break;
	}
}

void load_all_sounds(){
	printf("this is where we load all sounds\n");
}
void load_all_graphics(){
	printf("this is where we load all graphics\n");
}
void kill_all_enemies(){
    for(x = 0;x<=49;x++){
    	for(y = 0;y<=49;y++){
			enemies[x][y].alive = 0;
    	}
    }
}
