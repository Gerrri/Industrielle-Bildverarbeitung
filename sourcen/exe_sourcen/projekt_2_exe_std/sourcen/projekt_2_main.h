
#include ".\std_sourcen\qt_debug_bug.h"

#include <string.h>



int main_max_min (char *fct_name, char *cmd_line)
{
    char ImgPathBuffer[MAX_PATH]="\0";

    PIC sPic_In0,*Pic_In0=&sPic_In0;

    PIC sPic_Out0,*Pic_Out0=&sPic_Out0;

    int x, y, x_size, y_size;
    int start_x,start_y;
    int minGrauwert,maxGrauwert,i,j = 0;



    CHAR Buffer[10000]="\0";
    CHAR Berechnung[100]="\0";

    // Ausgabe des Funktionsnamens
    sprintf(Buffer,"fct_name hi9: %s",fct_name);
    SendLog(Buffer,FALSE);


    // Einlesen des Parameters für die Berechnungsart (min oder max)
    if(FALSE==GetParamStr(cmd_line, fct_name,"Berechnung",Berechnung,100)) {
        SendLog("GetParamStr fehlgeschlagen",FALSE);
        return (FALSE);
    }
    if( (strcmp(Berechnung, "max")!=0) && (strcmp(Berechnung, "min")!=0) ){
        SendLog("Berechnung weder max noch min",FALSE);
        return (FALSE);
    }


    // Einlesen des Parameters x-size
    if(FALSE==GetParamStr(cmd_line, fct_name,"x-size",Buffer,100)) {
        SendLog("GetParamStr fehlgeschlagen",FALSE);
        return (FALSE);
    }
    // Konvertieren des Parameters von ASCII nach ...
    x_size=atoi(Buffer);
    sprintf(Buffer,"x_size=%d\n",x_size);
    // Überprüfen des Parameters
    if (x_size <=0 ) {
        SendLog("Falscher Wert für x_size",FALSE);
        return (FALSE);
    }
    sprintf(Buffer,"x-size: %d",x_size);
    SendLog(Buffer,FALSE);


    // Einlesen des Parameters y-size
    if(FALSE==GetParamStr(cmd_line, fct_name,"y-size",Buffer,100)) {
        SendLog("GetParamStr fehlgeschlagen",FALSE);
        return (FALSE);
    }
    // Konvertieren des Parameters von ASCII nach ...
    y_size=atoi(Buffer);
    sprintf(Buffer,"y_size=%d\n",y_size);
    // Überprüfen des Parameters
    if (y_size <=0 ) {
        SendLog("Falscher Wert für y_size",FALSE);
        return (FALSE);
    }
    sprintf(Buffer,"y-size: %d",y_size);
    SendLog(Buffer,FALSE);


    //Dateipfade für Eingabebilder besorgen und Bilder einlesen
    GetInputImagePath(cmd_line, fct_name, 0,ImgPathBuffer);
    Read_Pic(ImgPathBuffer,Pic_In0,BYTE_IMG);


    //Ausgabebilder deklarieren und Speicher allokieren
    Pic_Out0->maxcol=Pic_In0->maxcol;
    Pic_Out0->maxrow=Pic_In0->maxrow;
    Pic_Out0->type=BYTE_IMG;

    Alloc_Pic_Data(Pic_Out0);



    // Schwellwert (da nicht schwarz/weiß) 1-255
    int schwelle = 100;


    // Source Code für einen Algorithmus bei max / Dilatation
    // ####### START Dilatation ###############################
    if(strcmp(Berechnung,"max")==0){

       SendLog("Berechne max",FALSE);

             // "rand" der Maske in x und y richtung
             int start_y = y_size/2;
             int start_x = x_size/2;


             //innerer Rahmen (abzügliche maskenrand)
             for (y=start_y; y<(Pic_In0->maxrow-start_y); y++){

                   //innerer Rahmen (abzügliche maskenrand)
                   for (x=start_x; x<(Pic_In0->maxcol-start_x); x++){

                            maxGrauwert=0;

                            //Geringsten Grauswert in Maske suchen z.B. in 3x3
                            for(i=(x-start_x); i<(x+start_x);i++){

                                for(j=(y-start_y); j<(y+start_y);j++){

                                    //Geringsten Grauswert in Maske speichern
                                    if((b_pixel(Pic_In0,i,j))> maxGrauwert){
                                        maxGrauwert = ((b_pixel(Pic_In0,i,j)));
                                    }

                                }
                            }
                        // geringsten ermittelten Frauwert setzen
                        b_pixel(Pic_Out0,x,y)=(maxGrauwert);
                    }
            }
    }


    // Source Code für einen Algorithmus bei min / Erosion
    // ####### START Erosion ###############################
        if(strcmp(Berechnung,"min")==0){

           SendLog("Berechne min",FALSE);

                 // "rand" der Maske in x und y richtung
                 int start_y = y_size/2;
                 int start_x = x_size/2;


                 //innerer Rahmen (abzügliche maskenrand)
                 for (y=start_y; y<(Pic_In0->maxrow-start_y); y++){

                       //innerer Rahmen (abzügliche maskenrand)
                       for (x=start_x; x<(Pic_In0->maxcol-start_x); x++){

                            minGrauwert=255;

                                //Geringsten Grauswert in Maske suchen z.B. in 3x3
                                for(i=(x-start_x); i<(x+start_x);i++){

                                    for(j=(y-start_y); j<(y+start_y);j++){

                                        //Geringsten Grauswert in Maske speichern
                                        if((b_pixel(Pic_In0,i,j))<minGrauwert){
                                            minGrauwert = ((b_pixel(Pic_In0,i,j)));
                                        }

                                    }
                                }
                            // geringsten ermittelten Frauwert setzen
                            b_pixel(Pic_Out0,x,y)=(minGrauwert);
                        }
                }
        }


        // Source Code für einen Algorithmus bei min / Erosion
        // ####### START Erosion ###############################
            if(strcmp(Berechnung,"ver")==0){

               SendLog("Vergleich wird gestartet ...",FALSE);

               //innerer Rahmen (abzügliche maskenrand)
               for (y=0; y<(Pic_In0->maxrow); y++){

                     //innerer Rahmen (abzügliche maskenrand)
                     for (x=0; x<(Pic_In0->maxcol); x++){

                         //vorbereiten der Masken
                         //y maske = x,y
                         //x maske = umgedreht
                         start_x = 39/2;
                         start_y = 7/2;

                         //Geringsten Grauswert in Maske suchen z.B. in 3x3
                         for(i=(x-start_x); i<(x+start_x);i++){

                             for(j=(y-start_y); j<(y+start_y);j++){

                                 //Geringsten Grauswert in Maske speichern
                                 if((b_pixel(Pic_In0,i,j))<minGrauwert){
                                     minGrauwert = ((b_pixel(Pic_In0,i,j)));
                                 }

                             }
                         }





                     }
               }


            }

    //Dateipfade für Ausgabebilder besorgen und Bilder abspeichern
    GetOutputImagePath(cmd_line, fct_name, 0,ImgPathBuffer);
    Write_Pic(ImgPathBuffer,Pic_Out0);


    //Speicher freigeben
    Free_Pic_Data(Pic_In0);
    Free_Pic_Data(Pic_Out0);

    return TRUE;
}





