#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2_Image/SDL_image.h>
#include <stdbool.h>
#include <inttypes.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>


#include "screen1.c";

#include "easyG.c";
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


struct sdlColors{
	SDL_Color white;
};


//int map[50][50];

struct enemy enemies[50][50];

struct gameType game;
struct sdlColors colors;
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
void enemyRun(int x, int y);
void keyInputTitle(const char *inVal);
void keyInputGamePlay(const char *inVal);
int randInt(int rmin, int rmax);

void renderMap();

void findPlayer();// find the player on the map;
void loadEnemies();// find and load all enemies;

// Get a random number from 0 to 255
int randInt(int rmin, int rmax) {
    return rand() % rmax + rmin;
}

// Window dimensions
static const int width = 832;
static const int height = 520;

const int SCREEN_FPS = 60;

float floor();
SDL_Texture* bricTex;
SDL_Texture* dragTex;
SDL_Texture* moneyTex;
SDL_Texture* doorTex;
SDL_Texture* heroTex;
SDL_Texture* nexTex;

int main(){
	
	// this is the C port of the dragon savior engine
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	sdlContainer.window = SDL_CreateWindow("Dragon Savior", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    sdlContainer.renderer = SDL_CreateRenderer(sdlContainer.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);    
	
	//SDL_Surface* bricksIMG = SDL_LoadIMG("bricks.png");


	SDL_Surface* optimizedSurface = NULL;
	// load bricks sprite
	
	SDL_Surface* loadedSurface = IMG_Load("bricks.png");
		
	bricTex = SDL_CreateTextureFromSurface(sdlContainer.renderer, loadedSurface);
	//--------------

	// load dragon sprite
	loadedSurface = IMG_Load("dragon.png");
	dragTex = SDL_CreateTextureFromSurface(sdlContainer.renderer, loadedSurface);
	//--------------
	
	// load money sprite
	loadedSurface = IMG_Load("money.png");
	moneyTex = SDL_CreateTextureFromSurface(sdlContainer.renderer, loadedSurface);
	//--------------
	
	// load door sprite
	loadedSurface = IMG_Load("door.png");
	doorTex = SDL_CreateTextureFromSurface(sdlContainer.renderer, loadedSurface);
	//--------------
	
	// load hero sprite
	loadedSurface = IMG_Load("hero.png");
	heroTex = SDL_CreateTextureFromSurface(sdlContainer.renderer, loadedSurface);
	//--------------
	// load next sprite
	loadedSurface = IMG_Load("next.png");
	nexTex = SDL_CreateTextureFromSurface(sdlContainer.renderer, loadedSurface);
	//--------------


	// wipe enemy array
	for(int y = 0;y<50;y++){
		for(int x=0;x<50;x++){
			enemies[x][y].alive = 0;
			enemies[x][y].ttl = 0;
			
		}
	}
	//---------------


	//SDL_Rect titleRect; //create a rect
	


	SDL_SetRenderDrawColor(sdlContainer.renderer, 0, 0, 0, 255);

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
			
			
			gameLoop();
            if (event.type == SDL_KEYDOWN){
            	switch(game.state){
            		case 0:
            			keyInputTitle(SDL_GetKeyName(event.key.keysym.sym));
					case 2:
						keyInputGamePlay(SDL_GetKeyName(event.key.keysym.sym));
						
            	}
            	printf("button pressed: %s\n",SDL_GetKeyName(event.key.keysym.sym));
				if(event.key.keysym.sym==13){
					running = false;}
            }

    	}    

    	Uint64 start = SDL_GetPerformanceCounter();	
    	
    	
    	SDL_RenderClear(sdlContainer.renderer);
		gameLoop(sdlContainer.renderer);
		

    	SDL_RenderPresent(sdlContainer.renderer);
    	Uint64 end = SDL_GetPerformanceCounter();

    	float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
    	SDL_Delay(floor(16.666f - elapsedMS));
    }


    SDL_DestroyTexture(sdlContainer.titleTexture);
	SDL_FreeSurface(sdlContainer.titleSurface);


    SDL_DestroyRenderer(sdlContainer.renderer);
    SDL_DestroyWindow(sdlContainer.window);


    TTF_CloseFont(sdlContainer.Sans);
    TTF_Quit();
    SDL_Quit();




	return 0;
}


