#include <sourcemod>
#include <l4d2_direct>

public OnPluginStart()
{
	RegConsoleCmd("sm_addtest", addtest);
}

public Action:addtest(client,args)
{
	ReplyToCommand(client, "Tank count: %d", L4D2Direct_GetTankCount());
	ReplyToCommand(client, "Campaign Scores[0]: %d", L4D2DirectVS_GetCampaignScore(0));
	ReplyToCommand(client, "Campaign Scores[1]: %d", L4D2DirectVS_GetCampaignScore(1));
	ReplyToCommand(client, "Tank spawn[0]: %s %f %f", 
		L4D2DirectVS_TankSpawnThisRound(0) ? "yes" : "no", 
		L4D2DirectVS_GetTankFlowPercent(0), 
		L4D2DirectVS_GetTankFlowPercent(0)*L4D2Direct_GetMapMaxFlowDistance());
	ReplyToCommand(client, "Tank spawn[1]: %s %f %f", 
		L4D2DirectVS_TankSpawnThisRound(1) ? "yes" : "no", 
		L4D2DirectVS_GetTankFlowPercent(1), 
		L4D2DirectVS_GetTankFlowPercent(1)*L4D2Direct_GetMapMaxFlowDistance());
	return Plugin_Handled;
}