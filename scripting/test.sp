#include <sourcemod>

new Handle:g_gconf;

public OnPluginStart()
{
	g_gconf = LoadGameConfigFile("l4d2_direct");
	RegConsoleCmd("sm_addtest", addtest);

}

public Action:addtest(client,args)
{
	static Address:TheDirector = Address_Null;
	if(TheDirector == Address_Null) TheDirector = GameConfGetAddress(g_gconf, "CDirector");
	
	ReplyToCommand(client, "CDirector found at 0x%08x", TheDirector);
	
	static tankcountOffs = -1;
	if(tankcountOffs == -1) tankcountOffs = GameConfGetOffset(g_gconf, "CDirector::m_iTankCount");
	
	ReplyToCommand(client, "Reading m_iTankCount from TheDirector+%d (0x%08x)", tankcountOffs, _:TheDirector+tankcountOffs);
	
	new tankcount = LoadFromAddress(TheDirector+Address:tankcountOffs,NumberType_Int32);
	ReplyToCommand(client, "Tank count: %d", tankcount);
	return Plugin_Handled;
}