#include <hidef.h> 	  	/* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "FslTypes.h"   /* Freescale Types */
#include "CPU.h"	    	/* MCU Initialization*/
#include "SD.h"         /* SD Driver */
#include "FAT.h"        /* FAT Driver */

#define FILE_NAME "LOG.txt" /* LOG file name */                                                              

/* Global variables */
UINT8 gu8IntFlags=0;
UINT8 u16SampleCounter;
//UINT8 gau8LogArray[SAMPLES_WRITE];
UINT8 gu8Result[3]={0,0,0};

void imdead(void){
  for(;;)
    __RESET_WATCHDOG();
}

void main(void) {
  UINT8 u8Error;
  unsigned char FileReadBuffer[BLOCK_SIZE];
  UINT16 u16FileLength;
   
  CPU_Init();
  SPI_Init();
  EnableInterrupts; 
  /* include your code here */
  
  u8Error=SD_Init();
  if(u8Error==OK){ //SD initializes right
    FAT_Read_Master_Block();
    
    
    /*CREATE LOG1.TXT*/
    /* Creating the file if it doesn't exist */
    if (FAT_FileOpen("LOG1.TXT", MODIFY) == FILE_NOT_FOUND) 
    {
      u8Error=FAT_FileOpen("LOG1.TXT",CREATE); 
    } 
    FAT_FileClose();   

    /*Writing the file*/
    FAT_FileOpen("LOG1.TXT", MODIFY);
    FAT_FileWrite("UNO",3);
    FAT_FileClose();
    
    /*CREATE LOG2.TXT*/
    u8Error=FAT_FileOpen("LOG2.TXT",CREATE); 
    FAT_FileClose();
    FAT_FileOpen("LOG2.TXT", MODIFY);
    FAT_FileWrite("DOS",3);
    FAT_FileClose();
    
    /*CREATE LOG3.TXT*/
    u8Error=FAT_FileOpen("LOG3.TXT",CREATE); 
    FAT_FileClose();
    FAT_FileOpen("LOG3.TXT", MODIFY);
    FAT_FileWrite("TRE",3);
    FAT_FileClose();    
    
    /*DELETE LOG2.TXT*/
    /*Deleting the file*/
    FAT_FileOpen("LOG2.TXT", DELETE);
    FAT_FileClose();   
    
    /*Reading the file*/
    //FAT_FileOpen(FILE_NAME, READ);
    //u16FileLength=FAT_FileRead(FileReadBuffer);
       
  
  }
  for(;;) {
    __RESET_WATCHDOG(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}