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

struct sdlPointers{
	SDL_Window *window;
	SDL_Renderer *renderer;
	TTF_Font* Sans;
	
};

int map[50][50];

struct gameType game;

struct sdlPointers sdlContainer;

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
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	sdlContainer.window = SDL_CreateWindow("Dragon Savior", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    sdlContainer.renderer = SDL_CreateRenderer(sdlContainer.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);    
	

	sdlContainer.Sans = TTF_OpenFont("arial.ttf", 24);
	SDL_Color White = {255, 255, 255};

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(sdlContainer.Sans, "DRAGON SAVIOR", White);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(sdlContainer.renderer, surfaceMessage);

	SDL_Rect Message_rect; //create a rect
Message_rect.x = 100;  //controls the rect's x coordinate 
Message_rect.y = 100; // controls the rect's y coordinte
Message_rect.w = 100; // controls the width of the rect
Message_rect.h = 100; // controls the height of the rect


	SDL_SetRenderDrawColor(sdlContainer.renderer, 0, 100, 0, 255);

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
    	
    	
    	SDL_RenderClear(sdlContainer.renderer);
		gameLoop(sdlContainer.renderer);
		SDL_RenderCopy(sdlContainer.renderer, Message, NULL, NULL);//, NULL, &Message_rect);

    	SDL_RenderPresent(sdlContainer.renderer);
    	Uint64 end = SDL_GetPerformanceCounter();

    	float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
    	SDL_Delay(floor(16.666f - elapsedMS));
    }


    SDL_DestroyTexture(Message);
	SDL_FreeSurface(surfaceMessage);


    SDL_DestroyRenderer(sdlContainer.renderer);
    SDL_DestroyWindow(sdlContainer.window);


    TTF_CloseFont(sdlContainer.Sans);
    TTF_Quit();
    SDL_Quit();




	return 0;
}

void renderTitle(){
	//SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
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
