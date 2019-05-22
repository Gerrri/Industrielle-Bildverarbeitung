#ifndef	_WINDOWS_ 
	#include "windows.h"
#endif

#ifndef _IbvStudioCommonFunctions_
	#define _IbvStudioCommonFunctions_
#endif

#ifndef _GlobalDefs_
	#include "GlobalDefs.h"
#endif


//Exportfunktion für Kommunikation mit Hauptprogramm
IBVSTUDIODLLEXPORT BOOL	isdReturnDllInfo (pIBVSTUDIODLLINFO pIbvStudioInfo);
IBVSTUDIODLLEXPORT BOOL	isdSetFunctionName (CHAR *FunctionName);
IBVSTUDIODLLEXPORT BOOL	isdSetParamSource (CHAR *ParamSource);

IBVSTUDIODLLEXPORT CHAR	*isdGetParamSource ();
IBVSTUDIODLLEXPORT BOOL	isdSetWindowHandle (HWND WindowHandle);
IBVSTUDIODLLEXPORT HWND	isdGetWindowHandle ();
IBVSTUDIODLLEXPORT BOOL	isdSetLogWindowHandle (HWND WindowHandle);

//Interne Funktionen zur Auswertung des Parameterfiles

//  Summary:
//     Sendet eine Nachricht an einen "LogTab" - von Ibv-Studio zur Ausgabe zur Laufzeit einer Dll-Funktion
//  Arguments:
//      Message - Meldung, die ausgegeben werden soll
//		ShowTime - True = Der Meldung wird die Uhrzeit vorangestellt, False =  Meldung wird wie in "Message" enthalten, ausgegeben
//  Return Value:
//      True bei Erfolg,
//		False, sonst
//  Description:
//     Sendet eine Nachricht an einen "LogTab" - von Ibv-Studio zur Ausgabe zur Laufzeit einer Dll-Funktion
//		Ersatz für das gute,alte "myprintf"
BOOL SendLogMessage(CHAR *Message,BOOL ShowTime);
