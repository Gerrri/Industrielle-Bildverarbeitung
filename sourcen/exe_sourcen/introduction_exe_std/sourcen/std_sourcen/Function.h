#ifndef	_WINDOWS_ 
	#include "windows.h"
#endif


#ifndef _IbvStudioCommonFunctions_
	#include "IbvStudioCommonFunctions.h"
#endif


//Exportierte Ibv-Dll-Funktionen (Source-Code unter Function.c)
//IBVSTUDIODLLEXPORT BOOL DLLFUNCTIONNAME0 (CHAR* ParamStringPointer);
IBVSTUDIODLLEXPORT BOOL DLLFUNCTIONNAME0 ();


// ###########################  ERWEITERN ANFANG ########################################
#ifdef ERWEITERN
IBVSTUDIODLLEXPORT BOOL DLLFUNCTIONNAME1 (CHAR* ParamStringPointer);	
#endif //ERWEITERN
// ###########################  ERWEITERN ENDE    ########################################
