#include <SDL2/SDL.h>
#include <stdio.h>
#include<SDL2/SDL_image.h>
#include<time.h>

SDL_Surface* pacsurf;
SDL_Texture* pactext;
SDL_Renderer* render;

render=SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
void display_newframe(char* image, SDL_Rect pacsize);
void pac_animate();

void display_newframe(char* image, SDL_Rect pacsize){
	pacsurf=IMG_Load(image);
	pactext=SDL_CreateTextureFromSurface(render, pacsurf);
	SDL_FreeSurface(pacsurf);
	SDL_QueryTexture(pactext, NULL, NULL, &pacsize.w, &pacsize.h);
	SDL_RenderCopy(render, pactext, NULL, &pacsize);
	SDL_RenderPresent(render);
	SDL_RenderClear(render);
}

void pac_animate(){
	SDL_Rect pacsize;
		pacsize.x=150;
		pacsize.y=100;
		pacsize.h=36;
		pacsize.w=41;
		display_newframe("pac anim1.png", pacsize);
		SDL_Delay(110);
		display_newframe("pac anim2.png", pacsize);
		SDL_Delay(110);
		display_newframe("pac anim3.png", pacsize);
		SDL_Delay(110);
		display_newframe("pac anim4.png", pacsize);
		SDL_Delay(110);
		display_newframe("pac anim5.png", pacsize);
		SDL_Delay(110);
		display_newframe("pac anim4.png", pacsize);
		SDL_Delay(110);
		display_newframe("pac anim3.png", pacsize);
		SDL_Delay(110);
		display_newframe("pac anim2.png", pacsize);
		SDL_Delay(110);
}
