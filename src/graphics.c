#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "graphics.h"

BOOL GRAPHICS_init(GRAPHICS *graphics)
{

	graphics->window = SDL_CreateWindow(graphics->window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, graphics->width, graphics->height, SDL_WINDOW_SHOWN);
	if(graphics->window == NULL) 
		LOG_error("WINDOW CREATION");

	graphics->renderer = SDL_CreateRenderer(graphics->window, -1, 0);
	if(graphics->renderer == NULL)
		LOG_error("RENDER INITIALIZATION");
	
	if(MANAGER_assetInit(&graphics->texture_manager, ASSET_TEXTURE) == 1)
		LOG_info("ASSET MANAGER CREATED");
	return 1;
}

BOOL GRAPHICS_loadBMP(U8 *path, GRAPHICS *graphics)
{
	
	SDL_Surface *surface = SDL_LoadBMP(path);
	SDL_SetColorKey(surface, SDL_TRUE, STD_DARK_GREY);
	if(surface == NULL)
		LOG_error("LOADING BMP SURFACE");
	U0 *texture = SDL_CreateTextureFromSurface(graphics->renderer, surface);
	MANAGER_assetPush(&graphics->texture_manager, texture);
	if(texture == NULL)
		LOG_error("LOADING BMP TEXTURE");
	SDL_FreeSurface(surface);
	return 1;
}

SPRITE GRAPHICS_createSprite(U32 position, U32 width, U32 height, GRAPHICS graphics)
{
	
	SYNTH_RECT rect = {position%10 * 8, position/10 * 8, width, height};
	SPRITE sprite = {rect, NULL};
	sprite.texture = MANAGER_assetTop(&graphics.texture_manager);
	return sprite;
}

BOOL GRAPHICS_renderBMP(U32 x, U32 y, F32 scale, SPRITE sprite, GRAPHICS graphics)
{
	SYNTH_RECT rect = {x, y, sprite.on_map.width*scale, sprite.on_map.height*scale};
	SDL_RenderCopy(graphics.renderer, sprite.texture, (SDL_Rect *)&sprite.on_map, (SDL_Rect *)&rect);
	return 1;
}

FONT GRAPHICS_loadFontBMP(GRAPHICS graphics)
{
	U8 buffer_array[80] = 
		{
			'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
			'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
			'U', 'V', 'W', 'X', 'Y', 'Z', ' ', ' ', ' ', ' ',
			'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
			'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
			'u', 'v', 'w', 'x', 'y', 'z', ' ', ' ', ' ', '_',
			'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
			'.', ',', ';', ':', '!', '?', '(', ')', '-', '$'
		};
	
	FONT font = {0};

	for(U32 i = 0; i < 80; i++){
		font.array_chars[i] = buffer_array[i];
		font.chars[i].on_map.x = i%10 * 8;
		font.chars[i].on_map.y = i/10 * 8;
		font.chars[i].on_map.width = 7;
		font.chars[i].on_map.height = 8;
		font.chars[i].texture = MANAGER_assetTop(&graphics.texture_manager);
	}
	return font;
}

BOOL GRAPHICS_print(U32 x, U32 y, F32 scale, S8 *output, GRAPHICS graphics, FONT font)
{

	U32 k = 0;
	if(output == NULL)
		return 0;
	while(output[k] != '\0'){
		for(U32 i = 0; i <= 80; i++){
			if(output[k] == font.array_chars[i]){
				GRAPHICS_renderBMP(x + ((k * 6) * scale), y, scale, font.chars[i], graphics);
				k++;
				break;
			}
		}
	}
	return 1;
}

U0 GRAPHICS_renderClear(GRAPHICS window)
{
	SDL_RenderClear(window.renderer);
	return;
}
U0 GRAPHICS_renderPresent(GRAPHICS window)
{
	SDL_RenderPresent(window.renderer);
	return;
}

BOOL GRAPHICS_free(GRAPHICS *graphics)
{
	SDL_DestroyWindow(graphics->window);
	SDL_DestroyRenderer(graphics->renderer);
	if(MANAGER_assetFree(&graphics->texture_manager) == 1)
		LOG_info("TEXTURE MANAGER DESTROYED");
	return 1;
}
