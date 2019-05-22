
// Alle switches aus "schalter.h" übernehmen
#include "..//..//sourcen//schalter.h"




// ACHTUNG: Wenn nicht mit Visual-Studio sondern mit Dev++ (GCC) gearbeitet wird,
// so kann die in den folgenden aufgeführten Include-Dateien jeweils aufgeführte Library
// nicht über "pragma" eingebunden werden, sondern muss im 
// Projekt selbst als einzubindende Datei angegeben werden.
// Bei Dev++ geschieht die über 
// "Projekt-> Projekt Optionen -> Parameter -> Bibliothek hinzufügen"

// Einbinden der genutzten statischen Libs
// Hierzu die switches (DEP_1, DEP_2) aus schalter.h umdefinieren
#define DEP_1 extern
#define DEP_2
#define LIB_IMPORT		// LIB_IMPORT aktivieren
//#include "i:\vorlagen\includes\ibv_lib.h"
//#include "i:\vorlagen\includes\example.h"
// usw.
#undef LIB_IMPORT		// LIB_IMPORT deaktivieren


// Einbinden der genutzten DLLs 
// Hierzu die switches (DEP_1, DEP_2) aus schalter.h umdefinieren
// und switch DLL_IMPORT aktivieren
#undef DEP_1
#undef DEP_2
#define DEP_1 __declspec(dllimport)
#define DEP_2 _stdcall
#define DLL_IMPORT		// DLL_IMPORT aktiviren
#include "i:\vorlagen\includes\ibv_lib.h"
#include "i:\vorlagen\includes\param_parser.h"

// ###########################  ANPASSEN ANFANG ########################################
//#include "i:\vorlagen\includes\bin.h"
// Bei Nutzung mehrerer neuer Bibliotheken, muss auch hier entsprechend erweiter werden.
// ###########################  ANPASSEN ENDE   ########################################

// usw. 
#undef DLL_IMPORT		// DLL_IMPORT deaktivieren

// Änderungen an den switches wieder rückgängig machen
#undef DLL_IMPORT		// DLL_IMPORT deaktivieren


#include "..//..//sourcen//schalter.h"	// durch erneutes includen von schalter.h werden DEP_1 und DEP_2 
										// restauriert


//#pragma warning( default : 4005 )	// Comiler-Warnung bei Makro-Redifinition wierder aktivieren



// Includen von Dateien
#include "Function.h"


#ifndef _GlobalDefs_
	#include "GlobalDefs.h"
#endif




extern CHAR CurrentFunctionName[MAX_FUNCTION_NAME_LENGTH];
extern CHAR *CurrentParamSourcePointer;



// ###########################  ANPASSEN ANFANG ########################################
#include "..//..//sourcen//projekt_6_main.h"
// ###########################  ANPASSEN ENDE   ########################################



//IBVSTUDIODLLEXPORT BOOL DLLFUNCTIONNAME0 (CHAR* ParamStringPointer)
IBVSTUDIODLLEXPORT BOOL DLLFUNCTIONNAME0 ()
{

// ###########################  ANPASSEN ANFANG ########################################
    main_projekt_6(CurrentFunctionName, CurrentParamSourcePointer);
// ###########################  ANPASSEN ENDE   ########################################
	
	return TRUE;
}



// ###########################  ERWEITERN ANFANG ########################################
#ifdef ERWEITERN
IBVSTUDIODLLEXPORT BOOL DLLFUNCTIONNAME1 (CHAR* ParamStringPointer)
{

	main_sleep(CurrentFunctionName, CurrentParamSourcePointer);

	return TRUE;
}
#endif //ERWEITERN
// ###########################  ERWEITERN ENDE   ########################################

