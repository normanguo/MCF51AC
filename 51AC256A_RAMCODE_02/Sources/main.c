#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

///////////////////////////////////////////////////////////////////
//
// A section testram is added in linker file Project.lcf
// vraibles and codes can be placed in the section.
// User needs to save the code in Flash or external memory, load it
// into RAM before executing.
//
// Disconnect the debugger, power on and off the target board to check the effect
//
///////////////////////////////////////////////////////////////////

#pragma define_section mySection ".testram" far_absolute RWX

// Define variable in section testram
__declspec (mySection) volatile byte array[10];

// Define function in section testram
__declspec (mySection) unsigned int test_function01(unsigned int n) {

  static unsigned int counter = 0;
  
  counter += n;
  PTFD_PTFD0 = ~PTFD_PTFD0;
  PTFD_PTFD1 = ~PTFD_PTFD1;
  
} 

// test_function01 generated code in .s19 These code can be saved in external
// flash or EEPROM and laoded before executing
// S32100807000  2F07D1AD00001E38800A0887000075B8800A721FE3AAE2AA4682A341  BE
// S3110080701C  C4818E8211C7800A2E1F4E75  1B
// Toggle PTFD0
const byte flash_code1[0x28] = {
  0x2F,0x07,0xD1,0xAD,0x00,0x00,0x1E,0x38,0x80,0x0A,0x08,0x87,0x00,0x00,0x75,0xB8,
  0x80,0x0A,0x72,0x1F,0xE3,0xAA,0xE2,0xAA,0x46,0x82,0xA3,0x41,0xC4,0x81,0x8E,0x82,
  0x11,0xC7,0x80,0x0A,0x2E,0x1F,0x4E,0x75
};

// test_function01 generated code in .s19
// S32100807000  2F07D1AD00001E38800A0887000175B8800A721EE3AA721FE2AA4682  11
// S3170080701C  A341C4817382E3898E8111C7800A2E1F4E75  D1
// Toggle PTFD1
const byte flash_code2[0x2E] = {
  0x2F,0x07,0xD1,0xAD,0x00,0x00,0x1E,0x38,0x80,0x0A,0x08,0x87,0x00,0x01,0x75,0xB8,
  0x80,0x0A,0x72,0x1E,0xE3,0xAA,0x72,0x1F,0xE2,0xAA,0x46,0x82,0xA3,0x41,0xC4,0x81,
  0x73,0x82,0xE3,0x89,0x8E,0x81,0x11,0xC7,0x80,0x0A,0x2E,0x1F,0x4E,0x75
};


// delay fuction used for demo
void delay(unsigned long counter) {
  unsigned int j;
  for(j = 0;j < counter;j ++) {
     __RESET_WATCHDOG();
     asm {
     nop;
     nop;
    }
  }
}

void CopyCode2RAM(char *src, char *dest, long size) { 

  if (dest != src) 
  while (size--) 
    *dest++ = *src++; 

}

void main(void) {

  byte i;
  
  EnableInterrupts; /* enable interrupts */
  /* include your code here */
  PTFDD = 0xFF;            // Just for test, PortF configured as output
  PTFD = 0xAA;

  for(i = 0;i < 10;i ++) {
    array[i] = 0xAA;
  }
  
//CopyCode2RAM((char*)flash_code1, ((char *)0x807000), 0x28);
//CopyCode2RAM((char*)flash_code2, ((char *)0x807000), 0x2E);
  
  for(;;) {
    delay(100000);

    test_function01(5);
  }
    

  for(;;) {
    __RESET_WATCHDOG(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
