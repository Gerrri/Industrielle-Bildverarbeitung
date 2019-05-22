
#include ".\std_sourcen\qt_debug_bug.h"

// Im zur Verfügung gestellten Software-Rahmen existieren diese Dateien schon,
// sind aber noch leer. Sie müssen diese durch die (mittels snns2c.exe) selbst
// erzeugten Dateien ziff_erkennung.h und ziff_erkennung.c ersetzen. Die Datei
// ziff_erkennung.c muss vorher jedoch noch in ziff_erkennung.co unbenannt werden.

#include "ziff_erkennung.h"



#include "reg.h"




// Diese Funktion sollten Sie nutzen. Sie kopiert den durch y_oben, y_unten,
// x_rechts und x_links definierten Bereich von Pic_In0 in das Bild Pic_Out0
// und skaliert dabei so dass Pic_Out0 ganz mit diesem Ausschnitt gefüllt wird.
// Ist Pic_Out ein Bild, das die Größe des Bildmusters hat (z.B. 35x35) hat
// so erzeugt diese Funktion direkt das Bildmuster.
void bild_ausschneiden_und_normieren(int y_oben,int y_unten,int x_links,int x_rechts,PIC *Pic_In0, PIC *Pic_Out0)
{

    float koef_x,koef_y, hoehe, breite;

    int x,y;

    hoehe= (float) Pic_Out0->maxrow;
    breite= (float) Pic_Out0->maxcol;

    // Ausgangsbild normieren

    koef_x=(x_rechts-x_links+1)/(breite);
    koef_y=(y_unten-y_oben+1)/(hoehe);

    for (y=0; y<Pic_Out0->maxrow; y++)
    {
        for (x=0; x<Pic_Out0->maxcol; x++)
            {
                f_pixel(Pic_Out0,x,y)=f_pixel(Pic_In0,(int)(((float)x)*koef_x)+x_links,(int)(((float)y)*koef_y)+y_oben);


            }
    }

}



//########### Diese Funktion müssen Sie mit Leben füllen #############################
int umschreibendes_rechteck_bestimmen(int *y_oben,int *y_unten,int *x_links,int *x_rechts, REGION  *Reg)
{

    return 0; // Alles ist ohne Fehler "gelaufen".
}

//#################################################################################





#define HOEHE_PATTERN 35			// Höhe des Bildmusters
#define BREITE_PATTERN 35			// Breite des Bildmusters
#define KLASSIFIKATIONSSCHWELLE 0.5


#define MAX_ANZZIFFERN 1000


// Diese Struktur dient zur Aufnahme der Werte von Klassifizierten Segmenten
// In wert[0] steht Wert der erkannten Ziffer zum ersten gefunden Segment
// In anzahl steht die maximale Anzahl von Werten, die in wert[] gespeichert
// werden können.
typedef struct Ziffer_Struct
{
  int	wert[MAX_ANZZIFFERN];
  int	anzahl;
} ZIFFER;




