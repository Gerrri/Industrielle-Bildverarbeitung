#include "..//..//sourcen//schalter.h"

#define NO_TRY  // Aktivieren wenn mit dev++ (gcc) gearbeitet wird. Hierdurch
				// wird __try (eigenes Exception-Handling) in dieserr Source-Datei
				// IbvStudioCommonFunctions.c deaktiviert.

#ifdef NO_TRY
#define __try 
#define __leave
#endif


//#pragma warning( disable : 4005 )	// Compiler-Warnung bei Makro-Redifinition deaktivieren

#include "IbvStudioCommonFunctions.h"
#include "malloc.h"
#include "stdio.h"



extern IBVSTUDIODLLINFO IbvStudioDllInfo;
extern HWND ApplictationWindowHandle;
extern CHAR CurrentFunctionName[MAX_FUNCTION_NAME_LENGTH];
extern CHAR *CurrentParamSourcePointer;
extern HWND  LogWindowHandle;

//Exportierte Funktionen (Get/Set-Methoden für Belegung der Globalen Variablen innerhalb der DLL)
IBVSTUDIODLLEXPORT BOOL	isdReturnDllInfo (pIBVSTUDIODLLINFO pIbvStudioInfo)
{
	BOOL success=FALSE;

__try
	{	
		if (pIbvStudioInfo==NULL) {success=FALSE; __leave;}
		else
		{
			CopyMemory(pIbvStudioInfo,&IbvStudioDllInfo,sizeof(IBVSTUDIODLLINFO));
			success=TRUE;
			__leave;
		}
	}

#ifndef NO_TRY
__except(EXCEPTION_EXECUTE_HANDLER)
	{
		return FALSE;
	}
#endif //NO_TRY


	return success;
}

IBVSTUDIODLLEXPORT BOOL	isdSetFunctionName (CHAR *FunctionName)
{
	BOOL success=FALSE;

 __try
	{	
		if (FunctionName==NULL) {success=FALSE;__leave;}
		else
		{
			sprintf(CurrentFunctionName,FunctionName);
			success=TRUE;
			__leave;
		}
	}

#ifndef NO_TRY
__except(EXCEPTION_EXECUTE_HANDLER)
	{
		sprintf(CurrentFunctionName,"");
		return FALSE;
	}
#endif 


	return success;
}


IBVSTUDIODLLEXPORT BOOL	isdSetParamSource (CHAR *ParamSource)
{
	BOOL success=FALSE;

 __try
	{	
		if (ParamSource==NULL) {success=FALSE;CurrentParamSourcePointer=NULL;__leave;}
		else
		{
			CurrentParamSourcePointer=ParamSource;
			success=TRUE;
			__leave;
		}
	}

#ifndef NO_TRY
__except(EXCEPTION_EXECUTE_HANDLER)
	{
		CurrentParamSourcePointer=NULL;
		return FALSE;
	}
#endif


	return success;

}

IBVSTUDIODLLEXPORT CHAR	*isdGetParamSource ()
{
	return CurrentParamSourcePointer;
}


IBVSTUDIODLLEXPORT BOOL	isdSetWindowHandle (HWND WindowHandle)
{
	BOOL success=FALSE;

 __try
	{	
		//if (!IsWindow(WindowHandle)) {success=FALSE;ApplictationWindowHandle=NULL;__leave;}
		//else
		{
			ApplictationWindowHandle=WindowHandle;
			success=TRUE;
			__leave;
		}
	}

#ifndef NO_TRY
__except(EXCEPTION_EXECUTE_HANDLER)
	{
		ApplictationWindowHandle=NULL;
		return FALSE;
	}
#endif


	return success;

}


IBVSTUDIODLLEXPORT HWND	isdGetWindowHandle ()
{
	return ApplictationWindowHandle;
}

IBVSTUDIODLLEXPORT BOOL	isdSetLogWindowHandle (HWND WindowHandle)
{
	BOOL success=FALSE;

 __try
	{	
		//if (!IsWindow(WindowHandle)) {success=FALSE;LogWindowHandle=NULL;__leave;}
		//else
		{
			LogWindowHandle=WindowHandle;
			success=TRUE;
			__leave;
		}
	}

#ifndef NO_TRY
__except(EXCEPTION_EXECUTE_HANDLER)
	{
		LogWindowHandle=NULL;
		return FALSE;
	}
#endif


	return success;

}


//Privat, diverse Hilfsfunktion Beschreibungen in der Funktionsreferenz

