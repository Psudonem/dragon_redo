struct sdlPointers{
	SDL_Window *window;
	SDL_Renderer *renderer;
	TTF_Font* Sans;

	SDL_Surface* titleSurface; 
	SDL_Texture* titleTexture;
	SDL_Rect titleRect;
};

struct sdlPointers sdlContainer;
void drawrect(int x, int y, int w, int h);
void drawrect(int x, int y, int w, int h){
	SDL_Rect rec ={x,y,w,h};
	SDL_RenderDrawRect(sdlContainer.renderer, &rec);
}