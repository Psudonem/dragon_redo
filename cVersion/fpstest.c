#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <inttypes.h>

#ifdef __TINYC__
    #undef main
#endif
static const int width = 800;
static const int height = 600;

void gameLoop();

uint32_t start,end;// = SDL_GetTicks();

int main(){
	SDL_Window *window = SDL_CreateWindow("Hello, SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);    


 bool running = true;
    SDL_Event event;
    while(running) {
    	while(SDL_PollEvent(&event)) {
    		if(event.type == SDL_QUIT) {
                running = false;
            }
    	}    	
    	start = SDL_GetTicks();
    	gameLoop();
    	end = SDL_GetTicks();
    	printf("%" PRIu32 "\n",end-start);
    	SDL_RenderClear(renderer);
    	SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();



	
	

}

void gameLoop(){
}