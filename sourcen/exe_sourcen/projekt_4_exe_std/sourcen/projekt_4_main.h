
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

/* Definition der Struktur REGION. Diese Struktur dient zur Aufnahme (Speicherung) 			*/
/* aller Punkte einer Region. Hauptbestandteil sind zwei Felder (Zeiger), die die x- und 	*/
/* die y-Koordinaten der Regionenpunkte aufnehmen. 											*/
typedef struct region_struct
{
  int max;					/* maximal erlaubte Anzahl der Punkte in der Region				*/
                            /* Alloc-Region (siehe unten) allokiert Speicher				*/
                            /* für max Punkte.												*/
  unsigned short int *x;	/* Zeiger auf Feld mit x-Koordinaten der Regionenpunkte			*/
  unsigned short int *y;	/* Zeiger auf Feld mit y-Koordinaten der Regionenpunkte			*/
  int anzahl;				/* gefundene/tatsächliche Anzahl der Punkte in der Region 		*/
  float nummer; 			/* Bei Bedarf kann hier die Nummer der Region eingetragen 		*/
                            /* werden. 														*/
} REGION;


/* Allokiert globalen Speicher für die Regionendaten.              */
/* Die Größe des allokierten Speichers wird entsprechend des       */
/* in der REGION-Struktur angegeben Wertes (max) berechnet         */
/* Der Zeiger auf die Koordinatendaten in der REGION-Struktur wird */
/* auf den jeweils allokierten Speicher "verbogen".                */
/* Rückgabewert: =0    wenn Allokierung erfolgreich                */
/*               <> 0  wenn Allokierung nicht erfolgreich          */
int Alloc_Region_Data (REGION *Reg)
{

  Reg->x =  malloc((unsigned short int) (sizeof (unsigned short int)) * (Reg->max));
  if (Reg->x == NULL)
  {
        return_error_msg("Alloc_Region(): Speicher fuer Region konnte nicht angelegt werden\n",1)
  }

  Reg->y =  malloc((unsigned short int) (sizeof (unsigned short int)) * (Reg->max));
  if (Reg->y == NULL)
  {
        return_error_msg("Alloc_Region(): Speicher fuer Region konnte nicht angelegt werden\n",1)
  }
  return (0);
}


/* Freigabe des für die Regionendaten allokierten Speichers.       */
void Free_Region_Data (REGION *Reg)
{
    free (Reg->x);
    free (Reg->y);
}






/* Anweisungssequenz (Makro), mit dem die Koordinaten eines Pixels		*/
/* d.h. x und y in das FIFO geschrieben werden können.					*/
/* Das FIFO wird über die zwei "Zaehler" push und pull verwaltet.		*/
/* Diese Zaehler müssen vor der ersten Nutzung des Makros als			*/
/* Integervariablen deklariert und auf den Wert 0 initialisiert			*/
/* werden.																*/
/* Desweiteren muessen die Felder x_fifo und y_fifo deklariert			*/
/* und allokiert worden sein.											*/

#define enqueue(x,y) \
        {\
          x_fifo[push]=(x);\
          y_fifo[push]=(y);\
          push++; if(push>=fifo_size) push=0;\
          if(push==pull) abort();\
        }


/* Anweisungssequenz (Makro), mit dem die Koordinaten eines Pixels		*/
/* d.h. x und y aus dem FIFO heraus gelesen werden können.				*/
/* Das FIFO wird über die zwei "Zaehler" push und pull verwaltet.		*/
/* Diese Zaehler müssen vor der ersten Nutzung des Makros als			*/
/* Integervariablen deklariert und auf den Wert 0 initialisiert  		*/
/* werden.																*/
/* Desweiteren muessen die Felder x_fifo und y_fifo deklariert	  		*/
/* und allokiert worden sein.											*/
#define dequeue(x,y) \
        {\
          (x)=x_fifo[pull];\
          (y)=y_fifo[pull];\
          pull++; if(pull>=fifo_size) pull=0;\
        }








