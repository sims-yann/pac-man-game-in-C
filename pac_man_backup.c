#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>	//to import images
#include <time.h>
#include <SDL_ttf.h>	//to import fonts
#include <SDL_mixer.h>	//to import sounds


#define WINDOWSIZE_W 800 //window size width
#define WINDOWSIZE_H 500 //window size height
#define PATH_NUM 46

SDL_Window* window;		//parameters controlling window
SDL_Renderer* render;
SDL_Rect pacsize;	//small brouillon
SDL_FRect wall[54];	//parameters controlling walls
SDL_Texture* dead_ghosttext;	//dead ghost img
SDL_FRect path_rect[PATH_NUM];

//parametsr of the data type pac man
typedef struct {
	clock_t lastTime;
	int frame;
	SDL_Texture* textures[8];
	SDL_FRect rect;
	SDL_bool faf;
} PacMan;

//parameters for data type ghosts
typedef struct {
	SDL_FRect rect;
	SDL_Texture *text;
	SDL_bool faf;
} phantom;

//parameters for coins data type
typedef struct{
	SDL_bool visited;
	SDL_FRect rect;
	SDL_Texture *texture;
}coins;


typedef struct {
    SDL_Rect rect;
    const char *text;
} MenuItem;


typedef enum {
    STATE_MENU,
    STATE_GAME,
    STATE_EXIT
} GameState;

PacMan newPacMan(int size, int posx, int posy);		//fxn controlling pac man parameters
void drawPacMan(PacMan* p, double pac_rot);			//fxn to control pac frame rate
void phant_init();									//load ghost pictures
void draw_ghost(PacMan pac_man);					//display good or dead ghosts
void drawMenu(SDL_Renderer *renderer, TTF_Font *font, MenuItem menuItems[], int itemCount, int selectedItem);  	//drawing the menu

phantom ghost[4];		//initialising ghosts

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);		//initialising sdl
	TTF_Init();
	Mix_Init(MIX_INIT_MP3);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	
//	FILE *carre, *carre1;
//	carre = fopen("carre.txt", "a+");
//	carre1 = fopen("carre1.txt", "a+");
//	int i = 0;
//	while (fscanf(carre, "%d %d %d %d\n", &pacsize.x, &pacsize.y, &pacsize.w, &pacsize.h) != EOF) {		//read elements till End Of File
//		fprintf_s(carre1, "path_rect[%d]=(SDL_FRect){%d, %d, %d, %d};\n", i, pacsize.x, pacsize.y, pacsize.w, pacsize.h);
//		i += 1;
//	}



