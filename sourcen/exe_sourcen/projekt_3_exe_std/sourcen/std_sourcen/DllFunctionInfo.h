//Hier kann der Funktionsexport konfiguriert werden

#ifndef _DllFunctionInfo_
	#define _DllFunctionInfo_
#endif



// ###########################  ANPASSEN ANFANG ########################################

//Dll-Name,der im Dll-Auswahldialog angezeigt werden soll
#define	DLLDESCRIPTION				"projekt_3_std_vc.dll"


//*******************************************
//*		Defs für DLL-Funktion 0				*
//*******************************************

#define	DLLFUNCTIONNAME0			A_faltung		//Funktionsname für Funktionsexport (Muß identisch mit
#define	DLLFUNCTIONNAMESTRING0		"A_faltung"		//DLLFUNCTIONNAMESTRING0 sein !
#define	DLLFUNCTIONDESCRIPTION0		"Faltung eines Bildes"	//Beschreibung der Funktion
				
#define	DLLFUNCTIONINPUTCOUNT0		0					//Anzahl der Eingabebilder (n-1) (oder NOIMAGE)
	#define DLLFUNCTION0INPUTNAME0	"In"		//Name von Eingabebild 0 (Wird in Ibv-Studio angezeigt)
	#define DLLFUNCTION0INPUTNAME1	""					//Name von Eingabebild 1 (Wird in Ibv-Studio angezeigt)
	#define DLLFUNCTION0INPUTNAME2	""					//....
	#define DLLFUNCTION0INPUTNAME3	""					//(Anm.: Werden die Namensbezeichnungen nicht definiert,
	#define DLLFUNCTION0INPUTNAME4	""					//benennt Ibv-Studio diese autom. mit "i: PicIn" (i=0-(n-1))
	//...
#define	DLLFUNCTIONOUTPUTCOUNT0		0					//Anzahl der Ausgabebilder (n-1) (oder NOIMAGE)
	#define DLLFUNCTION0OUTPUTNAME0	"Out"		//Name von Ausgabebild 0 (Wird in Ibv-Studio angezeigt)
	#define DLLFUNCTION0OUTPUTNAME1	""					//Name von Ausgabebild 1 (Wird in Ibv-Studio angezeigt)
	#define DLLFUNCTION0OUTPUTNAME2	""					//...
	#define DLLFUNCTION0OUTPUTNAME3	""					//(Anm.: Werden die Namensbezeichnungen nicht definiert,
	#define DLLFUNCTION0OUTPUTNAME4	""					//benennt Ibv-Studio diese autom. mit "i: PicOut" (i=0-(n-1))
	//...

// ###########################  ANPASSEN ENDE ########################################





// ###########################  ERWEITERN ANFANG ########################################
#ifdef ERWEITERN 
//*******************************************
//*		Defs für DLL-Funktion 1				*
//*******************************************


#define	DLLFUNCTIONNAME1			B_Sleep
#define	DLLFUNCTIONNAMESTRING1		"B_Sleep"
#define	DLLFUNCTIONDESCRIPTION1		"Schläft eine Weile..."

#define	DLLFUNCTIONINPUTCOUNT1		0
	#define DLLFUNCTION1INPUTNAME0	"In0"
	#define DLLFUNCTION1INPUTNAME1	""
	#define DLLFUNCTION1INPUTNAME2	""
	#define DLLFUNCTION1INPUTNAME3	""
	#define DLLFUNCTION1INPUTNAME4	""

#define	DLLFUNCTIONOUTPUTCOUNT1		0
	#define DLLFUNCTION1OUTPUTNAME0	"Out0"
	#define DLLFUNCTION1OUTPUTNAME1	""
	#define DLLFUNCTION1OUTPUTNAME2	""
	#define DLLFUNCTION1OUTPUTNAME3	""
	#define DLLFUNCTION1OUTPUTNAME4	""

#endif //ERWEITERN
// ###########################  ERWEITERN ENDE  ########################################



