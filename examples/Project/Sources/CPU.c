#include "MCF51JM128.h"

void CPU_Init(void)
{
  /* ### MC9S08JM60_44 "Cpu" init code ... */
  /*  PE initialization code after reset */

  /* Common initialization of the write once registers */
  /* SOPT1: COPT=0,STOPE=0 */
  SOPT1 = 0x13;                                      
  /* SPMSC1: LVWF=0,LVWACK=0,LVWIE=0,LVDRE=1,LVDSE=1,LVDE=1,BGBE=0 */
  SPMSC1 = 0x1C;                                      
  /* SPMSC2: LVDV=0,LVWV=0,PPDF=0,PPDACK=0,PPDC=0 */
  SPMSC2 = 0x00;                                      
  /*  System clock initialization */
  if (*(unsigned char*far)0xFFAF != 0xFF) { /* Test if the device trim value is stored on the specified address */
    MCGTRM = *(unsigned char*far)0xFFAF; /* Initialize MCGTRM register from a non volatile memory */
    MCGSC = *(unsigned char*far)0xFFAE; /* Initialize MCGSC register from a non volatile memory */
  }

  /* ICSC1: CLKS=0,RDIV=0,IREFS=1,IRCLKEN=1,IREFSTEN=0 */
  //ICSC1 = 0x06;
  /* ICSC2: BDIV=0,RANGE=0,HGO=0,LP=0,EREFS=0,ERCLKEN=0,EREFSTEN=0 */
  //ICSC2 = 0x00;
  /*! Espera de la estabilizacion de la fuente de reloj interna */
  //while(!ICSSC_IREFST) {
  //};
  
  /* MCGC2: BDIV=0,RANGE=1,HGO=1,LP=0,EREFS=1,ERCLKEN=1,EREFSTEN=0 */
  /*! Osilador en alta ganancia, referencia externa hablitada y cristal de 12MHz en rango alto */
  MCGC2 = MCGC2_HGO_MASK | MCGC2_EREFS_MASK | MCGC2_RANGE_MASK | MCGC2_ERCLKEN_MASK;

  /*! Espera de la estabilizacion de la referencia de reloj externa */
  while (MCGSC_OSCINIT) ;
 
  /* MCGC1: CLKS=10,RDIV=011,IREFS=0,IRCLKEN=0,IREFSTEN=0 */
  /*! Seleccion de clock externo, division en 4 para obtener una referencia 1.5 MHz 
      a partir del cristal de 12 MHz.*/
  MCGC1 = 0x98;
  
  /*! Espera de la estabilizacion de la fuente de reloj externa */
  while (!MCGSC_IREFST) ;
  while (!MCGSC_CLKST) ;
 
  /* MCGC3: LOLIE=0,PLLS=1,CME=0,VDIV=1000 */
  /*! Seleccion del PLL con un factor de divion de 32, obteniendo 48 MHz a partir de 
      la refernecia de 1.5 MHz */
  MCGC3 = MCGC3_PLLS_MASK | 8;
  
  /*! Espera de la estabilizacion del PLL y el enganche en frecuencia del mismo */
  while (!MCGSC_PLLST) ;
  while (!MCGSC_LOCK) ;

  /* MCGC1: CLKS=00,RDIV=018,IREFS=0,IRCLKEN=0,IREFSTEN=0 */
  /*! Seleccion de PLL como reloj, division en 4 para obtener una referencia 1.5 MHz 
      a partir del cristal de 12 MHz.*/
  MCGC1 = 0x18;
  while (!MCGSC_CLKST) ;
  
  /*! El procesador queda funcionando a 24MHz de frecuencia de bus y 48MHz a la salida del generador de reloj */

  FCDIV=0x4E;                     // PRDIV8=1; DIV[5:0]=14, flash clock should be 150-200kHz
                                  // bus clock=24M, flash clock=fbus/8/(DIV[5:0]+1)
                                  
  USBTRC0=0x04; //Energizo pin VUSB33 para alimentar tarjeta SD                         
}