//create redimensionalisable window
	window = SDL_CreateWindow("pac boy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOWSIZE_W, WINDOWSIZE_H, SDL_WINDOW_FULLSCREEN_DESKTOP);
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(render, 0, 0, 0, SDL_ALPHA_OPAQUE);
//	SDL_RenderDrawPoint(render, 100, 100);
//	SDL_RenderDrawLine(render, 100, 300, 800, 300);


//define pac live img
	SDL_Surface *vie_img;
	SDL_Texture *pac_vie;
	SDL_Rect vie_rect;
	vie_img=IMG_Load("pac_vie.png");
	pac_vie=SDL_CreateTextureFromSurface(render, vie_img);
	SDL_FreeSurface(vie_img);
	vie_rect= (SDL_Rect) {900, 150, 130, 75};
	
//define parameters for background
	SDL_FRect background;
	background.x = 0;
	background.y = 0;
	background.h = WINDOWSIZE_H;
	background.w = WINDOWSIZE_W;

	//define the parameters for the brouillon
	pacsize.x = 150;
	pacsize.y = 150;
	pacsize.h = 25;
	pacsize.w = 25;

	//defining pellet paths
	path_rect[0]=(SDL_FRect){183, 96, 289, 37};
	path_rect[1]=(SDL_FRect){495, 96, 286, 37};
	path_rect[2]=(SDL_FRect){627, 132, 46, 36};
	path_rect[3]=(SDL_FRect){495, 132, 46, 36};
	path_rect[4]=(SDL_FRect){294, 132, 46, 36};
	path_rect[5]=(SDL_FRect){186, 219, 110, 40};
	path_rect[6]=(SDL_FRect){363, 222, 109, 37};
	path_rect[7]=(SDL_FRect){492, 222, 115, 40};
	path_rect[8]=(SDL_FRect){363, 276, 244, 37};
	path_rect[9]=(SDL_FRect){177, 327, 229, 41};
	path_rect[10]=(SDL_FRect){561, 330, 229, 39};
	path_rect[11]=(SDL_FRect){183, 441, 292, 34};
	path_rect[12]=(SDL_FRect){495, 441, 289, 40};
	path_rect[13]=(SDL_FRect){297, 495, 376, 37};
	path_rect[14]=(SDL_FRect){696, 495, 88, 39};
	path_rect[15]=(SDL_FRect){495, 549, 112, 37};
	path_rect[16]=(SDL_FRect){360, 549, 115, 34};
	path_rect[17]=(SDL_FRect){183, 549, 157, 34};
	path_rect[18]=(SDL_FRect){183, 603, 601, 37};
	path_rect[19]=(SDL_FRect){183, 96, 289, 37};
	path_rect[20]=(SDL_FRect){495, 96, 286, 37};
	path_rect[21]=(SDL_FRect){183, 168, 598, 37};
	path_rect[22]=(SDL_FRect){183, 219, 113, 40};
	path_rect[23]=(SDL_FRect){183, 132, 46, 36};
	path_rect[24]=(SDL_FRect){294, 132, 46, 36};
	path_rect[25]=(SDL_FRect){426, 132, 46, 36};
	path_rect[26]=(SDL_FRect){495, 132, 46, 36};
	path_rect[27]=(SDL_FRect){627, 132, 46, 36};
	path_rect[28]=(SDL_FRect){735, 132, 46, 36};
	path_rect[29]=(SDL_FRect){363, 222, 109, 37};
	path_rect[30]=(SDL_FRect){492, 222, 115, 40};
	path_rect[31]=(SDL_FRect){672, 222, 109, 36};
	path_rect[32]=(SDL_FRect){363, 276, 244, 37};
	path_rect[33]=(SDL_FRect){360, 387, 247, 40};
	path_rect[34]=(SDL_FRect){696, 495, 88, 39};
	path_rect[35]=(SDL_FRect){297, 495, 376, 37};
	path_rect[36]=(SDL_FRect){183, 495, 91, 37};
	path_rect[37]=(SDL_FRect){183, 549, 157, 34};
	path_rect[38]=(SDL_FRect){360, 549, 115, 34};
	path_rect[39]=(SDL_FRect){495, 549, 112, 37};
	path_rect[40]=(SDL_FRect){627, 549, 157, 37};
	path_rect[41]=(SDL_FRect){183, 603, 601, 37};
	path_rect[42]=(SDL_FRect){297, 204, 44, 124};
	path_rect[43]=(SDL_FRect){297, 366, 44, 76};
	path_rect[44]=(SDL_FRect){630, 204, 41, 127};
	path_rect[45]=(SDL_FRect){630, 369, 43, 73};
	

	//defining walls
	wall[0] = (SDL_FRect) {
		174, 87, 618, 9
	};
	wall[1] = (SDL_FRect) {
		174, 639, 618, 9
	};
	wall[2] = (SDL_FRect) {
		174, 87, 11, 170
	};
	wall[3] = (SDL_FRect) {
		780, 87, 11, 170
	};
	wall[4] = (SDL_FRect) {
		672, 132, 67, 36
	};
	wall[5] = (SDL_FRect) {
		540, 132, 87, 36
	};
	wall[6] = (SDL_FRect) {
		339, 132, 87, 36
	};
	wall[7] = (SDL_FRect) {
		228, 132, 68, 36
	};
	wall[8] = (SDL_FRect) {
		471, 99, 25, 67
	};
	wall[9] = (SDL_FRect) {
		228, 204, 65, 15
	};
	wall[10] = (SDL_FRect) {
		405, 204, 160, 18
	};
	wall[11] = (SDL_FRect) {
		669, 204, 73, 18
	};
	wall[12] = (SDL_FRect) {
		339, 204, 24, 125
	};
	wall[13] = (SDL_FRect) {
		606, 204, 23, 126
	};
	wall[14] = (SDL_FRect) {
		471, 222, 23, 52
	};
	wall[15] = (SDL_FRect) {
		174, 258, 122, 10
	};
	wall[16] = (SDL_FRect) {
		672, 258, 122, 9
	};
	wall[17] = (SDL_FRect) {
		540, 261, 89, 16
	};
	wall[18] = (SDL_FRect) {
		339, 258, 89, 17
	};
	wall[19] = (SDL_FRect) {
		282, 258, 14, 71
	};
	wall[20] = (SDL_FRect) {
		671, 256, 17, 74
	};
	wall[21] = (SDL_FRect) {
		672, 321, 120, 8
	};
	wall[22] = (SDL_FRect) {
		174, 321, 120, 8
	};
	wall[23] = (SDL_FRect) {
		405, 312, 100, 11
	};
	wall[24] = (SDL_FRect) {
		504, 312, 59, 11
	};
	wall[25] = (SDL_FRect) {
		405, 375, 159, 13
	};
	wall[26] = (SDL_FRect) {
		405, 312, 14, 75
	};
	wall[27] = (SDL_FRect) {
		549, 312, 14, 75
	};
	wall[28] = (SDL_FRect) {
		672, 369, 14, 69
	};
	wall[29] = (SDL_FRect) {
		606, 369, 23, 69
	};
	wall[30] = (SDL_FRect) {
		339, 368, 23, 69
	};
	wall[31] = (SDL_FRect) {
		282, 367, 16, 69
	};
	wall[32] = (SDL_FRect) {
		174, 368, 124, 9
	};
	wall[33] = (SDL_FRect) {
		672, 368, 120, 9
	};
	wall[34] = (SDL_FRect) {
		405, 426, 158, 12
	};
	wall[35] = (SDL_FRect) {
		672, 432, 120, 9
	};
	wall[36] = (SDL_FRect) {
		174, 432, 122, 9
	};
	wall[37] = (SDL_FRect) {
		225, 477, 69, 17
	};
	wall[38] = (SDL_FRect) {
		339, 480, 89, 16
	};
	wall[39] = (SDL_FRect) {
		540, 480, 89, 16
	};
	wall[40] = (SDL_FRect) {
		672, 480, 70, 16
	};
	wall[41] = (SDL_FRect) {
		738, 533, 53, 16
	};
	wall[42] = (SDL_FRect) {
		405, 531, 159, 19
	};
	wall[43] = (SDL_FRect) {
		177, 531, 52, 19
	};
	wall[44] = (SDL_FRect) {
		228, 582, 203, 21
	};
	wall[45] = (SDL_FRect) {
		537, 585, 203, 19
	};
	wall[46] = (SDL_FRect) {
		783, 432, 10, 216
	};
	wall[47] = (SDL_FRect) {
		672, 480, 24, 70
	};
	wall[48] = (SDL_FRect) {
		606, 534, 23, 49
	};
	wall[49] = (SDL_FRect) {
		474, 441, 21, 52
	};
	wall[50] = (SDL_FRect) {
		474, 552, 21, 52
	};
	wall[51] = (SDL_FRect) {
		339, 534, 23, 52
	};
	wall[52] = (SDL_FRect) {
		273, 474, 24, 73
	};
	wall[53] = (SDL_FRect) {
		174, 432, 11, 215
	};


	//parameters to show vortex
	SDL_Surface *vortex;
	SDL_Texture *vortL_text;
	SDL_Texture *vortR_text;
	SDL_FRect vort_rect = {160, 337, 15, 30};
	SDL_FRect vort_rect1 = {795, 337, 15, 30};
	vortex = IMG_Load("vortex R.png");
	vortL_text = SDL_CreateTextureFromSurface(render, vortex);
	vortR_text = SDL_CreateTextureFromSurface(render, vortex);
	SDL_FreeSurface(vortex);

	//initialising ghosts event loop and pacman
	SDL_RenderFillRectF(render, &background);
	SDL_RenderPresent(render);
	SDL_bool evloop = SDL_TRUE;
	double direct_mouv = 0;
	PacMan pac_man = newPacMan(30, 190, 100);
	pac_man.faf = SDL_FALSE;		//if pac can eat ghosts
	phant_init();		//load ghost image

	//ghost parameters
	ghost[0].rect = (SDL_FRect) {
		421, 280, 30, 30
	};
	ghost[1].rect = (SDL_FRect) {
		424, 391, 30, 30
	};
	ghost[2].rect = (SDL_FRect) {
		515, 280, 30, 30
	};
	ghost[3].rect = (SDL_FRect) {
		528, 391, 30, 30
	};

	//loading dead ghost image
	SDL_Surface* dead_img;
	dead_img = IMG_Load("ghost_dead.png");
	dead_ghosttext = SDL_CreateTextureFromSurface(render, dead_img);
	SDL_FreeSurface(dead_img);

	//parameters controlling pwr img
	SDL_FRect pwr_rect[4];
	SDL_Surface *pwr_img, *nothing_surf;
	SDL_Texture *pwr_text[4], *nothing_text;
	SDL_bool pwr_visited[4]={SDL_FALSE,SDL_FALSE,SDL_FALSE,SDL_FALSE};
	nothing_surf=IMG_Load("nothing.png");
	nothing_text=SDL_CreateTextureFromSurface(render, nothing_surf);
	SDL_FreeSurface(nothing_surf);
	pwr_img = IMG_Load("PWR_rainbow.png");
	for (int i = 0; i <= 3; i++) {		//creating texture from surface
		pwr_text[i] = SDL_CreateTextureFromSurface(render, pwr_img);
	}
	SDL_FreeSurface(pwr_img);
	pwr_rect[0] = (SDL_FRect) {
		307, 172, 29, 15
	};
	pwr_rect[1] = (SDL_FRect) {
		637, 172, 29, 15
	};
	pwr_rect[2] = (SDL_FRect) {
		190, 604, 29, 15
	};
	pwr_rect[3] = (SDL_FRect) {
		751, 604, 29, 15
	};

	//initialising pellet parameters
	coins Pellet[252];			//defining pellets
	SDL_Surface *pellet_surf;
	pellet_surf=IMG_Load("Pellets.png");
	int counter=0;		//to count the number of pellets
	for(int n=0;n<PATH_NUM;n++){		//to put each pellet per 30px in each rectangle
		for(int y=path_rect[n].y+15;y<path_rect[n].y+path_rect[n].h-15;y+=30){
			for(int x=path_rect[n].x+15;x<path_rect[n].x+path_rect[n].w-15;x+=30){
				Pellet[counter].rect= (SDL_FRect) {x, y, 10, 10};
				counter++;
			}
		}
	}
	printf("\ncounter=%d", counter);
	for(int i=0;i<=counter;i++){		//assigning texture and states
		Pellet[i].visited=SDL_FALSE;
		Pellet[i].texture=SDL_CreateTextureFromSurface(render, pellet_surf);
	}
	SDL_FreeSurface(pellet_surf);

	//parameters to manage texts
	char live_buff[20], score_buff[100], countdown_buff[8];
	int lives=3;
	int score_num=0;
	SDL_Surface *life_surf, *score_surf, *countdown_surf, *game_over_surf, *win_surf;
	SDL_Texture *live_texte, *score_text, *countdown_text, *game_over_text, *win_text;
	TTF_Font *live_font, *game_over_font;
	SDL_Rect countdown_rect=(SDL_Rect){890, 236, 130, 75};
	SDL_Rect live_rect=(SDL_Rect) {1040, 163, 130, 75};
	SDL_Rect score_rect=(SDL_Rect) {900, 90, 130, 75};
	SDL_Rect game_over_rect= (SDL_Rect) {282, 312, 130, 75};
	SDL_Rect win_rect= (SDL_Rect) {282, 312, 130, 75};
	SDL_Color color_white= {255,255,255};
	SDL_Color color_green = {0, 255, 0};
	SDL_Color time_color= {255, 255, 255};
	live_font= TTF_OpenFont("perfect-dark-brk.regular.ttf", 52);
	game_over_font= TTF_OpenFont("game-font-7.regular.ttf", 70);
	game_over_surf=TTF_RenderText_Solid(game_over_font, "GAME OVER", color_white);
	game_over_text=SDL_CreateTextureFromSurface(render, game_over_surf);
	win_surf=TTF_RenderText_Solid(game_over_font, "YOU WON! MISSION PASSED", color_green);
	win_text=SDL_CreateTextureFromSurface(render, win_surf);
	SDL_QueryTexture(game_over_text, NULL, NULL, &game_over_rect.w, &game_over_rect.h);
	SDL_QueryTexture(win_text, NULL, NULL, &win_rect.w, &win_rect.h);
	
	
	//parameters controlling sounds
	Mix_Music *backgrd_sound = Mix_LoadMUS("11-guiles-theme-101soundboards.mp3");
	Mix_Chunk *pwr_fx=Mix_LoadWAV("power.wav");
	Mix_Chunk *game_over_fx= Mix_LoadWAV("Mamami ehh.wav");
	Mix_Chunk *blurg_sound= Mix_LoadWAV("Blurg.wav");
	Mix_Chunk *coin_sound = Mix_LoadWAV("Coin.wav");
	Mix_Chunk *win_sound = Mix_LoadWAV("San Andreas theme modified.wav");
	Mix_PlayMusic(backgrd_sound, -1);		//plays background sound
	Mix_VolumeMusic(60);		//putting music volume by quarter
	Mix_Volume(-1, 64);			//putting sound volume by half
	
	MenuItem menuItems[] = {
	        {{300, 200, 200, 50}, "Start Game"},
	        {{300, 300, 200, 50}, "Leaderboards"},
	        {{300, 400, 200, 50}, "Exit"}
	    };
	    int itemCount = sizeof(menuItems) / sizeof(menuItems[0]);
	    int selectedItem = 0;
	
	    GameState currentState = STATE_MENU;

	Uint32 start_countdown= SDL_GetTicks();
	Uint32 pwr_startTime = SDL_GetTicks(); // Start the timer for pwr
	const float MOVE_INTERVAL = 0.2;
	const int PAC_MVT = 6;
	const int COUNTDOWN_TIME=120;			//countdown time
	int pellet_cnt=counter; 		//a mettre dans le loop du menu
	SDL_Event event;

	while (evloop) {
		SDL_SetRenderDrawColor(render, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(render);
		SDL_RenderCopyF(render, vortL_text, NULL, &vort_rect);		//displaying left vortex
		SDL_RenderCopyF(render, vortR_text, NULL, &vort_rect1);		//displaying right vortex
		SDL_RenderCopy(render, pac_vie, NULL, &vie_rect);			//displaying pac vie img
		SDL_SetRenderDrawColor(render, 0, 0, 255, SDL_ALPHA_OPAQUE);	//coloring the walls in blue
		for (int i = 0; i <= 53; i++) {		//displaying walls
			SDL_RenderDrawRectF(render, &wall[i]);
		}
//		SDL_SetRenderDrawColor(render, 255, 0, 0, SDL_ALPHA_OPAQUE);
//		for(int i=0;i<=PATH_NUM;i++){	//show pellet paths
//			SDL_RenderDrawRectF(render, &path_rect[i]);
//		}
		
		
		Uint32 pwr_currentTime = SDL_GetTicks();
		if (pwr_currentTime - pwr_startTime >= 3000 && pac_man.faf) {		//every 3 seconds, the ghosts become normal
			pac_man.faf = SDL_FALSE;
			printf("pac_man is NOT FAF!\n");
			pwr_startTime = pwr_currentTime; // Reset the timer
		}
		
		int timeleft=COUNTDOWN_TIME-(SDL_GetTicks()-start_countdown)/1000;		//countdown decreases every second
		if(timeleft<0){		//if countdown finishes
			timeleft=0;
			SDL_RenderCopy(render, game_over_text, NULL, &game_over_rect);		//display game over
			SDL_RenderPresent(render);
			Mix_HaltMusic();				//stops ongoing music
			Mix_PlayChannel(-1, game_over_fx, 0);		//plays gameovermusic
			SDL_Delay(5000);		//wait 5 secs
			SDL_Quit();				//quit
		}


		SDL_FRect r;
		for (int i = 0; i <= 3; i++) {		//controlling  ghost directions
			if (r.x < pac_man.rect.x) {
				r.x = ghost[i].rect.x;
				r.y = ghost[i].rect.y;
				r.w = ghost[i].rect.w;
				r.h = ghost[i].rect.h;
				r.x += MOVE_INTERVAL;
				SDL_bool free = SDL_TRUE;
				for (int n = 0; n <= 53; n++) {		//if ghosts meets wall, it blocks and print index representing wall
					if (SDL_HasIntersectionF(&r, &wall[n])) {
						free = SDL_FALSE;
						break;
					}
				}
				if (free) {
					ghost[i].rect.x = r.x;
					ghost[i].rect.y = r.y;
					ghost[i].rect.w = r.w;
					ghost[i].rect.y = r.y;
				}
			}
			if (r.y < pac_man.rect.y) {
				r.x = ghost[i].rect.x;
				r.y = ghost[i].rect.y;
				r.w = ghost[i].rect.w;
				r.h = ghost[i].rect.h;
				r.y += MOVE_INTERVAL;
				SDL_bool free = SDL_TRUE;
				for (int n = 0; n <= 53; n++) {		//if ghosts meets wall, it blocks and print index representing wall
					if (SDL_HasIntersectionF(&r, &wall[n])) {
						free = SDL_FALSE;
						break;
					}
				}
				if (free) {
					ghost[i].rect.x = r.x;
					ghost[i].rect.y = r.y;
					ghost[i].rect.w = r.w;
					ghost[i].rect.y = r.y;
				}
			}
			if (r.x > pac_man.rect.x) {
				r.x = ghost[i].rect.x;
				r.y = ghost[i].rect.y;
				r.w = ghost[i].rect.w;
				r.h = ghost[i].rect.h;
				r.x -= MOVE_INTERVAL;
				SDL_bool free = SDL_TRUE;
				for (int n = 0; n <= 53; n++) {		//if ghosts meets wall, it blocks and print index representing wall
					if (SDL_HasIntersectionF(&r, &wall[n])) {
						free = SDL_FALSE;
						break;
					}
				}
				if (free) {
					ghost[i].rect.x = r.x;
					ghost[i].rect.y = r.y;
					ghost[i].rect.w = r.w;
					ghost[i].rect.y = r.y;
				}
			}
			if (r.y > pac_man.rect.y) {
				r.x = ghost[i].rect.x;
				r.y = ghost[i].rect.y;
				r.w = ghost[i].rect.w;
				r.h = ghost[i].rect.h;
				r.y -= MOVE_INTERVAL;
				SDL_bool free = SDL_TRUE;
				for (int n = 0; n <= 53; n++) {		//if ghosts meets wall, it blocks and print index representing wall
					if (SDL_HasIntersectionF(&r, &wall[n])) {
						free = SDL_FALSE;
						break;
					}
				}
				if (free) {
					ghost[i].rect.x = r.x;
					ghost[i].rect.y = r.y;
					ghost[i].rect.w = r.w;
					ghost[i].rect.y = r.y;
				}
				if (ghost[i].rect.x > 781) {		//if ghost goes through portal, go to other portal
					ghost[i].rect.x = 160;
				}
				if (ghost[i].rect.x < 160) {		//if ghost goes through portal, go to other portal
					ghost[i].rect.x = 781;
				}
			}
			if (SDL_HasIntersectionF(&pac_man.rect, &ghost[i].rect) && !pac_man.faf) {		//if ghost meet pac when not faf
				pac_man.rect.x = 190;
				pac_man.rect.y = 100;
				lives--;
				score_num-=20;
			}
			if(score_num<0){
				score_num=0;
			}
			if(lives<0){		//if pac loses
				lives=0;
				SDL_RenderCopy(render, game_over_text, NULL, &game_over_rect);		//display game over
				SDL_RenderPresent(render);
				Mix_HaltMusic();				//stops ongoing music
				Mix_PlayChannel(-1, game_over_fx, 0);		//plays gameovermusic
				SDL_Delay(5000);		//wait 5 secs
				SDL_Quit();				//quit
			}
		}
		
	
//		SDL_RenderDrawRectF(render, &pac_man.rect);
//			SDL_RenderDrawRect(render, &pacsize);


		while (SDL_PollEvent(&event)) {		//pac man mvts
			switch (event.type) {
				case SDL_QUIT:			//if window is closed, quit the loop and exit the program
					evloop = SDL_FALSE;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_UP:							//when up key is pressed
//							pacsize.y -= 3;
							printf("pac pars en haut\n");		//print this
							pac_man.rect.y -= PAC_MVT;				//move pacman upwards
							printf("y=%f\n", pac_man.rect.y);	//print current y-coordinate
							printf("(%f, %f)\n", pac_man.rect.x, pac_man.rect.y);	//print current coordnates
							direct_mouv = 270;
							for (int i = 0; i <= 53; i++) {		//if pacman meets wall, it blocks and print index representing wall
								if (SDL_HasIntersectionF(&pac_man.rect, &wall[i])) {
									pac_man.rect.y += PAC_MVT;
									printf("blocked at index %d\n", i);
								}
							}
							break;
						case SDLK_DOWN:							//when down key is pressed
//							pacsize.y += 3;
							printf("pac pars en bas\n");	  //print this
							pac_man.rect.y += PAC_MVT;					//move pacman downwards
							printf("y=%f\n", pac_man.rect.y);		//print current y-coordinate
							printf("(%f, %f)\n", pac_man.rect.x, pac_man.rect.y);		//print current coordnates
							direct_mouv = 90;
							for (int i = 0; i <= 53; i++) {					//if pacman meets wall, it blocks and print index representing wall
								if (SDL_HasIntersectionF(&pac_man.rect, &wall[i])) {
									pac_man.rect.y -= PAC_MVT;
									printf("blocked at index %d\n", i);
								}
							}
							break;
						case SDLK_LEFT:							//when left key is pressed
//							pacsize.x -= 3;
							printf("pac pars à gauche\n");		//print this
							pac_man.rect.x -= PAC_MVT;				//move pacman to the left
							printf("x=%f\n", pac_man.rect.x);		//print current x-coordinate
							printf("(%f, %f)\n", pac_man.rect.x, pac_man.rect.y);	//print current coordnates
							direct_mouv = 180;					//rotate  by 180deg
							for (int i = 0; i <= 53; i++) {		//if pacman meets wall, it blocks and print index representing wall
								if (SDL_HasIntersectionF(&pac_man.rect, &wall[i])) {
									pac_man.rect.x += PAC_MVT;
									printf("blocked at index %d\n", i);
								}
							}
							if (pac_man.rect.x < 160) {		//if pac passes through the portals, it go to other portal
								pac_man.rect.x = 781;
							}
							break;
						case SDLK_RIGHT:						//when right key is pressed
//							pacsize.x += 3;
							printf("pac pars ? droite\n");			//print this
							pac_man.rect.x += PAC_MVT;					//move pacman to the right
							printf("x=%f\n", pac_man.rect.x);		//print current x-coordinate
							printf("(%f, %f)\n", pac_man.rect.x, pac_man.rect.y);	//print current coordnates
							direct_mouv = 0;
							for (int i = 0; i <= 53; i++) {			//if pacman meets wall, it blocks and print index representing wall
								if (SDL_HasIntersectionF(&pac_man.rect, &wall[i])) {
									pac_man.rect.x -= PAC_MVT;
									printf("blocked at index %d\n", i);
								}
							}
							if (pac_man.rect.x > 781) {		//if pac passes through the portals, it go to other portal
								pac_man.rect.x = 160;
							}
							break;
//						case SDLK_RETURN:
//							fprintf_s(carre, "%d %d %d %d\n", pacsize.x, pacsize.y, pacsize.w, pacsize.h);
//							printf("\nit has printed in the file showing %d %d %d %d", pacsize.x, pacsize.y, pacsize.w, pacsize.h);
//							break;
//						case SDLK_z:
//							pacsize.h -= 1;
//							break;
//						case SDLK_s:
//							pacsize.h += 1;
//							break;
//						case SDLK_q:
//							pacsize.w -= 1;
//							break;
//						case SDLK_d:
//							pacsize.w += 1;
//							break;
						default:

							continue;
					}
				default:
					continue;
			}
		}
		
//		for(int i=0;i<=PATH_NUM;i++){
//			if(SDL_HasIntersectionF(&pac_man.rect, &path_rect[i])){
//				printf("\npath of index %d", i);
//			}
//		}
		
		for (int i = 0; i <= 3; i++) {		//if pac eats pwr, the ghosts become eatable
			if (SDL_HasIntersectionF(&pac_man.rect, &pwr_rect[i]) ) {
				pac_man.faf=SDL_TRUE;
			}
		}
		
		for (int i = 0; i <= 3; i++) {		//if pac eats pwr, the pwr disappears
			if (SDL_HasIntersectionF(&pac_man.rect, &pwr_rect[i]) && !pwr_visited[i]) {
				Mix_PlayChannel(-1, pwr_fx, 0);
				pwr_visited[i]=SDL_TRUE;
				pwr_text[i]=nothing_text;
				printf("pac man is now FAF\n");
				score_num+=50;
			}
		}
		
		for(int i=0;i<=counter;i++){	//if pac man eats pellet
			if(SDL_HasIntersectionF(&pac_man.rect, &Pellet[i].rect) && !Pellet[i].visited){
				Mix_PlayChannel(-1, coin_sound, 0);
				score_num+=10;
				Pellet[i].texture=nothing_text;
				Pellet[i].visited=SDL_TRUE;
				pellet_cnt--;
				if(pellet_cnt==0){
					SDL_RenderCopy(render, win_text, NULL, &win_rect);		//display game over
					SDL_RenderPresent(render);
					Mix_HaltMusic();				//stops ongoing music
					Mix_PlayChannel(-1, win_sound, 0);		//plays you win music
					SDL_Delay(10000);		//wait 5 secs
					SDL_Quit();				//quit
				}
			}
		}
		
		for (int i = 0; i <= 3; i++) {		//if pac eats ghost while being faf
			if (SDL_HasIntersectionF(&pac_man.rect, &ghost[i].rect) && pac_man.faf) {
				score_num+=100;
				Mix_PlayChannel(-1, blurg_sound, 0);
				switch (i) {	//returning ghosts to intial places
					case 0:
						ghost[0].rect = (SDL_FRect) {
							421, 280, 30, 30
						};
						break;
					case 1:
						ghost[1].rect = (SDL_FRect) {
							424, 391, 30, 30
						};
						break;
					case 2:
						ghost[2].rect = (SDL_FRect) {
							515, 280, 30, 30
						};
						break;
					case 3:
						ghost[3].rect = (SDL_FRect) {
							528, 391, 30, 30
						};
						break;
					default:
						break;
				}
			}
		}
		
		sprintf(countdown_buff, "");
		sprintf(countdown_buff, "Timeleft %d", timeleft);
		if(timeleft<30){	//if countdown is <30 color is red
			time_color= (SDL_Color){255, 0, 0, 0};
		}
		countdown_surf=TTF_RenderUTF8_Solid(live_font, countdown_buff, time_color);	//countdown surface
		countdown_text=SDL_CreateTextureFromSurface(render, countdown_surf);		//countdown texture
		SDL_QueryTexture(countdown_text, NULL, NULL, &countdown_rect.w, &countdown_rect.h);		//loading into memory

		sprintf(score_buff, "");
		sprintf(score_buff, "score %d", score_num);
		score_surf=TTF_RenderText_Solid(live_font, score_buff, color_white);	//score surface
		score_text=SDL_CreateTextureFromSurface(render, score_surf);		//score texture
		SDL_QueryTexture(score_text, NULL, NULL, &score_rect.w, &score_rect.h);		//loading into memory
		
		sprintf(live_buff, "");
		sprintf(live_buff, "lives %d", lives);
		life_surf=TTF_RenderUTF8_Solid(live_font, live_buff, color_white);			//life surface
		live_texte=SDL_CreateTextureFromSurface(render, life_surf);			//life texture
		SDL_QueryTexture(live_texte, NULL, NULL, &live_rect.w, &live_rect.h);	//actualising live
		
		for (int i = 0; i <= 3; i++) {										//displaying pwr images
			SDL_RenderCopyF(render, pwr_text[i], NULL, &pwr_rect[i]);
		}
		for(int i=0;i<=counter;i++){	//displaying pellets
			if(!Pellet[i].visited){
				SDL_RenderCopyF(render, Pellet[i].texture, NULL, &Pellet[i].rect);
			}
		}
		SDL_RenderCopy(render, live_texte, NULL, &live_rect);
		SDL_RenderCopy(render, countdown_text, NULL, &countdown_rect);
		SDL_RenderCopy(render, score_text, NULL, &score_rect);		//displaying the "score" string
		draw_ghost(pac_man);
		drawPacMan(&pac_man, direct_mouv);
		
		SDL_RenderPresent(render);
		
//		SDL_FreeSurface(win_surf);
//		SDL_DestroyTexture(win_text);
		SDL_DestroyTexture(live_texte);
		SDL_FreeSurface(life_surf);
		SDL_DestroyTexture(score_text);
		SDL_FreeSurface(score_surf);
		SDL_DestroyTexture(countdown_text);
		SDL_FreeSurface(countdown_surf);
	}
//	fclose(carre);
//	fclose(carre1);
	Mix_FreeChunk(win_sound);
	Mix_FreeMusic(backgrd_sound);
	Mix_FreeChunk(coin_sound);
	Mix_FreeChunk(blurg_sound);
	Mix_FreeChunk(pwr_fx);
	Mix_FreeChunk(game_over_fx);
	Mix_CloseAudio();
	TTF_CloseFont(live_font);
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();

	return 0;
}

