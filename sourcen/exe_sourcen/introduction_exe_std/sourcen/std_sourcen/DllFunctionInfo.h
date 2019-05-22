//Hier kann der Funktionsexport konfiguriert werden

#ifndef _DllFunctionInfo_
	#define _DllFunctionInfo_
#endif


//Dll-Name,der im Dll-Auswahldialog angezeigt werden soll
#define	DLLDESCRIPTION				"introduction_std_vc.dll" //AENDERN


//*******************************************
//*		Defs für DLL-Funktion 0				*
//*******************************************

#define	DLLFUNCTIONNAME0			A_introduction		//Funktionsname für Funktionsexport (Muß identisch mit //AENDERN
#define	DLLFUNCTIONNAMESTRING0		"A_introduction"		//DLLFUNCTIONNAMESTRING0 sein ! //AENDERN
#define	DLLFUNCTIONDESCRIPTION0		"Konvertiert ein RGB- in drei Grauwertbilder-Bilder und berechnet die Gradientenkomponenten"	//Beschreibung der Funktion
				
#define	DLLFUNCTIONINPUTCOUNT0		0					//Anzahl der Eingabebilder (n-1) (oder NOIMAGE)
	#define DLLFUNCTION0INPUTNAME0	"RGB-Eingabebild"		//Name von Eingabebild 0 (Wird in Ibv-Studio angezeigt)
	#define DLLFUNCTION0INPUTNAME1	""					//Name von Eingabebild 1 (Wird in Ibv-Studio angezeigt)
	#define DLLFUNCTION0INPUTNAME2	""					//....
	#define DLLFUNCTION0INPUTNAME3	""					//(Anm.: Werden die Namensbezeichnungen nicht definiert,
	#define DLLFUNCTION0INPUTNAME4	""					//benennt Ibv-Studio diese autom. mit "i: PicIn" (i=0-(n-1))
	//...
#define	DLLFUNCTIONOUTPUTCOUNT0		4					//Anzahl der Ausgabebilder (n-1) (oder NOIMAGE)
	#define DLLFUNCTION0OUTPUTNAME0	"R-Ausgabe-Bild"	//Name von Ausgabebild 0 (Wird in Ibv-Studio angezeigt)
	#define DLLFUNCTION0OUTPUTNAME1	"G-Ausgabe-Bild"	//Name von Ausgabebild 1 (Wird in Ibv-Studio angezeigt)
	#define DLLFUNCTION0OUTPUTNAME2	"B-Ausgabe-Bild"					//...
	#define DLLFUNCTION0OUTPUTNAME3	"X-Steigung"		//(Anm.: Werden die Namensbezeichnungen nicht definiert,
	#define DLLFUNCTION0OUTPUTNAME4	"Y-Steigung"		//benennt Ibv-Studio diese autom. mit "i: PicOut" (i=0-(n-1))
	//...


#ifdef ERWEITERN
//*******************************************
//*		Defs für DLL-Funktion 1				*
//*******************************************

#define	DLLFUNCTIONNAME1			B_???
#define	DLLFUNCTIONNAMESTRING1		"B_???"
#define	DLLFUNCTIONDESCRIPTION1		"???"

#define	DLLFUNCTIONINPUTCOUNT1		0
	#define DLLFUNCTION1INPUTNAME0	"Hin0"
	#define DLLFUNCTION1INPUTNAME1	""
	#define DLLFUNCTION1INPUTNAME2	""
	#define DLLFUNCTION1INPUTNAME3	""
	#define DLLFUNCTION1INPUTNAME4	""

#define	DLLFUNCTIONOUTPUTCOUNT1		0
	#define DLLFUNCTION1OUTPUTNAME0	"Hout0"
	#define DLLFUNCTION1OUTPUTNAME1	""
	#define DLLFUNCTION1OUTPUTNAME2	""
	#define DLLFUNCTION1OUTPUTNAME3	""
	#define DLLFUNCTION1OUTPUTNAME4	""

#endif //ERWEITERN



//Defs für n-te Funktion in DLL
//...
//...
//...
