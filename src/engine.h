#include "utils.h"
#include "graphics.h"
BOOL test;

enum {SYNTH_UP, SYNTH_DOWN, SYNTH_LEFT, SYNTH_RIGHT, SYNTH_ESCAPE, SYNTH_BACKSPACE, SYNTH_SPACE, SYNTH_LSHIFT, SYNTH_RSHIFT, SYNTH_RETURN, SYNTH_F1, SYNTH_F2, SYNTH_F3, SYNTH_F4, SYNTH_F5, SYNTH_F6, SYNTH_F7, SYNTH_F8, SYNTH_F9, SYNTH_F10, SYNTH_F11, SYNTH_F12, BUTTON_COUNT};

struct{
    BOOL is_down;
    BOOL changed;
}typedef BUTTON;

struct{
	U32 count;
	S8 *buffer;
}typedef TEXT_INPUT;

struct{
    BUTTON button[BUTTON_COUNT];
	U32 key[BUTTON_COUNT];
	ASSET_STACK string_manager;
}typedef INPUT;

struct{
	U32 count;
	F32 raw;
	F32 cooked;
	F32 accum;
	F32 start_time;
	F32 target_time;
}typedef FPS;

struct{
	GRAPHICS window;
	INPUT input;
	FPS fps;
	BOOL running;
}typedef ENGINE;

S32 ENGINE_init(ENGINE *engine, GRAPHICS window, U32 target_fps);
BOOL ENGINE_inputInit(ENGINE *engine);
U0 ENGINE_delay(U32 time);

F32 ENGINE_initFPS(U32 target_fps);
BOOL ENGINE_startTimer(FPS *fps);
F32 ENGINE_fps(FPS *fps);

S8 *ENGINE_inputText(ENGINE *engine, FONT font, BOOL flag);

S32 ENGINE_event(ENGINE *engine);
BOOL PRESSED(U32 b, INPUT input);
BOOL RELEASED(U32 b, INPUT input);
BOOL HOLD(U32 b, INPUT input);

S32 ENGINE_exit(ENGINE *engine);