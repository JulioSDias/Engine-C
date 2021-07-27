#include <stdio.h>

#include "src/engine.h"
//read
//print variables
//shapes
//window sizes
//engine_exit

S32 main(){
	ENGINE engine = {0};
	GRAPHICS window = {"Synthesis", 800, 640};
	ENGINE_init(&engine, window, 60);
	GRAPHICS_loadBMP("mc_font.bmp", &engine.window);
	SPRITE M = GRAPHICS_createSprite(12, 7, 8, engine.window);
	SPRITE N = GRAPHICS_createSprite(13, 7, 8, engine.window);
	FONT _8bitfont = GRAPHICS_loadFontBMP(engine.window);
	BOOL flag = 0;
	while(engine.running == 1){
		ENGINE_startTimer(&engine.fps);
		ENGINE_event(&engine);
		if(PRESSED(SYNTH_F1, engine.input))
			flag = !flag;
		S8 *text = ENGINE_inputText(&engine, _8bitfont, flag);
		GRAPHICS_renderClear(engine.window);
		GRAPHICS_print(100, 100, 3.0, text, engine.window, _8bitfont);
		GRAPHICS_renderPresent(engine.window);
		F32 fps = ENGINE_fps(&engine.fps);
		if(PRESSED(SYNTH_DOWN, engine.input))
			printf("%.1f\n", fps);
	}
	ENGINE_exit(&engine);
}


