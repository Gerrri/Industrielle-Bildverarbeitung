//  ##############################################################################
//  AB HIER stehen die Musterlösung-Funktionen zur Segmentierung aus dem Projekt 4   
//  ##############################################################################




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



int is_point_of_region_and_not_filled(PIC *Pic_In, PIC *Pic_Out, int x, int y, float threshold)
{
  if(x<0 || y<0 || x>=Pic_In->maxcol || y>=Pic_In->maxrow) return(0);
  if(f_pixel(Pic_In,x,y)>threshold && f_pixel(Pic_Out,x,y) == 0.0) return(1);
  return(0);
}






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


  if(is_point_of_region_and_not_filled(Pic_In,Pic_Out,x,y,threshold)==1) /* Ist der Startpunkt ein Punkt der Region, der noch nicht gefüllt wurde ? */
  {
	  enqueue(x,y);							    /* Wenn ja dann ins FIFO eintragen */
	  f_pixel(Pic_Out,x,y)= (float) region_nr;  /* ... dann füllen */
	  Reg_intern->x[regionen_groesse] = x;      /* Punkte eintragen in die interne Regionenstruktur */
	  Reg_intern->y[regionen_groesse] = y; 
	  regionen_groesse++;
  }

  //enqueue(x,y);                                   /* Startpunkt in Queue legen.                */
 


   while(pull!=push)                               /* Erhält Queue mindestens noch ein Element? */
  {                                               /* Ja.                                       */
	  dequeue(x,y);                                 /* Startpunkt aus Queue holen.                          */
 
	  if(is_point_of_region_and_not_filled(Pic_In,Pic_Out,x+1,y,threshold)==1) /* Ist der rechte Nachbar ein Punkt der Region, der noch nicht gefüllt wurde ? */
	  {
		  enqueue(x+1,y);							  /* Wenn ja dann ins FIFO eintragen */
		  f_pixel(Pic_Out,x+1,y)= (float) region_nr;  /* ... dann füllen */
		  Reg_intern->x[regionen_groesse] = x+1;      /* Punkte eintragen in die interne Regionenstruktur */
	      Reg_intern->y[regionen_groesse] = y; 
	      regionen_groesse++;
	  }
	  if( is_point_of_region_and_not_filled(Pic_In,Pic_Out,x,y+1,threshold)==1) /* Ist der untere Nachbar ein Punkt der Region ? */
	  {
		  enqueue(x,y+1);							 /* Wenn ja dann ins FIFO eintragen */
		  f_pixel(Pic_Out,x,y+1)= (float) region_nr;  /* ... dann füllen */
		  Reg_intern->x[regionen_groesse] = x;      /* Punkte eintragen in die interne Regionenstruktur */
	      Reg_intern->y[regionen_groesse] = y+1; 
	      regionen_groesse++;
	  }
	  if(is_point_of_region_and_not_filled(Pic_In,Pic_Out,x-1,y,threshold)==1) /* Ist der linke Nachbar ein Punkt der Region ? */
	  {
		  enqueue(x-1,y);							 /* Wenn ja dann ins FIFO eintragen */
		  f_pixel(Pic_Out,x-1,y)= (float) region_nr;  /* ... dann füllen */
		  Reg_intern->x[regionen_groesse] = x-1;      /* Punkte eintragen in die interne Regionenstruktur */
	      Reg_intern->y[regionen_groesse] = y; 
	      regionen_groesse++;
	  }
	  if(is_point_of_region_and_not_filled(Pic_In,Pic_Out,x,y-1,threshold)==1) /* Ist der obere Nachbar ein Punkt der Region ? */
	  {
		  enqueue(x,y-1);							 /* Wenn ja dann ins FIFO eintragen */
		  f_pixel(Pic_Out,x,y-1)= (float) region_nr;  /* ... dann füllen */
		  Reg_intern->x[regionen_groesse] = x;      /* Punkte eintragen in die interne Regionenstruktur */
	      Reg_intern->y[regionen_groesse] = y-1; 
	      regionen_groesse++;
	  }	


  } /* end while */ 
 

  Reg_intern->anzahl = regionen_groesse; 

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
		
//  ###############################################################################
//  Bis HIER stehen die Musterlösung-Funktionen zur Segmentierung aus dem Projekt 4   
//  ###############################################################################
