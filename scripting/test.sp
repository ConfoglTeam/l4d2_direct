#include <sourcemod>
#include <l4d2_direct>

public OnPluginStart()
{
	RegConsoleCmd("sm_addtest", addtest);
}

public Action:addtest(client,args)
{
	ReplyToCommand(client, "Tank count: %d", L4D2Direct_GetTankCount());
	return Plugin_Handled;
}