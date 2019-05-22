//***************************************************
//*		Exportart der Funktionen deklarieren		*
//***************************************************

#ifdef __cplusplus
#define IBVSTUDIODLLEXPORT extern "C" __declspec (dllexport)
#else
#define IBVSTUDIODLLEXPORT __declspec (dllexport)
#endif

//Keine ASSERTIONS! Programm kümmert sich selbst um Ausnahmen!
#ifndef NDEBUG
	#define NDEBUG
#endif

#ifndef	_WINDOWS_ 
	#include "windows.h"
#endif

#ifndef _GlobalDefs_
	#define _GlobalDefs_
#endif

#ifndef _DllFunctionInfo_
	#include "DllFunctionInfo.h"
#endif

#ifndef _INC_STDIO
	#include "stdio.h"
#endif

/* LOTH
#ifndef __IBV_H
	#include "i:\vorlagen\includes\IBV_lib.h"
#endif
*/

#ifndef assert
	#include "assert.h"
#endif




#define	MAX_FUNCTION_NAME_LENGTH			 100	//Max Länge eines Dll-Funktionsnahmens
#define	MAX_FUNCTION_LINKNAME_LENGTH		 100	//MAx Länge einer Verknüpfungsbezeichnung
#define	MAX_FUNCTION_DESCRIPTION_LENGTH		 1000	//Max Länge einer Funktionsbeschreibung
#define	MAX_DLL_DESCRIPTION_LENGTH			 100	//Max Länge einer Dll-Beschreibung
#define	MAX_DLL_FUNCTIONS					  50	//Max Anzahl von Funktionen innerhalb einer DLL
#define MAX_DLL_FUNCTION_LINKS				  50	//Max Anzahl von Ein- und Ausgängen einer Funktion
#define	NOIMAGE								  -3	//Definition für kein Ein oder Ausgabebild

#define	ERR_MSG_DLL_FUNCTION			0xE0000002



//Struktur zur Speicherung einer Verbindungsbezeichnung einer DLL-Funktion
typedef struct tagIbvStudioDllFunctionLinkName
{
	CHAR						LinkNameInput[MAX_FUNCTION_LINKNAME_LENGTH];	//Eingabebildname
	CHAR						LinkNameOutput[MAX_FUNCTION_LINKNAME_LENGTH];	//Ausgabebildname

}
IBVSTUDIODLLFUNCTIONLINKNAME,*pIBVSTUDIODLLFUNCTIONLINKNAME;

//Struktur zur Speicherung von Eigenschaften einer DLL-Funktion
typedef struct tagIbvStudioDllFunctionInfo
{
	CHAR							FunctionName[MAX_FUNCTION_NAME_LENGTH];		//Funktionsname
	CHAR							FunctionDescription[MAX_FUNCTION_DESCRIPTION_LENGTH];	//Funktionsbeschreibung
	IBVSTUDIODLLFUNCTIONLINKNAME	FunctionLinkNames[MAX_DLL_FUNCTION_LINKS];				//Verbindungsbezeichnungen
	INT								FunctionInputImageCount;								//Anzahl der benötigten Eingabebilder
	INT								FunctionOutputImageCount;								//Anzahl der benötigten Ausgabebebilder
}
IBVSTUDIODLLFUNCTIONINFO,*pIBVSTUDIODLLFUNCTIONINFO;

//Struktur zur Speicherung von Eigenschaften einer DLL
typedef struct tagIbvStudioDllInfo
{
	IBVSTUDIODLLFUNCTIONINFO	IbvStudioDllFunctionInfo[MAX_DLL_FUNCTIONS];			//Feld von IBVSTUDIODLLFUNCTIONINFO-Strukturen
	CHAR						DllDescription[MAX_DLL_DESCRIPTION_LENGTH];				//Dll-Name, der im Auswahl Dialog angezeigt werden soll
}
IBVSTUDIODLLINFO,*pIBVSTUDIODLLINFO;
