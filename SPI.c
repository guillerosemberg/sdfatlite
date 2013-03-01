#include "SPI.h"

/********** Adaptación de SDCS a GPIO ***********/
static int InitFlag=0;
void SD_ChipSelect(int State){
  if(InitFlag==0){
    PTGDD_PTGDD3=1; 
    InitFlag=1;
  }
  PTGD_PTGD3=State;
}
 
/************************************************/
void SPI_Init(void)
{
  
  //SOPT2 = SOPT2_SPI1PS_MASK;  // Drive PTE as SPI port
  
  SPI_SS = 1;
  _SPI_SS= 1;
  
  SPI2BR = 0x06; // 375 Khz     		
  SPI2C2 = 0x00;  
  SPI2C1 = SPI2C1_SPE_MASK | SPI2C1_MSTR_MASK;

}

/************************************************/
void SPI_Send_byte(UINT8 u8Data)
{
	while(!SPI2S_SPTEF) ;
  (void)SPI2S;
	SPI2DL=u8Data;
	
	
}

/************************************************/
UINT8 SPI_Receive_byte(void)
{
  (void)SPI2DL;
	SPI2DL=0xFF;
	while(!SPI2S_SPRF) ;	
	return(SPI2DL);
}

/************************************************/
void SPI_High_rate(void)
{
  SPI2C1 = 0x00;
  SPI2BR = 0x12; // 4 Mhz, lo mas proximo posible a 4.5 Mhz     		
  SPI2C1 = SPI2C1_SPE_MASK | SPI2C1_MSTR_MASK;

}