void renderTitle(){
	SDL_RenderCopy(sdlContainer.renderer, sdlContainer.titleTexture, NULL, &sdlContainer.titleRect);//, NULL, &Message_rect);
	
}
void keyInputTitle(const char *inVal){

	printf("button for title inputted %s\n",inVal);
	if(strcmp(inVal, "P")==0){// if P is pressed
		game.state=1;
	}else if(strcmp(inVal, "T")==0){
		game.state=9;}
}

void keyInputGamePlay(const char *inVal){
	int dx,dy;
	dx = 0;
	dy = 0;
	//printf("button for title inputted %s\n",inVal);
	if(strcmp(inVal, "W")==0){// if W is pressed
		dy-=1;
	}
	else if(strcmp(inVal, "S")==0){// if S is pressed
		dy+=1;
	}
	else if(strcmp(inVal, "D")==0){// if D is pressed
		dx+=1;
	}
	else if(strcmp(inVal, "A")==0){// if A is pressed
		dx-=1;
	}
	
	if(map[(py+dy)*50 + (px+dx)]==3){
		map[(py+dy)*50 + (px+dx)]=0;
	}
	
	if(map[(py+dy)*50 + (px+dx)]==0){
		map[py*50 + px]=0;
		px+=dx;
		py+=dy;
		map[(py)*50 + (px)]=4;
	}
	
	
	camx = px-7;
	camy = py-5;
}


void runTitle(){
	renderTitle();}

void setupGame(){
	px = 0;
	py = 0;
	findPlayer();
	loadEnemies();
}


void enemyRun(int x, int y){
	int ex = x;
	int ey = y;
	int dx =  randInt(-1,2);//(rand() % 3)-1;
	int dy = 0;
	if(dx==0){
		dy = randInt(-1,2);//(rand() % 3)-1;
	}
	
	printf("\n ~~~ %d\n",enemies[ex][ey].ttl);
	if(enemies[ex][ey].ttl==0){
		if(map[(ey+dy)*50 + (ex+dx)] == 0 && enemies[ex+dx][ey+dy].alive==0){
			enemies[ex+dx][ey+dy].alive = 1;
			enemies[ex+dx][ey+dy].ttl = (rand() % 10)+25;
			enemies[ex][ey].alive=0;
			enemies[ex][ey].ttl=0;
		}
	}else{
		enemies[ex][ey].ttl--;
	}
}
void loadEnemies(){
	int m;
	for(int y= 0; y<50;y++){
		for(int x=0;x<50;x++){
			m = (int)(map[y*50+x]);
			if(m==7){
				enemies[x][y].alive = 1;
				enemies[x][y].ttl = 10;
				map[y*50+x]=0;
			}
		}
	}
}
void findPlayer(){
	int m;
	for(int y= 0; y<50;y++){
		for(int x=0;x<50;x++){
			m = (int)(map[y*50+x]);
			if(m==4){
				camx = x-7;
				camy = y-5;
				px = x;
				py = y;
			}
		}
	}
}


