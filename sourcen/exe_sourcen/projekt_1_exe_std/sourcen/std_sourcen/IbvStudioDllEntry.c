#ifndef	_WINDOWS_ 
	#include "windows.h"
#endif

#ifndef _GlobalDefs_
	#include "GlobalDefs.h"
#endif

#ifndef _INC_STDIO
	#include "stdio.h"
#endif



//Erzeugen der Dll-Infostruktur an die Definitionen aus "DllFunctionInfo.h"

//DLL-Funktion 0
IBVSTUDIODLLFUNCTIONINFO IbvStudioDllFunctionInfo0={DLLFUNCTIONNAMESTRING0,DLLFUNCTIONDESCRIPTION0,
                                                    {   DLLFUNCTION0INPUTNAME0,DLLFUNCTION0OUTPUTNAME0,
														DLLFUNCTION0INPUTNAME1,DLLFUNCTION0OUTPUTNAME1,
														DLLFUNCTION0INPUTNAME2,DLLFUNCTION0OUTPUTNAME2,
														DLLFUNCTION0INPUTNAME3,DLLFUNCTION0OUTPUTNAME3,
                                                        DLLFUNCTION0INPUTNAME4,DLLFUNCTION0OUTPUTNAME4,
                                                    },
													DLLFUNCTIONINPUTCOUNT0,DLLFUNCTIONOUTPUTCOUNT0};


//DLL-Funktion 1
IBVSTUDIODLLFUNCTIONINFO IbvStudioDllFunctionInfo1={DLLFUNCTIONNAMESTRING1,DLLFUNCTIONDESCRIPTION1,
                                                    {
                                                        DLLFUNCTION1INPUTNAME0,DLLFUNCTION1OUTPUTNAME0,
                                                        DLLFUNCTION1INPUTNAME1,DLLFUNCTION1OUTPUTNAME1,
                                                        DLLFUNCTION1INPUTNAME2,DLLFUNCTION1OUTPUTNAME2,
                                                        DLLFUNCTION1INPUTNAME3,DLLFUNCTION1OUTPUTNAME3,
                                                        DLLFUNCTION1INPUTNAME4,DLLFUNCTION1OUTPUTNAME4,
                                                    },
                                                    DLLFUNCTIONINPUTCOUNT1,DLLFUNCTIONOUTPUTCOUNT1};

//DLL-Funktion 2
IBVSTUDIODLLFUNCTIONINFO IbvStudioDllFunctionInfo2={DLLFUNCTIONNAMESTRING2,DLLFUNCTIONDESCRIPTION2,
                                                    {
                                                        DLLFUNCTION2INPUTNAME0,DLLFUNCTION2OUTPUTNAME0,
                                                        DLLFUNCTION2INPUTNAME1,DLLFUNCTION2OUTPUTNAME1,
                                                        DLLFUNCTION2INPUTNAME2,DLLFUNCTION2OUTPUTNAME2,
                                                        DLLFUNCTION2INPUTNAME3,DLLFUNCTION2OUTPUTNAME3,
                                                        DLLFUNCTION2INPUTNAME4,DLLFUNCTION2OUTPUTNAME4,
                                                    },
                                                    DLLFUNCTIONINPUTCOUNT2,DLLFUNCTIONOUTPUTCOUNT2};






// ###########################  ERWEITERN ANFANG ########################################
#ifdef ERWEITERN
//DLL-Funktion 1
IBVSTUDIODLLFUNCTIONINFO IbvStudioDllFunctionInfo1={DLLFUNCTIONNAMESTRING1,DLLFUNCTIONDESCRIPTION1,
													{
														DLLFUNCTION1INPUTNAME0,DLLFUNCTION1OUTPUTNAME0,
														DLLFUNCTION1INPUTNAME1,DLLFUNCTION1OUTPUTNAME1,
														DLLFUNCTION1INPUTNAME2,DLLFUNCTION1OUTPUTNAME2,
														DLLFUNCTION1INPUTNAME3,DLLFUNCTION1OUTPUTNAME3,
														DLLFUNCTION1INPUTNAME4,DLLFUNCTION1OUTPUTNAME4,
													},
													DLLFUNCTIONINPUTCOUNT1,DLLFUNCTIONOUTPUTCOUNT1};
#endif //ERWEITERN
// ###########################  ERWEITERN ENDE   ########################################





IBVSTUDIODLLINFO IbvStudioDllInfo;					//Dll-Infostruktur dieser Dll

HWND ApplictationWindowHandle;						//Fensterhandle von Ibv-Studio
HWND LogWindowHandle;								//Handle für LogWindow von Ibv-Studio
CHAR CurrentFunctionName[MAX_FUNCTION_NAME_LENGTH];	//Aktuelll aufgerufene Funktion
CHAR *CurrentParamSourcePointer=NULL;				//Pointer auf Parameterdateistring


//Dll-Einsprungfunktion
BOOL APIENTRY DllMain( HINSTANCE  hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{

	switch(ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			//Dll-Infostruktur dieser Dll initialisieren
			ZeroMemory(&IbvStudioDllInfo,sizeof(IBVSTUDIODLLINFO));

			// DLL-Funktion 0
			IbvStudioDllInfo.IbvStudioDllFunctionInfo[0]=IbvStudioDllFunctionInfo0;

            // DLL-Funktion 1
            IbvStudioDllInfo.IbvStudioDllFunctionInfo[1]=IbvStudioDllFunctionInfo1;

            // DLL-Funktion 1
            IbvStudioDllInfo.IbvStudioDllFunctionInfo[2]=IbvStudioDllFunctionInfo2;



// ###########################  ERWEITERN ANFANG ########################################
#ifdef ERWEITERN
			// DLL-Funktion 1
			IbvStudioDllInfo.IbvStudioDllFunctionInfo[1]=IbvStudioDllFunctionInfo1;
#endif //ERWEITERN
// ###########################  ERWEITERN ENDE   ########################################


			
		

			sprintf(IbvStudioDllInfo.DllDescription,"%s",DLLDESCRIPTION);
		break;
		
		case DLL_PROCESS_DETACH:		
		break;
	}
    return TRUE;
}
