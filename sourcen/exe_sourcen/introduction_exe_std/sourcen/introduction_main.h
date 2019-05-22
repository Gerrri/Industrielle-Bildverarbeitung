
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



int main_introduction (char *fct_name, char *cmd_line) //AENDERN
{

    char ImgPathBuffer[MAX_PATH]="\0";
    CHAR Buffer[10000]="\0";

    PIC sPic_In0,*Pic_In0=&sPic_In0;
    PIC sPic_Byte_In0,*Pic_Byte_In0=&sPic_Byte_In0;

    PIC sPic_OutR,*Pic_OutR=&sPic_OutR;
    PIC sPic_OutG,*Pic_OutG=&sPic_OutG;
    PIC sPic_OutB,*Pic_OutB=&sPic_OutB;
    PIC sPic_XGrad,*Pic_XGrad=&sPic_XGrad;
    PIC sPic_YGrad,*Pic_YGrad=&sPic_YGrad;

    int x, y;
    int abstand;



    //### 1.) ### Einige Standard-Debugausgaben
    sprintf(Buffer,"fct_name_3_Hello: %s",fct_name);
    SendLog(Buffer,TRUE); // TRUE => Ausgabe mit vorangestellter Uhrzeit

    sprintf(Buffer,"Es folgt die cmd_line:");
    SendLog(Buffer,TRUE);
    SendLog(cmd_line,TRUE);

    //### 2.) ### Einlesen der Parameter
    if(FALSE==GetParamStr(cmd_line, fct_name,"Abstand",Buffer,100)) {
        SendLog("GetParamStr fehlgeschlagen",TRUE);
        return (FALSE);
    }

    abstand=atoi(Buffer);


    ////### 3.) ### Ueberpruefen der Parameter
    sprintf (Buffer,"Wert fuer Abstand: %d", abstand); // den Wert von abstand ausgeben
    SendLog(Buffer,FALSE); //FALSE => Ausgabe ohne Uhrzeit

    if (abstand <= 0) {				// den Wert von abstand ueberpruefen
        SendLog("Der Wert fuer abstand muss >= 0 sein.",TRUE);
        return (FALSE);
    }

    //### 4.) ### Einlesen der Eingabebilder
    GetInputImagePath(cmd_line, fct_name, 0,ImgPathBuffer); // Eingabebild 0 einlesen
    Read_Pic(ImgPathBuffer,Pic_In0,RGB_IMG);		// Einlesen als RGB-Farbbild
    Read_Pic(ImgPathBuffer,Pic_Byte_In0,BYTE_IMG);	// Einlesen als Byte-Bild. Hierbei wird automatisch konvertiert, also so dass ein Grauwertbild berechnet wird.



    //### 5.) ### Ausgabebilder deklarieren und Speicher allokieren
    Pic_OutR->maxcol=Pic_In0->maxcol;
    Pic_OutR->maxrow=Pic_In0->maxrow;
    Pic_OutR->type=BYTE_IMG;
    Alloc_Pic_Data(Pic_OutR);

    Pic_OutG->maxcol=Pic_In0->maxcol;
    Pic_OutG->maxrow=Pic_In0->maxrow;
    Pic_OutG->type=BYTE_IMG;
    Alloc_Pic_Data(Pic_OutG);

    Pic_OutB->maxcol=Pic_In0->maxcol;
    Pic_OutB->maxrow=Pic_In0->maxrow;
    Pic_OutB->type=BYTE_IMG;
    Alloc_Pic_Data(Pic_OutB);

    Pic_XGrad->maxcol=Pic_In0->maxcol;
    Pic_XGrad->maxrow=Pic_In0->maxrow;
    Pic_XGrad->type=FLOAT_IMG;
    Alloc_Pic_Data(Pic_XGrad);

    Pic_YGrad->maxcol=Pic_In0->maxcol;
    Pic_YGrad->maxrow=Pic_In0->maxrow;
    Pic_YGrad->type=FLOAT_IMG;
    Alloc_Pic_Data(Pic_YGrad);

    //### 6.) ### Aufruf der eigentlichen Bildverarbeitungsfunktionalitaet
    // Aufteilung in R, G und B
    for (y=0; y<Pic_In0->maxrow; y++)
        for (x=0; x<Pic_In0->maxcol; x++)
        {
            // Aufteilung in R, G und B
            b_pixel(Pic_OutR,x,y) = rgb_pixel(Pic_In0,x,y)->r;
            b_pixel(Pic_OutG,x,y) = rgb_pixel(Pic_In0,x,y)->g;
            b_pixel(Pic_OutB,x,y) = rgb_pixel(Pic_In0,x,y)->b;
        }


    // Wegen Rand die Ausgabebilder fuer die Gradientenkomponenten mit Nullen vorbelegen
    for (y=0; y < Pic_Byte_In0->maxrow; y++)
        for (x=0; x < Pic_Byte_In0->maxcol; x++)
        {
            f_pixel(Pic_XGrad,x,y) = 0;
            f_pixel(Pic_YGrad,x,y) = 0;

        }

    // Gradientenkomponenten berechnen
    for (y=abstand; y < Pic_Byte_In0->maxrow - abstand; y++)
        for (x=abstand; x < Pic_Byte_In0->maxcol - abstand; x++)
        {
            f_pixel(Pic_XGrad,x,y) = (b_pixel(Pic_Byte_In0,x+abstand,y) -  b_pixel(Pic_Byte_In0,x-abstand,y)) / (2*abstand+1);
            f_pixel(Pic_YGrad,x,y) = (b_pixel(Pic_Byte_In0,x,y+abstand) -  b_pixel(Pic_Byte_In0,x,y-abstand)) / (2*abstand+1);

        }

    //### 7.) ### Dateipfad für Ausgabebilder besorgen und Bilder abspeichern
    GetOutputImagePath(cmd_line, fct_name, 0,ImgPathBuffer);
    Write_Pic(ImgPathBuffer,Pic_OutR);

    GetOutputImagePath(cmd_line, fct_name, 1,ImgPathBuffer);
    Write_Pic(ImgPathBuffer,Pic_OutG);

    GetOutputImagePath(cmd_line, fct_name, 2,ImgPathBuffer);
    Write_Pic(ImgPathBuffer,Pic_OutB);

    GetOutputImagePath(cmd_line, fct_name, 3,ImgPathBuffer);
    Write_Pic(ImgPathBuffer,Pic_XGrad);

    GetOutputImagePath(cmd_line, fct_name, 4,ImgPathBuffer);
    Write_Pic(ImgPathBuffer,Pic_YGrad);


    //### 8.) ### Speicher für die allokierten Bilder wieder freigeben
    Free_Pic_Data(Pic_In0);
    Free_Pic_Data(Pic_Byte_In0);
    Free_Pic_Data(Pic_OutR);
    Free_Pic_Data(Pic_OutG);
    Free_Pic_Data(Pic_OutB);
    Free_Pic_Data(Pic_XGrad);
    Free_Pic_Data(Pic_YGrad);

    return TRUE;
}


