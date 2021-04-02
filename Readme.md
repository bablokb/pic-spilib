SPI Library for PIC Microcontrollers
====================================

This is a simple SPI-library for PIC microcontrollers, targeted at
developers who do not want to use Microchips development tools, e.g.
because they use Linux as the development system.


Library
-------

Definitions are in the `include`-directory, implementation is in `lib/spi.c`.
Since the registers and default pins differ from mcu to mcu, you need
to provide a pic-specific `include/spi_xxx.h` file with register and
pin definitions.

Currently, the following PICs are supported:

  - PIC12F1840
  - PIC16F690
  - PIC16F1829

If you add a new mcu, please provide a pull-request.


Sample Implementation
---------------------

You will find a simple implementation of a host (formally known as *master*)
and a device (known as *slave*) in the directories `host/` and `device/`
respectively.

Host and device exchange a counter. Both devices have an additional
shift-register attached to them (see <https://github.com/bablokb/pic-sn74hc595>).
The shift-register drives LEDs, so this setup allows for monitoring of
the bytes exchanged by the PICs.

The sample sources and makefiles assume that you have installed my
[pic-toolchain](https://github.com/bablokb/pic-toolchain), which supports
both sdcc/gpasm and XC8.

The setup for two PIC12F1840:

  - host
      * RA0: SDO -> device SDI (RA2), -> SR1-SERin
      * RA1: CLK -> device CLK (RA1), -> SR1-CLK
      * RA2: SDI <- device SDO (RA4)
      * RA3: unused
      * RA4: CS  -> device SS (RA0)
      * RA5: -> SR1-PARout

  - device
      * RA0: SS  <- host CS (RA4)
      * RA1: CLK <- host CLK (RA1), -> SR2-CLK
      * RA2: SDI <- host SDO (RA0)
      * RA3: unused
      * RA4: SDO -> host SDI (RA2), -> SR2-SERin
      * RA5: -> SR2-PARout
