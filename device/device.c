// --------------------------------------------------------------------------
// SPI test program
//
// This is the SPI-device. It starts by sending a zero, and then sends the
// byte received from the SPI-host incremented by 1.
//
// CLK and SDO are additionally connected to a shift-register.
// After sending the byte, the PIN_SR_OUT is toggled to expose
// the output on the shift-register. The shift-register thus visualizes
// the byte sent to the SPI-host.
//
// Author: Bernhard Bablok
//
// https://github.com/bablokb/pic-spi
// --------------------------------------------------------------------------

#include "picconfig.h"
#include <stdint.h>

#include "delay.h"

// shift-register output pin
#ifndef PIN_SR_OUT
  #define PIN_SR_OUT 5
#endif
#ifndef PORT_SR_OUT
  #define PORT_SR_OUT A
#endif
#define ANSEL_SR_OUT _CONCAT(ANSEL,PORT_SR_OUT)
#define TRIS_SR_OUT  _CONCAT(TRIS,PORT_SR_OUT)
#define GP_SR_OUT    _CONCAT(R,_CONCAT(PORT_SR_OUT,PIN_SR_OUT))

#include "spi.h"

CONFIG_WORDS;

////////////////////////////////////////////////////////////////////////
// Intialize registers

static void init(void) {
  // configure registers

  __asm__ ("CLRWDT");            // clear WDT even if WDT is disabled

  // some standard settings
  ANSELA   = 0;
  PORTA    = 0;
  LATA     = 0;
  CM1CON0  = 0x07;               // disable comparator for GP0-GP2
  WPUA     = 0;                  // default: no pullups on any pin
  NOT_GPPU = 0;                  // but enable pullups if set
  INTCON   = 0;                  // clear interrupt flag bits
  GIE      = 0;                  // global interrupt disable

  // PIN_SR_OUT is digital output
  bitclear(ANSEL_SR_OUT,PIN_SR_OUT);
  bitclear(TRIS_SR_OUT,PIN_SR_OUT);
  GP_SR_OUT = 0;

  INIT_SPECIAL;
  CLOCK_4MHZ;
}

////////////////////////////////////////////////////////////////////////
// Interrupt service routine

static void isr(void) __interrupt 0 {
}

// --- main program   --------------------------------------------------------

void main(void) {
  uint8_t data = 0xFF;
  init();
  spi_init(SPI_SMP_MOD | SPI_CKE_I2A, // SMP=0, CKE=0
           SPI_SSPM_DEVICE_SS_EN |    // device-mode, SS-pin control enabled
           SPI_CKP_HIGH,              // CKP=1
           0x0);                      // baud-rate 0x0
  while (1) {
    // read data (blocking), return last data
    data = spi_read(data);
    // enable shift-register output
    GP_SR_OUT = 1;
    GP_SR_OUT = 0;
  }
}
