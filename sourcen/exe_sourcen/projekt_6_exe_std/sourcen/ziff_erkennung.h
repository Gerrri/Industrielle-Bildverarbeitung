/*********************************************************
  ziff_erkennung.h
  --------------------------------------------------------
  generated at Sat Jun 09 11:09:13 2007
  by snns2c ( Bernward Kett 1995 ) 
*********************************************************/

extern int ziff_erkennung(float *in, float *out, int init);

static struct {
  int NoOfInput;    /* Number of Input Units  */
  int NoOfOutput;   /* Number of Output Units */
  int(* propFunc)(float *, float*, int);
} ziff_erkennungREC = {1225,10,ziff_erkennung};