/* Überprüft ob ein übergebener Punkt mit den Koordinaten x,y
 * innerhalb des Eingabebildes (Pic_In) liegt und ob der Punkt
 * ein Punkt der Region ist und ob dieser noch nicht im Ausgabebild (Pic_Out)
 * markiert wurde.
 * Eingabeparameter:
 *		Pic_In 	Eingabebild vom Typ FLOAT
 *		Pic_Out Merkerbild vom Typ FLOAT
 *		x		X-Koordinate des Punktes
 *		y		Y-Koordinate des Punktes
 * Rückgabewert: 	= 1   wenn der Punkt ein Puntk der Region ist, d.h. wenn dieser
 *							a.) innerhalb des Eingabebildes liegt und
 *							b.) im Eingabebild einen Wert größer als threshold hat und
 *			 				c.) im Merkerbild noch nicht markiert wurde.
 *		 			= 0   sonst
*/

int is_point_of_region_and_not_filled(PIC *Pic_In, PIC *Pic_Out, int x, int y, float threshold)
{

  //########################### Ab hier vervollständigen  ##################################

    if(x<0) {
        return(0);
    } else {
        return(1);
    }
  //########################### Bis hier vervollständigen  ##################################
}





/*  Ermittelt alle Punkte einer Region in 4er-Nachbarschaft und
 *  allokiert den Speicher für eine Regionenstruktur
 *  Eingabeparameter:
 *		Pic_In		Eingabebild vom Typ FLOAT
 *      x			X-Koordinate eines ersten gefundenen Punktes der Region
 *      y			Y-Koordinate eines ersten gefundenen Punktes der Region
 *      threshold	Schwellwert für die Regionenbildung, d.h. nur Pixel mit
 *					einem Wert > threshold gehören zur Region
 *		region_nr	Wert mit dem die Region bezeichnet wird
 *
 *	Ausgabeparameter:
 *		Pic_Out		Ausgabebild von Typ FLOAT, das in den Bildpunkte
 *					den Wert "region_nr" enthält, die zu der Region gehören.
 *					Typischerweise wird fill_region für alle Regionen
 *                  mit dem selben Ausgabebild aber anderer "region_nr" aufgerufen,
 *                  so dass nach dem Finden aller Regionen, diese mit entsprechenden
 *	                verschiedenen Werten im Ausgabebild gekannzeichnet sind.
 *					ACHTUNG: Das Ausgabebild muss vor dem Suchen nach allen Regionen
 *							 in allen Pixeln auf den Wert 0.0 gesetzt werden.
 * Ein-/Ausgabe
 *      reg         Zeiger auf Regionenstruktur. Fuer die Felder der x und y-Koordinaten
 *                  wird globaler Speicher allokiert und die Felder werden mit den
 *                  Koordinaten der Regionenpunkte gefuellt.
 *
 * Rückgabewert: =0    wenn Region gefunden und alles o.k
 *              <> 0   wenn Fehler (z.B. beim Allokieren) aufgetreten ist
 *
*/

