//(TODO) INIT MORE STUFF (TFF...)
#include "utils.h"
#include "asset_manager.h"
#include "logging.h"

struct{
	S32 x;
	S32 y;
	S32 width;
	S32 height;
}typedef SYNTH_RECT;

struct{
	SYNTH_RECT on_map;
	U0 *texture;
}typedef SPRITE;

struct{
	SPRITE chars[80];
	U8 array_chars[80];
}typedef FONT;

struct{
	S8 *window_title;
	S32 width;
	S32 height;
	U0 *window;
	U0 *renderer;
	ASSET_STACK texture_manager;
}typedef GRAPHICS;

BOOL GRAPHICS_init(GRAPHICS *graphics);
BOOL GRAPHICS_free(GRAPHICS *graphics);
BOOL GRAPHICS_loadBMP(U8 *path, GRAPHICS *graphics);
SPRITE GRAPHICS_createSprite(U32 position, U32 width, U32 height, GRAPHICS graphics);
BOOL GRAPHICS_renderBMP(U32 x, U32 y, F32 scale, SPRITE sprite, GRAPHICS graphics);
FONT  GRAPHICS_loadFontBMP(GRAPHICS graphics);
BOOL GRAPHICS_print(U32 x, U32 y, F32 scale, S8 *output, GRAPHICS graphics, FONT font);
U0 GRAPHICS_renderClear(GRAPHICS window);
U0 GRAPHICS_renderPresent(GRAPHICS window);