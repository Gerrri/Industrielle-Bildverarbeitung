//Hier kann der Funktionsexport konfiguriert werden

#ifndef _DllFunctionInfo_
	#define _DllFunctionInfo_
#endif



// ###########################  ANPASSEN ANFANG ########################################

//Dll-Name,der im Dll-Auswahldialog angezeigt werden soll
#define	DLLDESCRIPTION				"projekt_1_std_vc.dll"


//*******************************************
//*		Defs für DLL-Funktion 0				*
//*******************************************

#define	DLLFUNCTIONNAME0			A_hist_ausgleich		//Funktionsname für Funktionsexport (Muß identisch mit
#define	DLLFUNCTIONNAMESTRING0		"A_hist_ausgleich"		//DLLFUNCTIONNAMESTRING0 sein !
#define	DLLFUNCTIONDESCRIPTION0		"Histogrammausgleich"	//Beschreibung der Funktion
				
#define	DLLFUNCTIONINPUTCOUNT0		0					//Anzahl der Eingabebilder (n-1) (oder NOIMAGE)
	#define DLLFUNCTION0INPUTNAME0	"Bild-In"		//Name von Eingabebild 0 (Wird in Ibv-Studio angezeigt)
	#define DLLFUNCTION0INPUTNAME1	""					//Name von Eingabebild 1 (Wird in Ibv-Studio angezeigt)
	#define DLLFUNCTION0INPUTNAME2	""					//....
	#define DLLFUNCTION0INPUTNAME3	""					//(Anm.: Werden die Namensbezeichnungen nicht definiert,
	#define DLLFUNCTION0INPUTNAME4	""					//benennt Ibv-Studio diese autom. mit "i: PicIn" (i=0-(n-1))
	//...
#define	DLLFUNCTIONOUTPUTCOUNT0		0					//Anzahl der Ausgabebilder (n-1) (oder NOIMAGE)
	#define DLLFUNCTION0OUTPUTNAME0	"Bild-Out"		//Name von Ausgabebild 0 (Wird in Ibv-Studio angezeigt)
	#define DLLFUNCTION0OUTPUTNAME1	""					//Name von Ausgabebild 1 (Wird in Ibv-Studio angezeigt)
	#define DLLFUNCTION0OUTPUTNAME2	""					//...
	#define DLLFUNCTION0OUTPUTNAME3	""					//(Anm.: Werden die Namensbezeichnungen nicht definiert,
	#define DLLFUNCTION0OUTPUTNAME4	""					//benennt Ibv-Studio diese autom. mit "i: PicOut" (i=0-(n-1))
	//...
// ###########################  ANPASSEN ENDE ########################################



//*******************************************
//*		Defs für DLL-Funktion 1				*
//*******************************************

#define	DLLFUNCTIONNAME1			B_rgb2hsi
#define	DLLFUNCTIONNAMESTRING1		"B_rgb2hsi"
#define	DLLFUNCTIONDESCRIPTION1		"RGB->HSI"

#define	DLLFUNCTIONINPUTCOUNT1		0
	#define DLLFUNCTION1INPUTNAME0	"RGB-Bild"
	#define DLLFUNCTION1INPUTNAME1	""
	#define DLLFUNCTION1INPUTNAME2	""
	#define DLLFUNCTION1INPUTNAME3	""
	#define DLLFUNCTION1INPUTNAME4	""

#define	DLLFUNCTIONOUTPUTCOUNT1		2
	#define DLLFUNCTION1OUTPUTNAME0	"FLOAT-H-Bild"
	#define DLLFUNCTION1OUTPUTNAME1	"FLOAT-S-Bild"
	#define DLLFUNCTION1OUTPUTNAME2	"FLOAT-I-Bild"
	#define DLLFUNCTION1OUTPUTNAME3	""
	#define DLLFUNCTION1OUTPUTNAME4	""



//*******************************************
//*		Defs für DLL-Funktion 2				*
//*******************************************

#define	DLLFUNCTIONNAME2			C_hsi2rgb
#define	DLLFUNCTIONNAMESTRING2		"C_hsi2rgb"
#define	DLLFUNCTIONDESCRIPTION2		"HSI->RGB"

#define	DLLFUNCTIONINPUTCOUNT2		2
	#define DLLFUNCTION2INPUTNAME0	"FLOAT-H-Bild"
	#define DLLFUNCTION2INPUTNAME1	"FLOAT-S-Bild"
	#define DLLFUNCTION2INPUTNAME2	"FLOAT-I-Bild"
	#define DLLFUNCTION2INPUTNAME3	""
	#define DLLFUNCTION2INPUTNAME4	""

#define	DLLFUNCTIONOUTPUTCOUNT2		0
	#define DLLFUNCTION2OUTPUTNAME0	"RGB-Bild"
	#define DLLFUNCTION2OUTPUTNAME1	""
	#define DLLFUNCTION2OUTPUTNAME2	""
	#define DLLFUNCTION2OUTPUTNAME3	""
	#define DLLFUNCTION2OUTPUTNAME4	""



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



