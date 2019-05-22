#define KONVERTIERE_SENDLOG_MESSAGES_TO_UTF16


#define _DEBUG

#define DEBUG_Messages  // Aktivieren wenn Debug-Messages ausgegeben werden sollen
						  // Dies Ausgabe von Debugmessages sollte bei System-DLL-Projekten
						  // und bei Lib-Projekten deaktiviert sein.
						  // Rechenfunktionen sollten nichts aus- sondern nur etwas 
						  // zurück-geben. 


//#define KONSOLEN_IO		// Aktivieren wenn Debug_Messages (myprintf) an eine 
                        // Konsole ausgegeben werden sollen.

#define USE_SENDLOG		// Aktivieren wenn SendLog genutzt werden soll.




//#define NO_TRY		// Aktivieren wenn mit dev++ (gcc) gearbeitet wird. Hierdurch
                // wird __try (eigenes Exception-Handling) in der Source-Datei
                // IbvStudioCommonFunctions.c deaktiviert.

#define IBV_STD			// Aktivieren nur IBV-Studio-DLL-Projekt compiliert werden soll.

#define WINDOWS_IO		// Aktivieren wenn Debug_Messages (myprintf) an ein
                        // Windows-Fenster ausgegeben werden sollen.

//#define NDEBUG /* Nur aktivieren wenn ASSERTs nicht genutzt werden sollen.    */
                 /* Über Asserts wird der Pixelzugriff überprüft und die        */
                 /* Funktionen error_msg() und  return_error_msg() realisiert   */
                 /* Bei einem Release-Projekt ist NDEBUG automatisch aktiviert. */
                 /* Bei einer Konsolenanwendung führt ein ASSERT zum Programm-  */
                 /* abbruch, bei einer Windows-Anwendung kann mit Click auf     */
                 /* "Ignore" der Programmablauf fortgeführt werden.             */




///// Ab hier nichts mehr editieren: ALLES SO LASSEN WIE ES IST !!!!

#define USE_ASSERT_FOR_ERROR  /* Wenn aktiviert, dann lösen error_msg() und  */
                              /* return_error_msg() ASSERTs aus.             */
                              /* Dies sollte bei der LIB-Erstellung          */
                              /* immer aktiv sein, denn nur dann ist die LIB */
                              /* sowohl für eine Konsolen-Anwendung als auch */
                              /* für eine Windows-Anwendung hinsichtlich     */
                              /* der Fehlermeldungen nutzbar.                */


#ifdef __cplusplus											//ifdef 4
#define PREFIX_C extern "C"{
#define SUFFIX_C }
#else													   // else 4
#define PREFIX_C
#define SUFFIX_C
#endif													   // endif 4


//DEP_1 steht für Dll-Export-Prefix-1
//DEP_2 steht für Dll-Export-Prefix-2

#ifdef  DLL_EXPORT
#define DEP_1 __declspec(dllexport)
#define DEP_2 _stdcall
#endif


#ifdef  LIB_EXPORT
#define DEP_1 extern
#define DEP_2
#endif


// Dateien includen
#include "windows.h"
#include <stdio.h>
#include <assert.h>
#ifdef ADO
#include "i:\vorlagen\includes\global.h"
#endif
#include "i:\vorlagen\includes\ibv.h"

#ifdef NO_TRY
#define __try
#define __leave
#endif

									