#ifdef KONVERTIERE_SENDLOG_MESSAGES_TO_UTF16
// Qt arbeit anscheinen nicht mit dem utf16
// Das Log-Fenster verlangt dies aber wohl
// => Der String muss vor dem versenden noch konvertiert werden
BOOL SendLogMessage(CHAR *Message,BOOL ShowTime)
{
	int MessageLength=0; 
	int TimeLength=0;
	char LogTime[20]="\0"; //char LogTime[14]="\0"; 14 war zu wenig s.u. sprintf (LogTime...
    CHAR *TempMessageBuffer=NULL;
	int nTxtLen=0;
    int i,p,d;

	SYSTEMTIME time;
	



	if (Message!=NULL)// && IsWindow(LogWindowHandle)) //String auch nicht leer ?
	{
		//Meldungszeit besorgen
		GetLocalTime(&time);
		sprintf(LogTime,"%02d:%02d:%02d Uhr - ",time.wHour, time.wMinute,time.wSecond); //LogTime wird mit in Summe 16 Chars gefüllt
		
		
		MessageLength=strlen(Message);
		TimeLength=strlen(LogTime);

		//Zwischenspeicher allokieren
        TempMessageBuffer=(char *) calloc ((2*(MessageLength+3+TimeLength)),sizeof(char));
		
		//String basteln
        d=2; // utf16 ist ASCII mit vorangestellter 0x00. Z.B. 0x0031 fuer die '1'
        p=0; // p=0: Weil bei little-endian stehen die ASCII-Werte an den Positionen 0, 2, 4, 8 usw
        if (ShowTime) {
            for(i=0;i<TimeLength;i++)
                TempMessageBuffer[(d*i)+p]= LogTime[i];

            for(i=TimeLength;i<(TimeLength+MessageLength);i++)
                TempMessageBuffer[(d*i)+p]= Message[i-TimeLength];

            TempMessageBuffer[(d*i)+p]=0x0D; // CR dran haengen
            i++;

            TempMessageBuffer[(d*i)+p]=0x0A; // LF dran haengen
            i++;

            TempMessageBuffer[(d*i)+p]=0; // Stringendezeichen noch dran haengen

        }
        else {
            for(i=0;i<MessageLength;i++)
                TempMessageBuffer[(d*i)+p]= Message[i];

            TempMessageBuffer[(d*i)+p]=0x0D; // CR dran haengen
            i++;

            TempMessageBuffer[(d*i)+p]=0x0A; // LF dran haengen
            i++;

            TempMessageBuffer[(d*i)+p]=0; // Stringendezeichen noch dran haengen

        }

		nTxtLen = GetWindowTextLength(LogWindowHandle);		
		SendMessage(LogWindowHandle, EM_SETSEL, nTxtLen, nTxtLen);	        
		SendMessage(LogWindowHandle, EM_REPLACESEL, 0, (LPARAM) TempMessageBuffer);	 
		SendMessage(LogWindowHandle, EM_SCROLLCARET, 0, 0);

		// Warten
		Sleep(10);


		//Zwischenspeicher freigeben
		
		  free(TempMessageBuffer);
			
		return TRUE;
			
	}
	
   return FALSE;

}

#else //KONVERTIERE_SENDLOG_MESSAGES_TO_UTF16
BOOL SendLogMessage(CHAR *Message,BOOL ShowTime)
{

	int MessageLength=0;
	int BufferLength=0;
	int LineCount=0;
	int TimeLength=0;
	char *KonsoleText=NULL;
	char LogTime[20]="\0"; //char LogTime[14]="\0"; 14 war zu wenig s.u. sprintf (LogTime...
	char *TempMessageBuffer=NULL;
	int nTxtLen=0;

	SYSTEMTIME time;
	

	if (Message!=NULL)// && IsWindow(LogWindowHandle)) //String auch nicht leer ?
	{
		//Meldungszeit besorgen
		GetLocalTime(&time);
		sprintf(LogTime,"%02d:%02d:%02d Uhr - ",time.wHour, time.wMinute,time.wSecond); //LogTime wird mit in Summe 16 Chars gefüllt
		
		
		MessageLength=strlen(Message);
		TimeLength=strlen(LogTime);

		//Zwischenspeicher allokieren
		TempMessageBuffer=(char *) calloc ((MessageLength+3+TimeLength),sizeof(char));
		
		//String basteln

		if (ShowTime)
			strcpy(TempMessageBuffer,LogTime);
		else
			sprintf(TempMessageBuffer,"");
		strcat(TempMessageBuffer,Message);
		strcat(TempMessageBuffer,"\x0D\x0A"); //Zeilenumbruch
		
		nTxtLen = GetWindowTextLength(LogWindowHandle);		
		SendMessage(LogWindowHandle, EM_SETSEL, nTxtLen, nTxtLen);	        
		SendMessage(LogWindowHandle, EM_REPLACESEL, 0, (LPARAM) TempMessageBuffer);	 
		SendMessage(LogWindowHandle, EM_SCROLLCARET, 0, 0);

		// Warten
		Sleep(10);


		//Zwischenspeicher freigeben
		
		  free(TempMessageBuffer);
			
		return TRUE;
			
	}
	
   return FALSE;


}
#endif // #else //KONVERTIERE_SENDLOG_MESSAGES_TO_UTF16



