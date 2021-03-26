# --------------------------------------------------------------------------
# SPI library for PIC microcontrollers.
#
# Makefile for the SPI-device (aka slave).
#
# Author: Bernhard Bablok
#
# https://github.com/bablokb/pic-spilib
# 
# --------------------------------------------------------------------------

PIN_SR_OUT  = 5
PORT_SR_OUT = A

PROJECT=device
EXTRA_C=spi.c
EXTRA_ASM=delay.asm
ARCH=pic14

SDCC_ARGS=-DPIN_SR_OUT=$(PIN_SR_OUT) \
          -DPORT_SR_OUT=$(PORT_SR_OUT) \
          -DSPI_ALT_PIN \
          -DSPI_DEVICE 

include ptc_rules.inc
MCLR  = OFF


# --------------------------------------------------------------------------
