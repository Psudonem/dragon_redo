#include <stdio.h>

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


int camx,camy, px, py, dx, dy;

int x,y;
void kill_all_enemies();
void load_all_sounds();
void load_all_graphics();


int main(){
	// this is the C port of the dragon savior engine. no graphics yet.

	kill_all_enemies();
	load_all_sounds();
	load_all_graphics();
	
	game.state = 0;

	return 0;
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
