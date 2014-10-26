//
// Invoke.cpp
// This file contains the PawnFunction command, which simply said
// provides functionality to invoke on a specific pawn command, using
// a ScriptCommand-like syntax. The pawn functions _have_ to be used
// in the filterscript/gamemode using the LVP Core.
//
// Author: Peter Beverloo
//         peter@dmx-network.com
//
// The structure of the code is ScriptCommand-like, therefore some
// credits to spookie as well.
//

#include "../SDK/plugin.h"
#include "functions.h"

#include <stdarg.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MAX_REFERENCE_VARS 6
#pragma warning(disable:4267 4312)

// A type-definition for the AMX-function type;
typedef int (*amx_Function_t)(AMX *amx, cell* params);

// A pointer to the AMX interface;
AMX* pAMX;

// PawnFunction( )
// This function invokes the SA-MP server and directly calls the
// requested function, specified by the PAWN_FUNCTION parameter.
int PawnCommand( const PAWN_FUNCTION* Command, ... )
{
	va_list vArguments; int Index, i = 1, iVarCnt = 0;
	const char *pArgs = Command->Params;
	va_start( vArguments, Command );

	if (!pAMX) return 0;

	// Get the function-index for this specific command;
	bool bVariable = false; // Variables?
	amx_FindNative( pAMX, Command->Function, &Index );
	if( Index == 2147483647 )
		return 0;	// The command cannot be found.

	// Proceed with locating the memory address for this function;
	AMX_HEADER *hdr= (AMX_HEADER *) pAMX->base;
	unsigned int dwCallAddr = (unsigned int)( ( AMX_FUNCSTUB* )
		( (char*)(hdr) + (hdr)->natives + hdr->defsize * Index) )->address;

	if( dwCallAddr == 0 )
		return 0; // Could not locate the function's address.

	// Initialize the Arguments array, in which we save all required
	// values (which are also needed by the invoked-function).
	cell *Arguments = (cell*)malloc( sizeof( cell ) * ( Command->ParamCnt + 1 ) );
	Arguments[ 0 ] = Command->ParamCnt * sizeof( cell );
	cell *physAddr [ MAX_REFERENCE_VARS ];

	// Use a while loop to loop through the list of parameters;
	while( *pArgs )
	{
		// Are we dealing with an integer parameter?
		if( *pArgs == 'i' )
			Arguments[ i ] = va_arg( vArguments, int );

		// In case we're currently up with a float.
		else if( *pArgs == 'f' )
		{
			float fValue = (float)va_arg( vArguments, double );
			Arguments[ i ] = amx_ftoc( fValue );
		}
		// Strings are slightly different, because we want their addr.
		else if( *pArgs == 's' )
		{
			// First get the string off the stack
			char* szString = va_arg( vArguments, char* ); 
			Arguments[ i ] = 0; cell* tmp;
			amx_Allot( pAMX, strlen( szString ) + 1, &Arguments[ i ], &tmp );
			amx_SetString( tmp, szString, 0, 0, strlen( szString ) + 1 );
		}
		else if( *pArgs == 'v' )
		{
			cell* tmp; // Temporary location for the physical addr.
			amx_Allot( pAMX, 1, &Arguments[ i ], &tmp );
			va_arg( vArguments, cell* ); // Just need to pop the arg.
			bVariable = 1; // Indicate that we've found a variable.
			physAddr[ iVarCnt++ ] = tmp;
		}
		else if( *pArgs == 'p' )
		{
			cell* tmp; pArgs++; // Temporary location for the string's addr.
			va_arg( vArguments, cell* ); // Pop it off the stack
			int iSize = va_arg( vArguments, int );
			amx_Allot( pAMX, iSize, &Arguments[ i ], &tmp );
			i++; Arguments[ i ] = iSize;
			bVariable = 1; physAddr[ iVarCnt++ ] = tmp;
		}

		// And to finish with, handle given variables;
		++pArgs; ++i;
	}

	va_end( vArguments );

	// Next off, we need to define the prototype for the function
	// we'll be using. Internally, so it works on Linux too.
	amx_Function_t pFunction = (amx_Function_t)dwCallAddr;
	int iRes = pFunction( pAMX, Arguments ); i = 1;
	delete Arguments;

	if( bVariable ) 
	{
		// Well wait, there are variables which we might need to return.
		pArgs = Command->Params; iVarCnt = 0;
		va_start( vArguments, Command );

		while( *pArgs )
		{
			// Check if the current argument is a variable;
			if( *pArgs == 'v' )
			{
				unsigned int* dwValue  = va_arg( vArguments, unsigned int* );
				unsigned int* dwRetVal = (unsigned int*)physAddr[ iVarCnt++ ];
				*dwValue = *dwRetVal;
				//amx_Release( pAMX, Arguments[ i ] );
			}
			else if( *pArgs == 'p' )
			{
				char* dwText = va_arg( vArguments, char* );
				pArgs++; int iSize = va_arg( vArguments, int );
				amx_GetString( dwText, physAddr[ iVarCnt++ ], 0, iSize );
			}

			else va_arg( vArguments, void* ); // Skip it
			++pArgs; ++i;
		}
	}

	// Now just return the value.
	return iRes;
}