PacMan newPacMan(int size, int posx, int posy) {
	PacMan p;
	p.faf=SDL_FALSE;
	p.frame = 0;
	p.rect.w = p.rect.h = size;
	p.rect.x = posx;
	p.rect.y = posy;
	SDL_Surface* img[8];
	char w[20];
	for (int i = 0; i < 5; i++) {
		strcpy(w, "");
		sprintf(w, "pac anim%d.png", i + 1);
		printf(w);
		img[i] = IMG_Load(w);
		p.textures[i] = SDL_CreateTextureFromSurface(render, img[i]);
		SDL_FreeSurface(img[i]);
	}
	for (int i = 5; i < 8; i++) {
		strcpy(w, "");
		sprintf(w, "pac anim%d.png", 8 - i + 1);
		printf(w);
		img[i] = IMG_Load(w);
		p.textures[i] = SDL_CreateTextureFromSurface(render, img[i]);
		SDL_FreeSurface(img[i]);
	}
	p.lastTime = clock();
	return p;
}

void drawPacMan(PacMan* p, double pac_rot) {
	if (clock() - p->lastTime > 50) {
		p->frame++;
		p->lastTime = clock();
		if (p->frame == 8) {
			p->frame = 0;
		}
	}
	SDL_RenderCopyExF(render, p->textures[p->frame], NULL, &p->rect, pac_rot, NULL, SDL_FLIP_NONE);
}

