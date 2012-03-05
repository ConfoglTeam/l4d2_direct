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
#include <l4d2d_internals>
#include <l4d2d_timers>

#define CLAMP(%0,%1,%2) (((%0) < (%1)) ? (%1) : (((%0) > (%2)) ? (%2) : (%0)))

/* CDirector Variable access */

stock L4D2Direct_GetTankCount()
{
	return LoadFromAddress( L4D2Direct_GetTankCountAddr() , NumberType_Int32 );
}

/* CDirectorVersusMode Variable access */

// teamNumber = 0 or 1
stock L4D2Direct_GetVSCampaignScore( teamNumber )
{
	if(teamNumber < 0 || teamNumber > 1) return -1;

	return LoadFromAddress( L4D2Direct_GetVSCampaignScoresAddr() + Address:(teamNumber * 4), NumberType_Int32 );
}

stock L4D2Direct_SetVSCampaignScore( teamNumber , score )
{
	if(teamNumber < 0 || teamNumber > 1) return;

	StoreToAddress( L4D2Direct_GetVSCampaignScoresAddr() + Address:(teamNumber * 4), score, NumberType_Int32 );
}

// roundNumber = 0 or 1
stock Float:L4D2Direct_GetVSTankFlowPercent( roundNumber )
{
	if(roundNumber < 0 || roundNumber > 1) return -1.0;
	
	return Float:LoadFromAddress( L4D2Direct_GetVSTankFlowAddr() + Address:(roundNumber * 4) , NumberType_Int32 );
}

stock L4D2Direct_SetVSTankFlowPercent( roundNumber , Float:flow )
{
	if(roundNumber < 0 || roundNumber > 1) return;
	
	flow = CLAMP(flow,0.0,1.0);
	
	StoreToAddress( L4D2Direct_GetVSTankFlowAddr() + Address:(roundNumber * 4) , _:flow , NumberType_Int32 );
}

// Is there a tank spawn left to do this round? (or has it already been spawned)
stock bool:L4D2Direct_GetVSTankToSpawnThisRound( roundNumber )
{
	if(roundNumber < 0 || roundNumber > 1) return false;
	
	return bool:LoadFromAddress( L4D2Direct_GeVSTankToSpawnAddr() + Address:roundNumber , NumberType_Int8 );
}

stock L4D2Direct_SetVSTankToSpawnThisRound( roundNumber , bool:spawn )
{
	if(roundNumber < 0 || roundNumber > 1) return;
	
	StoreToAddress( L4D2Direct_GeVSTankToSpawnAddr() + Address:roundNumber , _:spawn, NumberType_Int8 );
}

// roundNumber = 0 or 1
stock Float:L4D2Direct_GetVSWitchFlowPercent( roundNumber )
{
	if(roundNumber < 0 || roundNumber > 1) return -1.0;

	return Float:LoadFromAddress( L4D2Direct_GetVSWitchFlowAddr() + Address:(roundNumber * 4) , NumberType_Int32 );
}

stock L4D2Direct_SetVSWitchFlowPercent( roundNumber , Float:flow )
{
	if(roundNumber < 0 || roundNumber > 1) return;

	flow = CLAMP(flow,0.0,1.0);
	
	StoreToAddress( L4D2Direct_GetVSWitchFlowAddr() + Address:(roundNumber * 4) , _:flow , NumberType_Int32 );
}

// Is there a witch spawn left to do this round? (or has it already been spawned)
stock bool:L4D2Direct_GetVSWitchToSpawnThisRound( roundNumber )
{
	if(roundNumber < 0 || roundNumber > 1) return false;
	
	return bool:LoadFromAddress( L4D2Direct_GetVSWitchToSpawnAddr() + Address:roundNumber , NumberType_Int8 );
}

stock L4D2Direct_SetVSWitchToSpawnThisRound( roundNumber , bool:spawn )
{
	if(roundNumber < 0 || roundNumber > 1) return;
	
	StoreToAddress( L4D2Direct_GetVSWitchToSpawnAddr() + Address:roundNumber , _:spawn , NumberType_Int8 );
}

// Take a flow distance, divide by this value, and you get a flow %
stock Float:L4D2Direct_GetMapMaxFlowDistance()
{
	return Float:LoadFromAddress( L4D2Direct_GetMapMaxFlowDistanceAddr() , NumberType_Int32 );
}

#undef CLAMP
