#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#include "engine.h"

S32 ENGINE_init(ENGINE *engine, GRAPHICS window, U32 target_fps)
{
	LOG_init();
    
	if (ENGINE_inputInit(engine) != 1)
		LOG_error("FAILED TO INIT INPUT");
	
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		LOG_info("SDL STARTED");
		engine->window = window;
		
		engine->running = 1;
		
		if(GRAPHICS_init(&engine->window) == 1)
			LOG_info("WINDOW CREATION SUCCESSFUL");
		
		engine->fps.target_time = ENGINE_initFPS(target_fps);
		
		if(MANAGER_assetInit(&engine->input.string_manager, ASSET_STRING) == 1)
			LOG_info("TEXT MANAGER INITIALIZED");
		SDL_StartTextInput();
	}
	return 1;
}

BOOL ENGINE_inputInit(ENGINE *engine){
	
	U32 SDLkey[BUTTON_COUNT] = {SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT, SDLK_ESCAPE, SDLK_BACKSPACE, SDLK_SPACE, SDLK_LSHIFT, SDLK_RSHIFT, SDLK_RETURN, SDLK_F1, SDLK_F2, SDLK_F3, SDLK_F4, SDLK_F5, SDLK_F6, SDLK_F7, SDLK_F8, SDLK_F9, SDLK_F10, SDLK_F11, SDLK_F12};
	
	for(U32 i = 0; i < BUTTON_COUNT; i++)
		engine->input.key[i] = SDLkey[i];
	
	return 1;
}

S32 ENGINE_event(ENGINE *engine)
{
	SDL_Event event;
	
	for(U32 i = 0; i < BUTTON_COUNT; i++)
		engine->input.button[i].changed = 0;
	
	while (SDL_PollEvent(&event) != 0){
		if(event.type == SDL_QUIT)
			engine->running = 0;
        
		if(event.type == SDL_KEYDOWN){
			for(U32 i = 0; i < BUTTON_COUNT; i++){
				if(event.key.keysym.sym == engine->input.key[i]){
					if(engine->input.button[i].is_down == 0) 
						engine->input.button[i].changed = 1; 
					engine->input.button[i].is_down = 1;
				}
			}
		}
		
		if(event.type == SDL_KEYUP){
			for(U32 i = 0; i < BUTTON_COUNT; i++){
				if(event.key.keysym.sym == engine->input.key[i]){
					if(engine->input.button[i].is_down == 1) 
						engine->input.button[i].changed = 1; 
					engine->input.button[i].is_down = 0;
				}
			}
		}
		
		if(event.type == SDL_TEXTINPUT){
			TEXT_INPUT *string;
			string = MANAGER_assetTop(&engine->input.string_manager);
			MANAGER_assetPop(&engine->input.string_manager);
			string->count++;
			
			if(string->count > 1)
				string->buffer = (S8 *)realloc(string->buffer, (string->count + 1));
			
			string->buffer[string->count - 1] = *event.text.text;
			string->buffer[string->count] = '\0';
			MANAGER_assetPush(&engine->input.string_manager, &string);
		}
	}		
}
BOOL x = 0;
S8 *ENGINE_inputText(ENGINE *engine, FONT font, BOOL flag)
{
	TEXT_INPUT *string;
	if(x == 0){
		string->buffer = (S8 *)calloc(2, 1);
		MANAGER_assetPush(&engine->input.string_manager, string);
		x = 1;
	}
	//string = MANAGER_assetTop(&engine->input.string_manager);
	//GRAPHICS_print(0, 0, 2.0, string->buffer, engine->window, font);
	U32 i = 0;
	//if(string->count > 0){
		//while(string->buffer[i] != '\0'){
			//printf("%c", string->buffer[i]);
			//i++;
		//}
		//printf("\n");
	//}
		
	return "a";
}

F32 ENGINE_initFPS(U32 target_fps)
{
	F32 target_time = 1000.0f/target_fps;
	return target_time;
}

BOOL ENGINE_startTimer(FPS *fps)
{
	fps->start_time = SDL_GetTicks();
	return 1;
}

F32 ENGINE_fps(FPS *fps)
{
	fps->count++;
	
	F32 elapsed_time = SDL_GetTicks() - fps->start_time;
	
	if(elapsed_time < fps->target_time)
		SDL_Delay(fps->target_time - elapsed_time);
	
	fps->raw = 1000.0f/(SDL_GetTicks() - fps->start_time);
	fps->accum += fps->raw;
	
	if(fps->count == 50){
		fps->cooked = fps->accum/(F32)(fps->count);
		
		fps->accum = 0;
		fps->count = 0;
	}
	return fps->cooked;
}

BOOL PRESSED(U32 b, INPUT input){
	if((input.button[b].is_down == 1) && (input.button[b].changed == 1))
		return 1;
	return 0;
}

BOOL RELEASED(U32 b, INPUT input){
	if((input.button[b].is_down == 0) && (input.button[b].changed == 1))
		return 1;
	return 0;
}

BOOL HOLD(U32 b, INPUT input){
	if(input.button[b].is_down == 1)
		return 1;
	return 0;
}

S32 ENGINE_exit(ENGINE *engine)
{
	if(GRAPHICS_free(&engine->window) == 1)
		LOG_info("GRAPHICS DESTROYED");
	if(MANAGER_assetFree(&engine->input.string_manager) == 1)
		LOG_info("TEXT MANAGER DESTROYED");
	SDL_Quit();
	return 1;
}

U0 ENGINE_delay(U32 time)
{
	SDL_Delay(time);
}