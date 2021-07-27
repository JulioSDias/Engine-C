#include "utils.h"

struct{
	U0 **stack;
	S32 capacity;
	S32 top;
	U32 type;
}typedef ASSET_STACK;

BOOL MANAGER_assetInit(ASSET_STACK *asset_manager, U32 data_type);
S32 MANAGER_assetPush(ASSET_STACK *asset_manager, U0 *asset);
S32 MANAGER_assetPop(ASSET_STACK *asset_manager);
BOOL MANAGER_assetFree(ASSET_STACK *asset_manager);
U0 *MANAGER_assetTop(ASSET_STACK *asset_manager);
U32 MANAGER_assetScale(ASSET_STACK *asset_manager);