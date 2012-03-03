/**
 * vim: set ts=4 :
 * =============================================================================
 * L4D2_Direct
 * Copyright (C) 2012 Michael "ProdigySim" Busby
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 *
 * Version: $Id$
 */
#if defined _l4d2_direct_included
 #endinput
#endif
#define _l4d2_direct_included

#include <sourcemod>

stock Handle:L4D2Direct_GetGameConf()
{
	static Handle:g_hGameConf_l4d2dir = INVALID_HANDLE;
	if(g_hGameConf_l4d2dir == INVALID_HANDLE)
	{
		g_hGameConf_l4d2dir = LoadGameConfigFile("l4d2_direct");
	}
	return g_hGameConf_l4d2dir;
}

stock Address:L4D2Direct_GetCDirectorAddress()
{
	static Address:TheDirector = Address_Null;
	if(TheDirector == Address_Null)
	{
		TheDirector = GameConfGetAddress(L4D2Direct_GetGameConf(), "CDirector");
	}
	return TheDirector;
}

stock L4D2Direct_GetTankCount()
{
	static Address:pTankCount = Address_Null;
	if(pTankCount == Address_Null) 
	{
		pTankCount = L4D2Direct_GetCDirectorAddress() + Address:GameConfGetOffset(L4D2Direct_GetGameConf(), "CDirector::m_iTankCount");
	}
	return LoadFromAddress( pTankCount , NumberType_Int32 );
}

