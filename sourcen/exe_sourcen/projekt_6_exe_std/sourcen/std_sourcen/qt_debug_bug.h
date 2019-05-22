#ifndef QT_DEBUG_BUG

#define QT_DEBUG_BUG

int  L_GetParamStr(char *ParamSourcePointer,char *FunctionName, char *ParamName, char *Destination, int MaxCharsToCopy)
{
    // Diese Funktion L_XYZ wurde nur erstellt weil der Gnu-Debugger mit F10
    // nicht ueber die in einer DLL implementierten Funktio XYZ
    // hinweg springt.
    return GetParamStr(ParamSourcePointer, FunctionName, ParamName, Destination, MaxCharsToCopy);
}
#define GetParamStr L_GetParamStr


int L_GetOutputImagePath(char *ParamSourcePointer, char *FunctionName, int ImgNr, char *Destination)
{
    // Diese Funktion L_XYZ wurde nur erstellt weil der Gnu-Debugger mit F10
    // nicht ueber die in einer DLL implementierten Funktio XYZ
    // hinweg springt.
    return GetOutputImagePath(ParamSourcePointer, FunctionName, ImgNr, Destination);
}
#define GetOutputImagePath L_GetOutputImagePath


int L_GetInputImagePath(char *ParamSourcePointer, char *FunctionName , int ImgNr, char *Destination)
{
    // Diese Funktion L_XYZ wurde nur erstellt weil der Gnu-Debugger mit F10
    // nicht ueber die in einer DLL implementierten Funktion XYZ
    // hinweg springt.
    return GetInputImagePath(ParamSourcePointer, FunctionName, ImgNr, Destination);
}
#define GetInputImagePath  L_GetInputImagePath


int L_Alloc_Pic_Data (PIC *Pic)
{
    // Diese Funktion L_XYZ wurde nur erstellt weil der Gnu-Debugger mit F10
    // nicht ueber die in einer DLL implementierten Funktion XYZ
    // hinweg springt.
    return Alloc_Pic_Data (Pic);
}
#undef Alloc_Pic_Data
#define  Alloc_Pic_Data L_Alloc_Pic_Data



void L_Free_Pic_Data (PIC *Pic)
{
    // Diese Funktion L_XYZ wurde nur erstellt weil der Gnu-Debugger mit F10
    // nicht ueber die in einer DLL implementierten Funktion XYZ
    // hinweg springt.
    Free_Pic_Data (Pic);
}
#undef Free_Pic_Data
#define Free_Pic_Data L_Free_Pic_Data



int L_Read_Pic ( char *file_in_name, PIC *Pic_In, int output_type)
{
    // Diese Funktion L_XYZ wurde nur erstellt weil der Gnu-Debugger mit F10
    // nicht ueber die in einer DLL implementierten Funktion XYZ
    // hinweg springt.
    return Read_Pic (file_in_name, Pic_In, output_type);
}
#define Read_Pic L_Read_Pic



int L_Write_Pic (char *file_out_name, PIC *Pic_Out)
{
    // Diese Funktion L_XYZ wurde nur erstellt weil der Gnu-Debugger mit F10
    // nicht ueber die in einer DLL implementierten Funktion XYZ
    // hinweg springt.
   return  Write_Pic (file_out_name, Pic_Out);
}
#define Write_Pic L_Write_Pic



int L_copy_all (PIC *Pic_In,PIC *Pic_Out)
{
    // Diese Funktion L_XYZ wurde nur erstellt weil der Gnu-Debugger mit F10
    // nicht ueber die in einer DLL implementierten Funktion XYZ
    // hinweg springt.
    return copy_all (Pic_In, Pic_Out);
}
#define copy_all L_copy_all

#endif // QT_DEBUG_BUG

