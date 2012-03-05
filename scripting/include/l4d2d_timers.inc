/**
 * vim: set ts=4 :
 * =============================================================================
 * L4D2_Direct Timer functions
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
#if defined _l4d2_direct_timers_included
 #endinput
#endif
#define _l4d2_direct_timers_included

#include <sourcemod>
#include <l4d2d_internals>

#define CTIMER_DURATION_OFFSET (Address:4)
#define CTIMER_TIMESTAMP_OFFSET (Address:8)
#define ITIMER_TIMESTAMP_OFFSET (Address:4)

enum CountdownTimer
{
	CTimer_Null = 0
};

enum IntervalTimer
{
	ITimer_Null = 0
};

stock CountdownTimer:L4D2Direct_GetVSStartTimer()
{
	static Address:pVSStartTimer = Address_Null;
	if(pVSStartTimer == Address_Null)
	{
		new offs = GameConfGetOffset(L4D2Direct_GetGameConf(), "CDirectorVersusMode::VersusStartTimer");
		if(offs == -1) return CTimer_Null;
		pVSStartTimer = L4D2Direct_GetCDirectorVersusMode() + Address:offs;
	}
	return CountdownTimer:pVSStartTimer;
}

static stock Float:CTimer_GetDuration( CountdownTimer:timer )
{
	return Float:LoadFromAddress( Address:timer + CTIMER_DURATION_OFFSET , NumberType_Int32 );
}

static stock CTimer_SetDuration( CountdownTimer:timer , Float:duration )
{
	StoreToAddress( Address:timer + CTIMER_DURATION_OFFSET , _:duration , NumberType_Int32 );
}

static stock Float:CTimer_GetTimestamp( CountdownTimer:timer )
{
	return Float:LoadFromAddress( Address:timer + CTIMER_TIMESTAMP_OFFSET , NumberType_Int32 );
}

static stock CTimer_SetTimestamp( CountdownTimer:timer , Float:timestamp )
{
	StoreToAddress( Address:timer + CTIMER_TIMESTAMP_OFFSET , _:timestamp , NumberType_Int32 );
}

static stock Float:ITimer_GetTimestamp( IntervalTimer:timer )
{
	return Float:LoadFromAddress( Address:timer + ITIMER_TIMESTAMP_OFFSET , NumberType_Int32 );
}

static stock ITimer_SetTimestamp( IntervalTimer:timer , Float:timestamp )
{
	StoreToAddress( Address:timer + ITIMER_TIMESTAMP_OFFSET , _:timestamp , NumberType_Int32 );
}

stock CTimer_Reset( CountdownTimer:timer )
{
	CTimer_SetTimestamp( timer , GetGameTime() + CTimer_GetDuration( timer ) );
}

stock CTimer_Start( CountdownTimer:timer , Float:duration )
{
	CTimer_SetTimestamp( timer , GetGameTime() + duration );
	CTimer_SetDuration( timer , duration );
}

stock CTimer_Invalidate( CountdownTimer:timer )
{
	CTimer_SetTimestamp( timer , -1.0 );
}

stock bool:CTimer_HasStarted( CountdownTimer:timer )
{
	return CTimer_GetTimestamp( timer ) >= 0.0;
}

stock bool:CTimer_IsElapsed( CountdownTimer:timer )
{
	return GetGameTime() >= CTimer_GetTimestamp( timer );
}

stock Float:CTimer_GetElapsedTime( CountdownTimer:timer )
{
	return ( GetGameTime() - CTimer_GetTimestamp( timer ) ) + CTimer_GetDuration( timer );
}

stock Float:CTimer_GetRemainingTime( CountdownTimer:timer )
{
	return CTimer_GetTimestamp( timer ) - GetGameTime();
}

stock Float:CTimer_GetCountdownDuration( CountdownTimer:timer )
{
	return ( CTimer_GetTimestamp( timer ) > 0.0 ) ? CTimer_GetDuration( timer ) : 0.0;
}

stock ITimer_Reset( IntervalTimer:timer )
{
	ITimer_SetTimestamp( timer , GetGameTime() );
}

stock ITimer_Start( IntervalTimer:timer )
{
	ITimer_SetTimestamp( timer , GetGameTime() );
}

stock ITimer_Invalidate( IntervalTimer:timer )
{
	ITimer_SetTimestamp( timer , -1.0 );
}

stock bool:ITimer_HasStarted( IntervalTimer:timer )
{
	return ( ITimer_GetTimestamp( timer ) > 0.0 );
}

stock Float:ITimer_GetElapsedTime( IntervalTimer:timer )
{
	return ITimer_GetHasStarted( timer ) ? GetGameTime() - ITimer_GetTimestamp() : 99999.9;
}

