
#include ".\std_sourcen\qt_debug_bug.h"
#include <stdio.h>

// Bei einer Erweiterung bzw. Änderung müssen die folgenden Datei
// an den durch AENDERN bzw. ERWEITERN gekennzeichneten Stellen sinngemäß
// erweitert bzw. angepasst werden. Eine Erweiterung steht dort jeweils schon
// schematisch; ist allerdings auskommentiert:

// 1.) DLLFunctionInfo.h
// 2.) IBVStudioDllEntry.c
// 3.) Änderung der Parameterdatei aus IBV-Studio heraus
// 4.) Function.h
// 5.) Function.c
double pi=3.14159265358979323846;       // pi


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

    //Hilfvaraiblen
    double r_in,g_in,b_in;                  // RGB Werte 0-255
    int y,x;                                // x und y Werte das Pixels
    double r_norm, g_norm, b_norm;          // RGB auf 0 bis 1 genormt
    double l;                       // Luminance                                        #L#
    double lr, lg, lb;                      // Vektor L
    double cr, cg, cb;                      // Vektor C
    double c;                               // Chrominance                                      #C#
    double rpr,rpg,rpb;                     // Vektor RP
    double rp_betrag;                       // RP-Betrag
    double cos_alpha;                       // cos (alpha)= (C * R) / (C-Betrag * R-Betrag)
    double alpha;                           // alpha
    double h;                               // HUE                                              #H#



    //zusätzlich für HCL2HSI
    double l_BG, l_BR, l_GR, l_YM, l_YT, l_MT, l_MAX, l_MIN_positiv =0;   //Alle Lambdas
    double smb, smg, smr =0;                                              //Schnittpunkte
    double db,dg,dr=0;                                                    //Differenzvektor SM und L
    double cMAXer=0;
    double S =0;                                                          //Chroma auf cMAXer normiert
    double I =0;                                                            // das I der HSI Farbraums





    for (y=0; y<Pic_In0->maxrow; y++)
    {
        for (x=0; x<Pic_In0->maxcol; x++)
        {
//START RGB2HCL
            //rgb des aktuellen Pixels auslesen
            r_in = rgb_pixel(Pic_In0,x,y)->r;
            g_in = rgb_pixel(Pic_In0,x,y)->g;
            b_in = rgb_pixel(Pic_In0,x,y)->b;

            //rgb Werte Normieren
            r_norm = r_in*1.0 / 255;
            g_norm = g_in*1.0 / 255;
            b_norm = b_in*1.0 / 255;

            //(1 + 2)Luminance Berechnen 1/sqrt(3)* (r_norm+g_norm+b_norm) + Vektor
            l = 1/sqrt(3)*(r_norm+g_norm+b_norm);

            lr = lg = lb = l / sqrt(3);


            //(3)Berechnung Verktor C
            cr = r_norm - lr;
            cg = g_norm - lg;
            cb = b_norm - lb;

            //(4)Chrominance
            c = sqrt(cr*cr+cg*cg+cb*cb);

            //(5)Vektor RP = Projektion des Vektors (r=1, g=0, b=0) in die Ebene in der auch der Vektor C lieg
            rpr =      0.66666666666666667;
            rpg =     -0.33333333333333333;
            rpb =     -0.33333333333333333;

            //(6)RP Betrag
            rp_betrag = sqrt(rpr*rpr + rpg*rpg + rpb*rpb);

            //(7.1)cos (alpha)= (C * R) / (C-Betrag * R-Betrag)
            if((c*rp_betrag)==0.0000000000){
                cos_alpha = 0;
            }else{
                cos_alpha = ((rpr*cr)+(rpg*cg)+(rpb*cb))/(c*rp_betrag);
                if(cos_alpha>1){cos_alpha=1;}
                if(cos_alpha<-1){cos_alpha=-1;}
            }





            //(7.2)alpha = arcos(cos_alpha)
            alpha = acos(cos_alpha) / pi * 180;

            //(7.3)Hue =
            if(b_in>g_in){
                h = 360 - alpha;
            }else{
                h =alpha;
            }


//END RGB2HCL (h,c,l)

//START HCL2HSI -> input : h, l, cr, cg, cb
            //(1) lr,lg,lb
            lr = lg = lb = l / sqrt(3);

            //(1) EmaxER aus HLCrCgCb berechnen unter Nutzung der folgenden MAKROS
            //START MAKRO_EmaxER_Bestimmen ##############################################################
                        // (1.2) alle Lambdas berechnen l_BG, l_BR, l_GR, l_YM, l_YT, l_MT;
                        if(cr == 0){l_BG = 10000;}      else{l_BG = -l /  (sqrt(3) * cr);}
                        if(cg == 0){l_BR = 10000;}      else{l_BR = -l /  (sqrt(3) * cg);}
                        if(cb == 0){l_GR = 10000;}      else{l_GR = -l /  (sqrt(3) * cb);}

                        if(cr == 0){l_YM = 10000;}      else{l_YM = (1-(l/sqrt(3)))/cr;}
                        if(cg == 0){l_YT = 10000;}      else{l_YT = (1-(l/sqrt(3)))/cg;}
                        if(cb == 0){l_MT = 10000;}      else{l_MT = (1-(l/sqrt(3)))/cb;}

                        // (1.3) minimales positives Lambda l_MIN_positiv Berechnen
                            // l_MAX berechnen
                            l_MAX = l_BG;
                            if(l_MAX < l_BR){l_MAX=l_BR;}
                            if(l_MAX < l_GR){l_MAX=l_GR;}
                            if(l_MAX < l_YM){l_MAX=l_YM;}
                            if(l_MAX < l_YT){l_MAX=l_YT;}
                            if(l_MAX < l_MT){l_MAX=l_MT;}

                            // negative lambda auf l_MAX
                            if(0 > l_BG){l_BG = l_MAX;}
                            if(0 > l_BR){l_BR = l_MAX;}
                            if(0 > l_GR){l_GR = l_MAX;}
                            if(0 > l_YM){l_YM = l_MAX;}
                            if(0 > l_YT){l_YT = l_MAX;}
                            if(0 > l_MT){l_MT = l_MAX;}

                            // minimal positiver Lambda wert
                            l_MIN_positiv = l_BG;
                            if(l_MIN_positiv > l_BR){l_MIN_positiv=l_BR;}
                            if(l_MIN_positiv > l_GR){l_MIN_positiv=l_GR;}
                            if(l_MIN_positiv > l_YM){l_MIN_positiv=l_YM;}
                            if(l_MIN_positiv > l_YT){l_MIN_positiv=l_YT;}
                            if(l_MIN_positiv > l_MT){l_MIN_positiv=l_MT;}

                        // (1.4) Schnittpunkte (SM) berechnen indem Lambda einfach in die Geradengleichung eingesetzt wird
                        // smb, smg, smr
                        smb = lr    +   l_MIN_positiv   *   cr;
                        smg = lg    +   l_MIN_positiv   *   cg;
                        smr = lb    +   l_MIN_positiv   *   cb;

                        // (1.5) Differenzvektor SM und L
                        // db,dg,dr
                        db = smb - lr;
                        dg = smg - lg;
                        dr = smr - lb;

                        // (1.6) Abstand von SM zur Unbuntgerade berechnen
                        cMAXer = sqrt((db*db)+(dg*dg)+(dr*dr));
            //ENDE MAKRO_EmaxER_Bestimmen ##############################################################

            //(2)Das Chroma aus Cr, Cb, Cg berechnen
            c = sqrt((cr*cr)+(cg*cg)+(cb*cb));

            //(3) Das Chroma (Betrag von Vektor C) auf EmaxER normieren
            if(cMAXer==0){S=0;}
            else{
                S = c/cMAXer;
            }

            //(3?) I berechnen
            I = l/sqrt(3);


            //Prüfung ob HSI Valide
            if(S>1 && S<1.1){ S=0.99; }    // Wenn S durch RUndungsfehler nicht ok
            if(I>1 && I<1.1){ I=0.99; }    // Wenn I durch RUndungsfehler nicht ok

            if(S<0) {S=0;}
            if(I<0) {I=0;}

//ENDE HCL2HSI
            // Bild schrieben
            f_pixel(Pic_OutH,x,y) = h;
            f_pixel(Pic_OutS,x,y) = S;
            f_pixel(Pic_OutI,x,y) = I;

            if(x==44 && y==45){
                int haltestelle = 123;
            }

        }
    }




    //copy_all(Pic_In0,Pic_OutH);
    //copy_all(Pic_In0,Pic_OutS);
    //copy_all(Pic_In0,Pic_OutI);
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
    //rgb_pixel(Pic_In0,x,y)->r;
    int x,y;
    double HSI_H, HSI_S, HSI_I;
    double HCL_H, HCL_C, HCL_L;
    double alpha;
    double rpr,rpg,rpb,rp_betrag;
    double Kr, Kg, Kb, K_Betrag;
    double v,u,t,a,b,c;
    int VZ_Wurzel,VZ_Lambda;
    double kg,lambda;
    double Cr,Cg,Cb,C;
    double Lr,Lg,Lb;

    double l_BG, l_BR, l_GR, l_YM, l_YT, l_MT, l_MAX, l_MIN_positiv =0;   //Alle Lambdas
    double db,dg,dr,smb, smg, smr, cMAXer;
    int R,G,B;


    for (y=0; y<Pic_H->maxrow; y++)
    {
        for (x=0; x<Pic_H->maxcol; x++)
        {
 //START HSI2HCL
            //INPUT
            HSI_H = f_pixel(Pic_H,x,y);
            HSI_S = f_pixel(Pic_S,x,y);
            HSI_I = f_pixel(Pic_I,x,y)/255;



            //(1) Arbeits HCL Trippel
            HCL_H = HSI_H;
            HCL_C = 1;
            HCL_L = HSI_I*sqrt(3);


            //(2) MAKRO_Vektor_C_aus_den Werten_HCL_Berechnen

            //(2.1)alpha
            alpha = HSI_H;

            //(2.2)Vektor RP = Projektion des Vektors (r=1, g=0, b=0) in die Ebene in der auch der Vektor C lieg
            rpr =      0.66666666666666667;
            rpg =     -0.33333333333333333;
            rpb =     -0.33333333333333333;

            //(2.3)RP Betrag
            rp_betrag = sqrt(rpr*rpr + rpg*rpg + rpb*rpb);


            //(2.5)
            v = rpg-rpr;
            u = rpb-rpr;
            t = rp_betrag*cos((alpha/180*pi));

            a = (v*v)-(2*(t*t));
            b = (2*v*u)-(2*t*t);
            c = (u*u)-(2*t*t);

            //(2.6)VZ_Wurzel
             if(HCL_H>=0 && HCL_H<=90){                    VZ_Wurzel =  1;
                 }else if(HCL_H>90    && HCL_H<150){       VZ_Wurzel = -1;
                 }else if(HCL_H>=150  && HCL_H<=180){      VZ_Wurzel = -1;
                 }else if(HCL_H>180   && HCL_H<=270){      VZ_Wurzel =  1;
                 }else if(HCL_H>270   && HCL_H<330){       VZ_Wurzel = -1;
                 }else if(HCL_H>=330  && HCL_H<360){       VZ_Wurzel = -1;
                 }else{                                  VZ_Wurzel =  0;
                 }

             //(2.7)VZ_Lambda
             if(HCL_H>=0 && HCL_H<=90){                   VZ_Lambda = -1;
                }else if(HCL_H>90    && HCL_H<150){       VZ_Lambda = -1;
                }else if(HCL_H>=150  && HCL_H<=180){      VZ_Lambda =  1;
                }else if(HCL_H>180   && HCL_H<=270){      VZ_Lambda =  1;
                }else if(HCL_H>270   && HCL_H<330){       VZ_Lambda =  1;
                }else if(HCL_H>=330  && HCL_H<360){       VZ_Lambda = -1;
                }else{                                  VZ_Lambda =  0;
                }
            //(2.8)kg =WENN(B151=0;-(B153/B152);(B155*WURZEL((B152*B152)-(4*B151*B153))-B152)/(2*B151)   )

            if(a==0){kg = c/b;}
            else{
                kg = ((VZ_Wurzel*1.0)*sqrt((b*b)-(4*a*c))-b) / (2*a);

            }

            //(2.4) Vektor K der parallel zu C ist aber gut gewählt zum Rechnen

            if(HCL_L!=330 && HCL_L!=150){Kg = kg;}              else{Kg = 1;}
            if(HCL_L!=330 && HCL_L!=150){Kb = 1;}               else{Kb = 0;}
            if(HCL_L!=330 && HCL_L!=150){Kr = -1 -Kg;}          else{Kr = -1;}

            K_Betrag = sqrt((Kr*Kr)+(Kg*Kg)+(Kb*Kb));


            //(2.9)lambda
            lambda = VZ_Lambda * HCL_C  / K_Betrag;

            //OUTPUT
            Cr = lambda*Kr;
            Cg = lambda*Kg;
            Cb = lambda*Kb;

          //(3) Berechne auf Basis des Arbeits-HCL-Trippels und des Arbeits-Vektors C das EmaxER
            //(3.1) L = HCL_L
            Lr = HCL_L/sqrt(3);
            Lg = HCL_L/sqrt(3);
            Lb = HCL_L/sqrt(3);

            //(3.2)
            if(Cr==0){l_BG=10000;} else{l_BG = -HCL_L/(sqrt(3)*Cr);}
            if(Cg==0){l_BR=10000;} else{l_BR = -HCL_L/(sqrt(3)*Cg);}
            if(Cb==0){l_GR=10000;} else{l_GR = -HCL_L/(sqrt(3)*Cb);}

            if(Cr==0){l_YM=10000;} else{l_YM=(1-(HCL_L/sqrt(3)))/Cr;}
            if(Cg==0){l_YT=10000;} else{l_YT=(1-(HCL_L/sqrt(3)))/Cg;}
            if(Cb==0){l_MT=10000;} else{l_MT=(1-(HCL_L/sqrt(3)))/Cb;}

            //(3.3)
                // l_MAX berechnen
                l_MAX = l_BG;
                if(l_MAX < l_BR){l_MAX=l_BR;}
                if(l_MAX < l_GR){l_MAX=l_GR;}
                if(l_MAX < l_YM){l_MAX=l_YM;}
                if(l_MAX < l_YT){l_MAX=l_YT;}
                if(l_MAX < l_MT){l_MAX=l_MT;}

                // negative lambda auf l_MAX
                if(0 > l_BG){l_BG = l_MAX;}
                if(0 > l_BR){l_BR = l_MAX;}
                if(0 > l_GR){l_GR = l_MAX;}
                if(0 > l_YM){l_YM = l_MAX;}
                if(0 > l_YT){l_YT = l_MAX;}
                if(0 > l_MT){l_MT = l_MAX;}

                // minimal positiver Lambda wert
                l_MIN_positiv = l_BG;
                if(l_MIN_positiv > l_BR){l_MIN_positiv=l_BR;}
                if(l_MIN_positiv > l_GR){l_MIN_positiv=l_GR;}
                if(l_MIN_positiv > l_YM){l_MIN_positiv=l_YM;}
                if(l_MIN_positiv > l_YT){l_MIN_positiv=l_YT;}
                if(l_MIN_positiv > l_MT){l_MIN_positiv=l_MT;}


            // (3.4) Schnittpunkte (SM) berechnen indem Lambda einfach in die Geradengleichung eingesetzt wird
            // smb, smg, smr
            smb = Lr    +   l_MIN_positiv   *   Cr;
            smg = Lg    +   l_MIN_positiv   *   Cg;
            smr = Lb    +   l_MIN_positiv   *   Cb;

            // (3.5) Differenzvektor SM und L
            // duble db,dg,dr,smb, smg, smr
            db = smb - Lr;
            dg = smg - Lg;
            dr = smr - Lb;

            // (3.6) Abstand von SM zur Unbuntgerade berechnen
            cMAXer = sqrt((db*db)+(dg*dg)+(dr*dr));

            C = cMAXer*HSI_S;

            // (4) Berechne auf Basis der "richtigen" C den "richtigen" Vektor C
            if(C==0){Cr=0;}else{Cr=Cr*C/1;}
            if(C==0){Cg=0;}else{Cg=Cg*C/1;}
            if(C==0){Cb=0;}else{Cb=Cb*C/1;}

            //OUTPUT H,L,Cr,Cg,Cb

 //ENDE HSI2HCL
 //START HCL2RGB
            //(3.1) L = HCL_L
            Lr = HCL_L/sqrt(3);
            Lg = HCL_L/sqrt(3);
            Lb = HCL_L/sqrt(3);

            //direkt von Normiert zu absolut!
            R = (Cr+Lr)*255;
            G = (Cg+Lg)*255;
            B = (Cb+Lb)*255;

            rgb_pixel(Pic_RGB,x,y)->r = R;
            rgb_pixel(Pic_RGB,x,y)->g = G;
            rgb_pixel(Pic_RGB,x,y)->b = B;



            int aasdasd = 5;


 //START HCL2RGB

        }
    }






    //copy_all(Pic_I,Pic_RGB);
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
