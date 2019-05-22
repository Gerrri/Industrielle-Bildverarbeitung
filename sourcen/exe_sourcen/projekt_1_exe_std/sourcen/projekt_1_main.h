﻿
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


int main_hist_ausgleich (char *fct_name, char *cmd_line)
{
    char ImgPathBuffer[MAX_PATH]="\0";

    PIC sPic_In0,*Pic_In0=&sPic_In0;

    PIC sPic_Out0,*Pic_Out0=&sPic_Out0;

    int schwelle, x, y;

    BYTE_IBV byte_schwelle;

    CHAR Buffer[100]="\0";


    sprintf(Buffer,"fct_name himo: %s",fct_name);
    SendLog(Buffer,TRUE);


    // Parameter einlesen (als ASCII) und ggf. von ASCII in andere Datentypen konvertieren
    if(FALSE==GetParamStr(cmd_line, fct_name,"Dummy-Parameter",Buffer,100)) {
        SendLog("GetParamStr fehlgeschlagen",TRUE);
        return (FALSE);
    }

    schwelle=atoi(Buffer);

    // Wert für schwelle überprüfen und ggf. Fehler melden
    if (schwelle <0 || schwelle >255) {
        SendLog("Falscher Wert für Bin-Schwelle",TRUE);
        return (FALSE);
    }
    else{
        byte_schwelle=(BYTE_IBV) schwelle;
    }

    //Eingelesenen und konvertierten Wert für schwelle ausgeben
    SendLog("Parameter eingelesen",TRUE);
    sprintf(Buffer,"Schwelle = %d",schwelle);
    SendLog(Buffer,TRUE);


    //Dateipfade für Eingabebilder besorgen und Bilder einlesen
    GetInputImagePath(cmd_line, fct_name, 0,ImgPathBuffer);
    Read_Pic(ImgPathBuffer,Pic_In0,BYTE_IMG);


    //Ausgabebilder deklarieren und Speicher allokieren
    Pic_Out0->maxcol=Pic_In0->maxcol;
    Pic_Out0->maxrow=Pic_In0->maxrow;
    Pic_Out0->type=BYTE_IMG;


    Alloc_Pic_Data(Pic_Out0);



    // ########## Ab hier den eigenen Source-Code einfügen
    int gmax = 255;
    int pixel_anz = Pic_In0->maxrow * Pic_In0->maxcol;
    int g_haeuf[255] = {};      // häufigkeit der Wertw
    double nh[255] = {};        //normierte Häufigkeit
    double hg[255] = {};        //normierte kumulative Häufigkeit
    int fg[255] = {};        //Tranformierte Grauwerte (Ganzzahlig)






    //Grauwert Häufigkeit in Array speichern (Grauwert = index+1)
    for (y=0; y<Pic_In0->maxrow; y++)
    {
        for (x=0; x<Pic_In0->maxcol; x++)
        {
           g_haeuf[b_pixel(Pic_In0,x,y)] += 1 ;
        }
    }


    //normierte häufigkeit berechnen und kumulative häufgikeit
    for (y=0; y<gmax; y++){
        nh[y] = (g_haeuf[y]* 1.0) / (pixel_anz * 1.0);

        if(y == 0){
            hg[y] = nh[y];
        }
        if(y > 0 && y < 255){
          hg[y] = hg[y-1] + nh[y];
        }
    }

    //f(g) tranformierter Grauwert
    for (y=0; y<gmax; y++){
        fg[y] = hg[y] * gmax;
    }



    //Schleife Output -> f(g) auf Bild Packen
    for (y=0; y<Pic_In0->maxrow; y++)
    {
        for (x=0; x<Pic_In0->maxcol; x++)
        {

            b_pixel(Pic_Out0,x,y)=fg[b_pixel(Pic_In0,x,y)-1];

        }
    }




    /*
    for (y=0; y<Pic_In0->maxrow; y++)
    {
        for (x=0; x<Pic_In0->maxcol; x++)
        {

            if( (b_pixel(Pic_In0,x,y)) <= byte_schwelle) {
                b_pixel(Pic_Out0,x,y)=128;
            }
            else {
                b_pixel(Pic_Out0,x,y)=0;
            }

        }
    }
    */

    // ########## Bis hierhin den eigenen Source-Code einfügen


    //Dateipfade für Ausgabebilder besorgen und Bilder abspeichern
    GetOutputImagePath(cmd_line, fct_name, 0,ImgPathBuffer);
    Write_Pic(ImgPathBuffer,Pic_Out0);


    //Speicher freigeben
    Free_Pic_Data(Pic_In0);
    Free_Pic_Data(Pic_Out0);

    return TRUE;
}




