#define U0 void
#define U8 unsigned char
#define S8 char
#define U16 unsigned short
#define S16 short
#define U32 unsigned int
#define S32 int
#define U64 unsigned long
#define S64 long int
#define F32 float
#define F64 double
#define BOOL U8

#define STD_WHITE 0xFFFFFF
#define STD_RED 0xFF0000
#define STD_GREEN 0x00FF00
#define STD_BLUE 0x0000FF
#define STD_CYAN 0x00FFFF
#define STD_PURPLE 0xFF00FF
#define STD_YELLOW 0xFFFF00
#define STD_DARK_GREY 0x111111

#define ASSET_TEXTURE 1
#define ASSET_STRING 2

/*struct{
	U32 count;
	S8 *buffer;
}typedef TEXT_INPUT;

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
			engine->input.text.count++;
            
			if(engine->input.text.count > 1)
				engine->input.text.buffer = (S8 *)realloc(engine->input.text.buffer, (engine->input.text.count + 1));
            
			engine->input.text.buffer[engine->input.text.count - 1] = *event.text.text;
			engine->input.text.buffer[engine->input.text.count] = '\0';		
		}
	}		
}

S8 *ENGINE_inputText(ENGINE *engine, FONT font, BOOL flag)
{
	S8 *text = NULL;
	if(flag == 0 && engine->input.text.buffer == NULL){
		engine->input.text.buffer = (S8 *)calloc(2, 1);
		SDL_StartTextInput();
		printf("START\n");
	}
	
	if(flag == 1 && engine->input.text.buffer != NULL){
		MANAGER_assetPush(&engine->input.text.string_manager, engine->input.text.buffer);
		free(engine->input.text.buffer);
		engine->input.text.buffer = NULL;
		engine->input.text.count = 0;
		SDL_StopTextInput();
		printf("STOP\n");
	}
	
	if(engine->input.text.buffer != NULL){
		if(engine->input.text.count > 0){
			for(U32 i = 0; i <= 80; i++){
				if(engine->input.text.buffer[engine->input.text.count - 1] == font.array_chars[i])
					break;
				if(i == 80)
					engine->input.text.buffer[engine->input.text.count - 1] = '?';
			}
		}
		text = engine->input.text.buffer;
	}
	if(engine->input.text.buffer == NULL)
		text = MANAGER_assetTop(&engine->input.text.string_manager);
		
    return text; 
}*/