int fill_region(PIC *Pic_In, PIC *Pic_Out, int x, int y, float threshold, unsigned long int region_nr,
                REGION *reg)
{
  int *x_fifo,*y_fifo;
  int pull=0,push=0;
  long int fifo_size;
  long int regionen_groesse,i;
  REGION intern;
  REGION *Reg_intern=&intern;
  char Buffer[10000]="\0";

  regionen_groesse = 0;

  fifo_size = Pic_In->maxcol * Pic_In->maxrow;

  /* Speicher für das FIFO entsprechend der Bildgröße allokieren */
  x_fifo =  malloc((long) (sizeof (FLOAT_IBV)) * fifo_size);
  if (x_fifo == NULL)
  {
        return_error_msg("fill_region(): Speicher fuer FIFO konnte nicht angelegt werden\n",1)
  }

  y_fifo =  malloc((long) (sizeof (FLOAT_IBV)) * fifo_size);
  if (y_fifo == NULL)
  {
        return_error_msg("fill_region(): Speicher fuer FIFO konnte nicht angelegt werden\n",1)
  }

  /* Speicher für die interne Regionenstruktur entsprechend der Bildgröße allokieren */
  /* Ein Region kann niemals mehr Pixel enthalten als das Bild groß ist. */
  Reg_intern->max = Pic_In->maxcol * Pic_In->maxrow;
  if(Alloc_Region_Data (Reg_intern)!=0)
      return_error_msg("fill_region(): Speicher fuer interne Region konnte nicht angelegt werden\n",1);


//########################### Ab hier vervollstaendigen /aendern ##################################
  if(is_point_of_region_and_not_filled(Pic_In,Pic_Out,x,y,threshold)==1) /* Ist der Startpunkt ein Punkt der Region, der noch nicht gefüllt wurde ? */
  {
      enqueue(x,y);							    /* Wenn ja dann ins FIFO eintragen */
      f_pixel(Pic_Out,x,y)= (float) region_nr;  /* ... dann füllen */
      Reg_intern->x[regionen_groesse] = x;      /* Punkte eintragen in die interne Regionenstruktur */
      Reg_intern->y[regionen_groesse] = y;
      regionen_groesse++;
  }



  while(pull!=push)                               /* Erhält Queue mindestens noch ein Element? */
  {                                               /* Ja.                                       */
      dequeue(x,y);                                 /* Startpunkt aus Queue holen.                          */



  } /* end while */

 //########################### Bis hier vervollstaendigen / aendern  ##################################

  Reg_intern->anzahl = regionen_groesse;

  /* Kontrollausgaben der Regionengröße auf dem Monitor */
  sprintf(Buffer,"Die Region %d hat %d Pixel",  (int) region_nr, (int) regionen_groesse);
  SendLog(Buffer,TRUE);

  /* Weiter oben wurde für die interne Regionenstruktur der maximal sinnvolle Speicher allokiert. */
  /* Dies war/ist relativ viel. Wie wissen nun wie groß die vorliegende Region wirklich ist und */
  /* können somit eine Regionenstruktur dieser Größe allokieren und die gefundenen Pixel der Region */
  /* hier hinein kopieren. Danach kann dann der Speicher für die große (interne) Regionenstruktur */
  /* fei gegeben werden. */
  /* Anlegen des Speichers für die zurueckzugebende Regionenstruktur */
  reg->max = regionen_groesse;
  if(Alloc_Region_Data (reg)!=0)
      return_error_msg("fill_region(): Speicher fuer Rueckgaberegion konnte nicht angelegt werden\n",1);

  /* Kopieren der Regionenpunkte von der internen (maximal grossen) Regionenstruktur */
  /* die die zurueckzugebende (passend grosse) Regionenstruktur */
  for (i=0; i<regionen_groesse; i++)
  {
      reg->x[i] = Reg_intern->x[i];
      reg->y[i] = Reg_intern->y[i];
  }
  reg->anzahl = regionen_groesse;


  /* Allokierten Speicher wieder freigeben */
  free (x_fifo);
  free (y_fifo);
  Free_Region_Data (Reg_intern);

  return (0);
} /* end fill_region */