int main_projekt_6 (char *fct_name, char *cmd_line)
{
    char ImgPathBuffer[MAX_PATH]="\0";

    PIC sPic_In0,*Pic_In0=&sPic_In0;

    PIC sPic_Out0,*Pic_Out0=&sPic_Out0;
    PIC sPic_Kontrolle,*Pic_Kontrolle=&sPic_Kontrolle; // kann für eigene Kontrollausgaben genutzt werden
    PIC sPic_Pattern,*Pic_Pattern=&sPic_Pattern; // enthält den Bildausschnitt

    int ret;
    float schwelle=128; // Da die Binarisierung durch an vorangestelltes M
                        // IBV-Modul gemacht wird, kann hier die Schwelle fest auf
                        // 128 gesetzt werden.

    char Buffer[10000]="\0";



    REGION  test;				/* Regionenstruktur zum Test der Funktion */
    REGION  *Reg_test=&test;


    int     x, x_links, x_rechts, xp;
    int     y, y_oben, y_unten, yp;
    int		z, j;

    unsigned long int   region_nr;


    float *netInput, *netOutput; /* Input und Output arrays des Netzwerks */
    float max_out;
    int	  max_out_pos;

    ZIFFER zahlenfeld;
    int zahlenwert=0;


    // Speicher für die Input und Output arrays des Netzwerks anlegen
    netInput = malloc(ziff_erkennungREC.NoOfInput * sizeof(float));
    netOutput = malloc(ziff_erkennungREC.NoOfOutput * sizeof(float));




    // Ausgabe des Funktionsnamens
    sprintf(Buffer,"fct_namellle: %s",fct_name);
    SendLog(Buffer,FALSE);

    //Dateipfade für Eingabebilder besorgen und Bilder einlesen
    GetInputImagePath(cmd_line, fct_name, 0,ImgPathBuffer);
    Read_Pic(ImgPathBuffer,Pic_In0,FLOAT_IMG);


    //Ausgabebilder deklarieren und Speicher allokieren
    Pic_Out0->maxcol=Pic_In0->maxcol;
    Pic_Out0->maxrow=Pic_In0->maxrow;
    Pic_Out0->type=FLOAT_IMG;

    Alloc_Pic_Data(Pic_Out0);


    Pic_Kontrolle->maxcol=Pic_In0->maxcol;
    Pic_Kontrolle->maxrow=Pic_In0->maxrow;
    Pic_Kontrolle->type=FLOAT_IMG;

    Alloc_Pic_Data(Pic_Kontrolle);


    // Bild für die Aufnahme des Bildmusters anlegen
    Pic_Pattern->maxcol=BREITE_PATTERN;
    Pic_Pattern->maxrow=HOEHE_PATTERN;
    Pic_Pattern->type=FLOAT_IMG;

    Alloc_Pic_Data(Pic_Pattern);



      /* Ausgabebilder initialisieren */
      for(y=0; y<Pic_In0->maxrow; y++)
        for(x=0; x<Pic_In0->maxcol; x++)
        {
          f_pixel(Pic_Out0,x,y)=0.0;

        }



      /*
       *  Durchscannen des Eingabebildes, Suche nach einem Pixel mit einem
       *  Wert größer als den Schwellwert, welches noch keiner Region angehört.
       */
      zahlenfeld.anzahl=0;

      region_nr=1;

      // Bem. A: Statt for(y=0; y<Pic_In0->maxrow; y++) nehmen wir
      y=(Pic_In0->maxrow)/2;
      // D.h. wir suchen Startwerte für das Füllen nur in der mittleren Zeile des Bildes
      // Dies ist erlaub, da in den Testbildern die Ziffern horizontal fast das Bild füllen.
      // Wir erhalten somit den großen Vorteil, dass die Ziffern von links nach rechts der
      // Reihe nach erkannt werden und nicht extra (abhängig von den gefundenen Postionen
      // der Ziffern) umsortiert werden müssen und auf den Zahlenwert zu kommen.
      for(x=0; x<Pic_In0->maxcol; x++)
          if( (f_pixel(Pic_In0,x,y)>schwelle) && (0.0 == f_pixel(Pic_Out0,x,y)) )
          {

            ret = fill_region(Pic_In0,Pic_Out0,x,y,schwelle,region_nr, Reg_test);
            if (ret == 0)
            {

                // Umschreibendes Rechteck bestimmen
                umschreibendes_rechteck_bestimmen(&y_oben, &y_unten, &x_links, &x_rechts, Reg_test);
                sprintf(Buffer,"y_oben= %d y_unten= %d x_links= %d x_rechts= %d",  y_oben, y_unten, x_links, x_rechts);
                SendLog(Buffer,TRUE);


                // Umschreibendes Rechteck ausschneiden und normieren
                // ...


                // Aus dem Bildmuster den Eingabevektor des NN berechnen.
                // Die obere linke (untere rechte) Ecke des Bildmusters ist die
                // erste (letzte) Komponente des Eingabevektors
                // ...

                // Eingabevektor durch Aufruf von ziff_erkennung() klassifizieren
                // ...




                // Das Klasifikationsergebnis (den Ausgabevektor) ausgeben
                for (z=0; z<ziff_erkennungREC.NoOfOutput; z++) {
                    sprintf(Buffer,"netOutput[ %d ] = %f",z, netOutput[z]);
                    SendLog(Buffer,FALSE);
                }




                /* Allokierten Speicher für die Felder in der Regionenstruktur wieder freigeben */
                Free_Region_Data (Reg_test);

                // Regionennummer erhöhen
                region_nr+=1;

            }
            else
            {
                return_error_msg("Fehlermeldung von fill_region zurueckerhalten\n", 0);
            }
          }

    sprintf(Buffer,"Es wurden: %d Regionen gefunden", (int) (region_nr-1));
    SendLog(Buffer,TRUE);

    // Die ermittelten und nunmehr in zahlenfeld stehenden Inhalte ausgeben
    for (j=0; j<zahlenfeld.anzahl; j++) {
        sprintf(Buffer,"%d:  wert=%d", j, zahlenfeld.wert[j]);
        SendLog(Buffer,FALSE);
    }

    // Zahlenwert der gesame Zahl bestimmen.
    // Wegen Bem. A (s.o.) steht die höchstwertigste (linkeste) Ziffer bei Index 0 ,
    // d.h. an der Stelle zahlenfeld.wert[0]
    // ...

    sprintf(Buffer,"Die dargestellte Zahl hat den Wert=%d", zahlenwert);
    SendLog(Buffer,FALSE);




    //Dateipfade für Ausgabebilder besorgen und Bilder abspeichern
    GetOutputImagePath(cmd_line, fct_name, 0,ImgPathBuffer);
    Write_Pic(ImgPathBuffer,Pic_Out0);


    GetOutputImagePath(cmd_line, fct_name, 1,ImgPathBuffer);
    Write_Pic(ImgPathBuffer,Pic_Kontrolle);


    //Speicher freigeben
    free (netInput);
    free (netOutput);


    Free_Pic_Data(Pic_In0);
    Free_Pic_Data(Pic_Out0);
    Free_Pic_Data(Pic_Kontrolle);
    Free_Pic_Data(Pic_Pattern);

    return TRUE;
}



