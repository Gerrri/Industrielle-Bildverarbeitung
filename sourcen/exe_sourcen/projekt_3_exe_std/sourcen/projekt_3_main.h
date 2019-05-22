
#include ".\std_sourcen\qt_debug_bug.h"

// Bei einer Erweiterung bzw. Änderung müssen die folgenden Datei
// an den durch AENDERN bzw. ERWEITERN gekennzeichneten Stellen sinngemäß
// erweitert bzw. angepasst werden. Eine Erweiterung steht dort jeweils schon
// schematisch; ist allerdings auskommentiert:

// 1.) DLLFunctionInfo.h
// 2.) IBVStudioDllEntry.c
// 3.) Änderung der Parameterdatei aus IBV-Studio heraus
// 4.) Function.h
// 5.) Function.c



int main_faltung (char *fct_name, char *cmd_line)
{
    char ImgPathBuffer[MAX_PATH]="\0";


    PIC sPic_In0,*Pic_In0=&sPic_In0;


    PIC sPic_Out0,*Pic_Out0=&sPic_Out0;


    int x, y, u, v, ret;

    float wert;


    char Buffer[10000]="\0";
    char maskendatei[1001]="\0";

    CONVMASK sMaske, *Maske=&sMaske;

    // Ausgabe des Funktionsnamens
    sprintf(Buffer,"fct_nammee: %s",fct_name);
    SendLog(Buffer,TRUE);

    // Ausgabe der cmd_line, d.h. der den Funktionsnamen selektierten Passage
    // der Parameterdatei
    sprintf(Buffer,"Es folgt die cmd_line::");
    SendLog(Buffer,TRUE);
    SendLog(cmd_line,TRUE);


    // Einlesen der Parameter als ASCII (String)
    if(FALSE==GetParamStr(cmd_line, fct_name,"Maskendatei",maskendatei,1000)) {
        SendLog("GetParamStr fehlgeschlagen",TRUE);
        return (FALSE);
    }


    //Dateipfade für Eingabebilder besorgen und Bilder einlesen
    GetInputImagePath(cmd_line, fct_name, 0,ImgPathBuffer);
    Read_Pic(ImgPathBuffer,Pic_In0,FLOAT_IMG);


    //Ausgabebilder deklarieren und Speicher allokieren
    Pic_Out0->maxcol=Pic_In0->maxcol;
    Pic_Out0->maxrow=Pic_In0->maxrow;
    Pic_Out0->type=FLOAT_IMG;

    Alloc_Pic_Data(Pic_Out0);


    // Einlesen der Faltungsmaske
    ret= alloc_and_read_conv_mask(maskendatei, Maske); //example(Pic_In0, Pic_Out0, schwelle);

    if( ret!=0 )
    {
        sprintf(Buffer,"Fehler-Nr.: %d in alloc_and_read_conv_mask()!", ret);
        SendLog(Buffer,FALSE);
    }
    else {
        SendLog("alloc_and_read_conv_mask() ... erfolgreich durchgefuehrt",FALSE);
    }


    // Testausgabe der eingelesenen Faltungsmaske (Maskenwerte)
    /* Die Faltungsmaske wird durch die folgende  (in faltung.h. aufgeführte) Struktur
       CONVMASK definiert. Der Aufbau ist ähnlich zum Aufbau der Struktur PIC.

          typedef struct convolution_mask {
            int x_size;			// Größe der Faltungsmaske in x-Richtung
            int y_size;			// Größe der Faltungsmaske in y-Richtung
            int **ftwert;		// Pointer auf zweidimensionales "Feld" für noch nicht normierte Maskenwerte
            int ftwichtkoef;	// Wichtungsfaktor für die Normierung aller Maskenwerte
            }   CONVMASK;

        Die Anwendung der Struktur wird durch den folgenden Source-Code zur
        Ausgabe der Maskenwerte auf dem Monitor erläutert.
    */

    for (v=0; v<Maske->y_size; v++) // Alle Zeilen der Maske bearbeiten
    {
        for (u=0; u<Maske->x_size; u++) // Alle Maskenwerte innerhalb der Zeile bearbeiten
        {
            wert= ( (float) Maske->ftwert[v][u]) / Maske->ftwichtkoef;	// Nicht normierten Maskenwert holen
                                                                        // und mit dem Wichtungsfaktor normieren.

            sprintf(Buffer,"Maske[Zeile=%d][Spalte=%d]=%f", v, u, wert  ); // Ausgabe des normierten Maskenwertes
            SendLog(Buffer,FALSE);
        }
    }


    // AB HIER DEN EIGENEN SOURCE-CODE EINFÜGEN

    // Source Code für einen Algorithmus (hier kopieren)
    for (y=0; y<Pic_In0->maxrow; y++)
    {
        for (x=0; x<Pic_In0->maxcol; x++)
        {

            f_pixel(Pic_Out0,x,y)=f_pixel(Pic_In0,x,y);

        }
    }

    // BIS HIER DEN EIGENEN SOURCE-CODE EINFÜGEN


    //Dateipfade für Ausgabebilder besorgen und Bilder abspeichern
    GetOutputImagePath(cmd_line, fct_name, 0,ImgPathBuffer);
    Write_Pic(ImgPathBuffer,Pic_Out0);


    //Speicher freigeben
    Free_Pic_Data(Pic_In0);
    Free_Pic_Data(Pic_Out0);
    free_conv_mask(Maske);

    return TRUE;
}



