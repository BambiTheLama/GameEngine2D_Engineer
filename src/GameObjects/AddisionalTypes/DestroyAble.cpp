#include "DestroyAble.h"

bool isThisToolType(ToolType tool, ToolType requestTool)
{
	if ((int)requestTool >= 0)
		return  ((int)requestTool % (int)tool) == 0;
	return false;
}

DestroyAble::DestroyAble(ToolType request)
{
	itemToolRequest = request;
}
DestroyAble::DestroyAble(DestroyAble& dest)
{
	itemToolRequest = dest.itemToolRequest;
}