void renderMap(){
	int m;
	int e;
	for(int y=0;y<11;y++){
		for(int x=0;x<15;x++){
			if((x + camx >= 0) && (x + camx < 50) && (y + camy >= 0) && (y + camy < 50)){
				m=0;e=0;
				m=map[(y+camy)*50 + (x+camx)];
				e =  enemies[x + camx][(y + camy)].alive;
				
					SDL_Rect tempRec ={x*32,y*32,32,32};
				 switch(m){
					case 1:// brick
						SDL_SetRenderDrawColor(sdlContainer.renderer, 255, 0, 0, 255);
						SDL_RenderCopy(sdlContainer.renderer, bricTex, NULL, &tempRec);
						//SDL_RenderDrawRect(sdlContainer.renderer, &bric);
						SDL_SetRenderDrawColor(sdlContainer.renderer, 0, 0, 0, 255);
						break;
					case 4://dragon
						SDL_SetRenderDrawColor(sdlContainer.renderer, 100, 255, 0, 255);
						SDL_RenderCopy(sdlContainer.renderer, dragTex, NULL, &tempRec);
						SDL_SetRenderDrawColor(sdlContainer.renderer, 0, 0, 0, 255);
						break;
					case 2://money
						SDL_SetRenderDrawColor(sdlContainer.renderer, 100, 255, 0, 255);
						SDL_RenderCopy(sdlContainer.renderer, moneyTex, NULL, &tempRec);
						SDL_SetRenderDrawColor(sdlContainer.renderer, 0, 0, 0, 255);
						break;
					case 3://door
						SDL_SetRenderDrawColor(sdlContainer.renderer, 100, 255, 0, 255);
						SDL_RenderCopy(sdlContainer.renderer, doorTex, NULL, &tempRec);
						SDL_SetRenderDrawColor(sdlContainer.renderer, 0, 0, 0, 255);
						break;
					case 7://hero
						SDL_SetRenderDrawColor(sdlContainer.renderer, 100, 255, 0, 255);
						SDL_RenderCopy(sdlContainer.renderer, heroTex, NULL, &tempRec);
						SDL_SetRenderDrawColor(sdlContainer.renderer, 0, 0, 0, 255);
						break;
					case 9://next
						SDL_SetRenderDrawColor(sdlContainer.renderer, 100, 255, 0, 255);
						SDL_RenderCopy(sdlContainer.renderer, nexTex, NULL, &tempRec);
						SDL_SetRenderDrawColor(sdlContainer.renderer, 0, 0, 0, 255);
						break;
				 }
				
				if(e>0){
					SDL_SetRenderDrawColor(sdlContainer.renderer, 100, 255, 0, 255);
					SDL_RenderCopy(sdlContainer.renderer, heroTex, NULL, &tempRec);
					SDL_SetRenderDrawColor(sdlContainer.renderer, 0, 0, 0, 255);
					enemyRun(x+camx,y+camy);
				}
				
				
				
				
			}
		}
	}
	
	SDL_SetRenderDrawColor(sdlContainer.renderer, 100, 255, 255, 255);
	drawrect(0,0,480,352);
	SDL_SetRenderDrawColor(sdlContainer.renderer, 0, 0, 0, 255);
}
void gamePlay(){
	printf("X: %d\nY: %d\n",px,py);
	
	camx = px-7;
	camy = py-5;
	renderMap();
	/*SDL_SetRenderDrawColor(sdlContainer.renderer, 0, 200, 0, 255);
	
	SDL_Rect location = {px,py,32,32}; 
	SDL_RenderDrawRect(sdlContainer.renderer, &location);
	SDL_RenderDrawPoint(sdlContainer.renderer, px, py);
	SDL_SetRenderDrawColor(sdlContainer.renderer, 0, 0, 0, 255);*/
	
}

void gameLoop(){

	/*
		CURRENT: game state function structure
		main loop:
			get input
			handle input

			handle in-engine events
			draw

		OLD: game state function structure
			- render screen
				- sometimes it is perferrable to handle events in this stage
			- get input (if needed)
			- handle events (if needed)
	*/
	switch(game.state){
		case 0:
			//printf("title\n\n");
			runTitle();
			break;
		case 1:
			printf("setting up game\n\n");
			setupGame();
			game.state++;
			break;
		case 2:
			printf("game play\n\n");
			gamePlay();
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
		case 9:
			printf("displaying tutorial slide\n\n");
			
			break;
	}
}





void load_all_sounds(){
	printf("this is where we load all sounds\n");}
void load_all_graphics(){
	printf("this is where we load all graphics\n");


	// Load and crate the title screen font
	sdlContainer.Sans = TTF_OpenFont("arial.ttf", 24);
	colors.white.r=255;
	colors.white.g=255;
	colors.white.b=255;
	colors.white.a=0;

	sdlContainer.titleSurface = TTF_RenderText_Solid(sdlContainer.Sans, "DRAGON SAVIOR TITLE. P = Play. T = Tutorial", colors.white);
	sdlContainer.titleTexture = SDL_CreateTextureFromSurface(sdlContainer.renderer, sdlContainer.titleSurface);



	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(sdlContainer.titleTexture, NULL, NULL, &texW, &texH);
	//sdlContainer.titleRect= { 0, 0, texW, texH };
	sdlContainer.titleRect.x = 0;  //controls the rect's x coordinate 
	sdlContainer.titleRect.y = 0; // controls the rect's y coordinte
	sdlContainer.titleRect.w = texW; // controls the width of the rect
	sdlContainer.titleRect.h = texH; // controls the height of the rect
}
void kill_all_enemies(){
    for(x = 0;x<=49;x++){
    	for(y = 0;y<=49;y++){
			enemies[x][y].alive = 0;}}}