int main_rgb2hsi (char *fct_name, char *cmd_line)
{

    char ImgPathBuffer[MAX_PATH]="\0";

    PIC sPic_In0,*Pic_In0=&sPic_In0;


    PIC sPic_OutH,*Pic_OutH=&sPic_OutH;
    PIC sPic_OutS,*Pic_OutS=&sPic_OutS;
    PIC sPic_OutI,*Pic_OutI=&sPic_OutI;


    CHAR Buffer[100]="\0";


    sprintf(Buffer,"fct_name: %s",fct_name);
    SendLog(Buffer,TRUE);



    //Dateipfade für Eingabebilder besorgen und Bilder einlesen
    GetInputImagePath(cmd_line, fct_name, 0,ImgPathBuffer);
    Read_Pic(ImgPathBuffer,Pic_In0,RGB_IMG);



    //Ausgabebilder deklarieren und Speicher allokieren
    Pic_OutH->maxcol=Pic_In0->maxcol;
    Pic_OutH->maxrow=Pic_In0->maxrow;
    Pic_OutH->type=FLOAT_IMG;

    Pic_OutS->maxcol=Pic_In0->maxcol;
    Pic_OutS->maxrow=Pic_In0->maxrow;
    Pic_OutS->type=FLOAT_IMG;

    Pic_OutI->maxcol=Pic_In0->maxcol;
    Pic_OutI->maxrow=Pic_In0->maxrow;
    Pic_OutI->type=FLOAT_IMG;

    Alloc_Pic_Data(Pic_OutH);
    Alloc_Pic_Data(Pic_OutS);
    Alloc_Pic_Data(Pic_OutI);


    // ########## Ab hier den eigenen Source-Code einfügen
    copy_all(Pic_In0,Pic_OutH);
    copy_all(Pic_In0,Pic_OutS);
    copy_all(Pic_In0,Pic_OutI);
    // ########## Bis hierhin den eigenen Source-Code einfügen


    //Dateipfade für Ausgabebilder besorgen und Bilder abspeichern
    GetOutputImagePath(cmd_line, fct_name, 0,ImgPathBuffer);
    Write_Pic(ImgPathBuffer,Pic_OutH);

    GetOutputImagePath(cmd_line, fct_name, 1,ImgPathBuffer);
    Write_Pic(ImgPathBuffer,Pic_OutS);

    GetOutputImagePath(cmd_line, fct_name, 2,ImgPathBuffer);
    Write_Pic(ImgPathBuffer,Pic_OutI);


    //Speicher freigeben
    Free_Pic_Data(Pic_In0);
    Free_Pic_Data(Pic_OutH);
    Free_Pic_Data(Pic_OutS);
    Free_Pic_Data(Pic_OutI);

    return TRUE;


}



int main_hsi2rgb (char *fct_name, char *cmd_line)
{
    char ImgPathBuffer[MAX_PATH]="\0";

    PIC sPic_RGB,*Pic_RGB=&sPic_RGB;


    PIC sPic_H,*Pic_H=&sPic_H;
    PIC sPic_S,*Pic_S=&sPic_S;
    PIC sPic_I,*Pic_I=&sPic_I;


    CHAR Buffer[100]="\0";


    sprintf(Buffer,"fct_name : %s",fct_name);
    SendLog(Buffer,TRUE);



    //Dateipfade für Eingabebilder besorgen und Bilder einlesen
    GetInputImagePath(cmd_line, fct_name, 0,ImgPathBuffer);
    Read_Pic(ImgPathBuffer,Pic_H,FLOAT_IMG);

    GetInputImagePath(cmd_line, fct_name, 1,ImgPathBuffer);
    Read_Pic(ImgPathBuffer,Pic_S,FLOAT_IMG);

    GetInputImagePath(cmd_line, fct_name, 2,ImgPathBuffer);
    Read_Pic(ImgPathBuffer,Pic_I,FLOAT_IMG);


    //Ausgabebilder deklarieren und Speicher allokieren
    Pic_RGB->maxcol=Pic_H->maxcol;
    Pic_RGB->maxrow=Pic_H->maxrow;
    Pic_RGB->type=RGB_IMG;


    Alloc_Pic_Data(Pic_RGB);

    // ########## Ab hier den eigenen Source-Code einfügen
    copy_all(Pic_I,Pic_RGB);
    // ########## Bis hierhin den eigenen Source-Code einfügen

    //Dateipfade für Ausgabebilder besorgen und Bilder abspeichern
    GetOutputImagePath(cmd_line, fct_name, 0,ImgPathBuffer);
    Write_Pic(ImgPathBuffer,Pic_RGB);



    //Speicher freigeben
    Free_Pic_Data(Pic_RGB);
    Free_Pic_Data(Pic_H);
    Free_Pic_Data(Pic_S);
    Free_Pic_Data(Pic_I);

    return TRUE;

}

#ifdef ERWEITERN
int main_sleep (char *fct_name, char *cmd_line) {

    SendLog("Sleep:",TRUE);
    Sleep(30000);
}
#endif // ERWEITERN
