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
float floor();

//uint32_t start,end;// = SDL_GetTicks();


int frame;
int main(){
	frame = 0;
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

    	//https://thenumb.at/cpp-course/sdl2/08/08.html	
    	Uint64 start = SDL_GetPerformanceCounter();
    	gameLoop();
    	Uint64 end = SDL_GetPerformanceCounter();

    	float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
    	SDL_Delay(floor(16.666f - elapsedMS));


    	SDL_RenderClear(renderer);
    	SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();



	
	

}

void gameLoop(){
	for(int i=0;i<10000;i++){}
	
	frame++;
	if(frame%60==0)printf("frame %d\n",frame/60);
}