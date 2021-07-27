#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#include "asset_manager.h"

BOOL MANAGER_assetInit(ASSET_STACK *asset_manager, U32 data_type)
{
	asset_manager->capacity = 3;
	asset_manager->stack = malloc(asset_manager->capacity * (sizeof(U8) * 4));
	asset_manager->top = -1;
	return 1;
}

BOOL MANAGER_assetFree(ASSET_STACK *asset_manager)
{
	
	while(asset_manager->top > -1)
		MANAGER_assetPop(asset_manager);
	free(asset_manager);
	asset_manager->stack = NULL;
	return 1;
}

S32 MANAGER_assetPush(ASSET_STACK *asset_manager, U0 *asset)
{
	asset_manager->top++;
	if(asset_manager->top == asset_manager->capacity)
		MANAGER_assetScale(asset_manager);
	asset_manager->stack[asset_manager->top] = asset;
	return asset_manager->top;
}

S32 MANAGER_assetPop(ASSET_STACK *asset_manager)
{
	if(asset_manager->top == -1)
		return 0;
	if(asset_manager->type == ASSET_TEXTURE)
		SDL_DestroyTexture(MANAGER_assetTop(asset_manager));
	if(asset_manager->type == ASSET_STRING)
		free(MANAGER_assetTop(asset_manager));
	asset_manager->top--;
	
	return asset_manager->top;
}

U0 *MANAGER_assetTop(ASSET_STACK *asset_manager)
{
	return asset_manager->stack[asset_manager->top];
}

U32 MANAGER_assetScale(ASSET_STACK *asset_manager)
{
	asset_manager->capacity += 3;
	asset_manager->stack = realloc(asset_manager->stack, asset_manager->capacity * (sizeof(U8) * 4));
	return asset_manager->capacity;
}