int main_projekt_4 (char *fct_name, char *cmd_line)
{
    char ImgPathBuffer[MAX_PATH]="\0";

    PIC sPic_In0,*Pic_In0=&sPic_In0;
    PIC sPic_In1,*Pic_In1=&sPic_In1;

    PIC sPic_Out0,*Pic_Out0=&sPic_Out0;
    PIC sPic_Kontrolle,*Pic_Kontrolle=&sPic_Kontrolle;

    int ret;
    float schwelle;

    char Buffer[10000]="\0";



    REGION  test;				/* Regionenstruktur zum Test der Funktion */
    REGION  *Reg_test=&test;


    int     j;


    int     x;
    int     y;

    unsigned long int   region_nr;


    // Ausgabe des Funktionsnamens
    sprintf(Buffer,"fct_name 471001: %s",fct_name);
    SendLog(Buffer,FALSE);


    // Einlesen der Parameter als ASCII (String)
    if(FALSE==GetParamStr(cmd_line, fct_name,"Bin-Schwelle",Buffer,100)) {
        SendLog("GetParamStr fehlgeschlagen",FALSE);
        return (FALSE);
    }

    // Konvertieren der Parameter von ASCII nach ...
    schwelle=(float) atof(Buffer);
    sprintf(Buffer,"Binarisierungs-Schelle=%f",schwelle);
    SendLog(Buffer,FALSE);


    // Überprüfen der Parameter
    if (schwelle <0.0 || schwelle >255.0) {
        SendLog("Falscher Wert für Bin-Schwelle",FALSE);
        return (FALSE);
    }


    //Dateipfade für Eingabebilder besorgen und Bilder einlesen
    GetInputImagePath(cmd_line, fct_name, 0,ImgPathBuffer);
    Read_Pic(ImgPathBuffer,Pic_In0,FLOAT_IMG);

    GetInputImagePath(cmd_line, fct_name, 1,ImgPathBuffer);
    Read_Pic(ImgPathBuffer,Pic_In1,FLOAT_IMG);


    //Ausgabebilder deklarieren und Speicher allokieren
    Pic_Out0->maxcol=Pic_In0->maxcol;
    Pic_Out0->maxrow=Pic_In0->maxrow;
    Pic_Out0->type=FLOAT_IMG;

    Alloc_Pic_Data(Pic_Out0);


    Pic_Kontrolle->maxcol=Pic_In0->maxcol;
    Pic_Kontrolle->maxrow=Pic_In0->maxrow;
    Pic_Kontrolle->type=RGB_IMG;

    Alloc_Pic_Data(Pic_Kontrolle);




      /* Ausgabebilder initialisieren */
      for(y=0; y<Pic_In0->maxrow; y++)
        for(x=0; x<Pic_In0->maxcol; x++)
        {
          f_pixel(Pic_Out0,x,y)=0.0;

          rgb_pixel(Pic_Kontrolle,x,y)->r=0;
          rgb_pixel(Pic_Kontrolle,x,y)->g=0;
          rgb_pixel(Pic_Kontrolle,x,y)->b=0;
        }



      /*
       *  Durchscannen des Eingabebildes, Suche nach einem Pixel mit einem
       *  Wert größer als den Schwellwert, welches noch keiner Region angehört.
       */


      region_nr=1;
      for(y=0; y<Pic_In0->maxrow; y++)
          for(x=0; x<Pic_In0->maxcol; x++) {

              if( x==0 && y==0 /* Hier vervollständigen bzw. anpassen */ )
              {

                ret = fill_region(Pic_In0,Pic_Out0,x,y,schwelle,region_nr, Reg_test);
                if (ret == 0)
                {
                    region_nr+=1;

                    /* Die Pixel der gefundenen Region im Bild zur Kontrolle mit 255 einfaerben */
                    for (j=0; j<Reg_test->anzahl; j++)
                    {
                        rgb_pixel(Pic_Kontrolle,(Reg_test->x[j]),(Reg_test->y[j]))->r = 255;
                        rgb_pixel(Pic_Kontrolle,(Reg_test->x[j]),(Reg_test->y[j]))->g = 0;
                        rgb_pixel(Pic_Kontrolle,(Reg_test->x[j]),(Reg_test->y[j]))->b = 0;

                    }

                    /* Den mittleren Grauwert der Region in Pic_In1 berechnen */
                    //########################### Ab hier vervollständigen  ##################################



                    //########################### Bis hier vervollständigen  ##################################

                    /* Allokierten Speicher für die Felder in der Regionenstruktur wieder freigeben */
                    Free_Region_Data (Reg_test);

                }
                else
                {
                    return_error_msg("Fehlermeldung von fill_region zurueckerhalten\n", 0);
                }
              }
          }

    sprintf(Buffer,"Es wurden: %d Regionen gefunden", (int)(region_nr-1));
    SendLog(Buffer,TRUE);


    //Dateipfade für Ausgabebilder besorgen und Bilder abspeichern
    GetOutputImagePath(cmd_line, fct_name, 0,ImgPathBuffer);
    Write_Pic(ImgPathBuffer,Pic_Out0);


    GetOutputImagePath(cmd_line, fct_name, 1,ImgPathBuffer);
    Write_Pic(ImgPathBuffer,Pic_Kontrolle);


    //Speicher freigeben
    Free_Pic_Data(Pic_In0);
    Free_Pic_Data(Pic_In1);
    Free_Pic_Data(Pic_Out0);
    Free_Pic_Data(Pic_Kontrolle);

    return TRUE;
}



