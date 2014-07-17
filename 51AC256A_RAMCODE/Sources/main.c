#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

//define the max length for a code buffer in RAM
#define RAM_CODE_SIZE      128
byte codeInRam[RAM_CODE_SIZE];   //RAM buffer


//=============================================================================
// Test function which will be copied to RAM
//=============================================================================
byte TestFunction01(byte cmd)
{
   byte test_flag = 1;
   static unsigned long mycounter = 0;
   
   if(cmd == 0) {                      // just for test
      return(0);                       // return with error flag
   }

   if(cmd == 1) {                      // just for test
      mycounter ++;
   }
   
   return(1);                          // return with success
}


//=============================================================================
// - Copy ROM data into RAM buffer 'codeInRam'
// - Input: romPtr - byte pointer of ROM data
//          size   - no. of bytes need to be copied
// - Return: no. of data bytes actually copied
//=============================================================================
word CopyRom2Ram(byte* romPtr, word size)
{
   word i;
   
   if (size==0 || size>RAM_CODE_SIZE)
      return(0);  //no data copied
   
   //copy ROM data into RAM
   for (i=0;i<size;i++) {
     codeInRam[i] = *romPtr++;
      
   }
   
   return(i);     //return with no. of bytes copied
}


void main(void) {

  byte i = 0;

  EnableInterrupts; /* enable interrupts */
  /* include your code here */

  //Copy test function code into RAM
  CopyRom2Ram((byte*)TestFunction01, 128);
  
  i = ((byte (*)(byte))codeInRam)(0x00);
  i = ((byte (*)(byte))codeInRam)(0x01);
  i = ((byte (*)(byte))codeInRam)(0x01);
  

  for(;;) {
    __RESET_WATCHDOG(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