int main_vergleich (char *fct_name, char *cmd_line)
{
    char ImgPathBuffer[MAX_PATH]="\0";

    PIC sPic_In0,*Pic_In0=&sPic_In0;
    PIC sPic_In1,*Pic_In1=&sPic_In1;

    PIC sPic_Out0,*Pic_Out0=&sPic_Out0;

    int x,y;
    int fail=1;

    int pixel0,pixel1,pixelSub;

    int schwelle;
    BYTE_IBV byte_schwelle;



    CHAR Buffer[10000]="\0";

    // Ausgabe des Funktionsnamens
    sprintf(Buffer,"fct_name: %s",fct_name);
    SendLog(Buffer,TRUE);


    // Einlesen der Parameter als ASCII (String)
    if(FALSE==GetParamStr(cmd_line, fct_name,"Schwelle",Buffer,100)) {
        SendLog("GetParamStr fehlgeschlagen",TRUE);
        return (FALSE);
    }

    // Konvertieren der Parameter von ASCII nach ...
    schwelle=atoi(Buffer);
    sprintf(Buffer,"Schelle=%d\n",schwelle);


    // Überprüfen der Parameter
    if (schwelle <0 || schwelle >255) {
        SendLog("Falscher Wert für Schwelle",TRUE);
        return (FALSE);
    }
    else{
        byte_schwelle=(BYTE_IBV) schwelle;
    }


    //Dateipfade für Eingabebilder besorgen und Bilder einlesen
    GetInputImagePath(cmd_line, fct_name, 0,ImgPathBuffer);
    Read_Pic(ImgPathBuffer,Pic_In0,BYTE_IMG);


    //Dateipfade für Eingabebilder besorgen und Bilder einlesen
    GetInputImagePath(cmd_line, fct_name, 1,ImgPathBuffer);
    Read_Pic(ImgPathBuffer,Pic_In1,BYTE_IMG);


    //Ausgabebilder deklarieren und Speicher allokieren
    Pic_Out0->maxcol=Pic_In0->maxcol;
    Pic_Out0->maxrow=Pic_In0->maxrow;
    Pic_Out0->type=BYTE_IMG;

    Alloc_Pic_Data(Pic_Out0);

    // Source Code für einen Algorithmus
    for (y=0; y<Pic_In0->maxrow; y++)
    {
        for (x=0; x<Pic_In0->maxcol; x++)
        {
            //pixel bild 1 und 0 holen (x,y)
            pixel0=b_pixel(Pic_In0,x,y);
            pixel1=b_pixel(Pic_In1,x,y);

            //pixel subtrahieren
            pixelSub=fabs(pixel1-pixel0);


            //wenn über schwelle -> schwarz
            if(pixelSub<byte_schwelle){
                pixelSub=0;

                //Fehler setzen, wenn schwarzer pixel geschrieben.
                if(x>17 && y>2 && x<(Pic_In0->maxcol-17) && y<(Pic_In0->maxrow-2) ){
                    fail = 0;
                }
            }

            //wenn über schwelle -> weiß
            else if(pixelSub>= byte_schwelle){
                pixelSub=255;
            }
            b_pixel(Pic_Out0,x,y)=pixelSub;
        }
    }

    // Fehlerausgabe!
    if(fail == 0){
        SendLog("Fehlerhaftes Bild!",TRUE);
    }else{
        SendLog("OK!",TRUE);
    }



    //Dateipfade für Ausgabebilder besorgen und Bilder abspeichern
    GetOutputImagePath(cmd_line, fct_name, 0,ImgPathBuffer);
    Write_Pic(ImgPathBuffer,Pic_Out0);


    //Speicher freigeben
    Free_Pic_Data(Pic_In0);
    Free_Pic_Data(Pic_In1);
    Free_Pic_Data(Pic_Out0);

    return TRUE;
}