void phant_init() {
	char name[20];
	SDL_Surface *img[4];
	for (int i = 0; i <= 3; i++) {
		strcpy(name, "");
		sprintf(name, "pac_ghost%d.png", i);
		img[i] = IMG_Load(name);
		ghost[i].text = SDL_CreateTextureFromSurface(render, img[i]);
		SDL_FreeSurface(img[i]);
	}
}

void draw_ghost(PacMan pac_man) {
	if (pac_man.faf) {
		for (int i = 0; i <= 3; i++) {
			SDL_RenderCopyF(render, dead_ghosttext, NULL, &ghost[i].rect);
		}
	} else {
		for (int i = 0; i <= 3; i++) {
			SDL_RenderCopyF(render, ghost[i].text, NULL, &ghost[i].rect);
		}
	}
}

void drawMenu(SDL_Renderer *renderer, TTF_Font *font, MenuItem menuItems[], int itemCount, int selectedItem) {
    SDL_Color color;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect dest;

    for (int i = 0; i < itemCount; i++) {
        color = (i == selectedItem) ? (SDL_Color){255, 0, 0, 255} : (SDL_Color){255, 255, 255, 255};
        surface = TTF_RenderText_Solid(font, menuItems[i].text, color);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        dest = menuItems[i].rect;
        SDL_RenderCopy(renderer, texture, NULL, &dest);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
}
