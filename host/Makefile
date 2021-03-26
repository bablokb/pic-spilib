# --------------------------------------------------------------------------
# SPI library for PIC microcontrollers.
#
# Makefile for the SPI-host (aka master).
#
# Author: Bernhard Bablok
#
# https://github.com/bablokb/pic-spilib
# 
# --------------------------------------------------------------------------

PIN_SPI_CS  = 4
PORT_SPI_CS = A
PIN_SR_OUT  = 5
PORT_SR_OUT = A

PROJECT=host
EXTRA_C=spi.c
EXTRA_ASM=delay.asm
ARCH=pic14

SDCC_ARGS=-DPIN_SPI_CS=$(PIN_SPI_CS) \
          -DPORT_SPI_CS=$(PORT_SPI_CS) \
          -DPIN_SR_OUT=$(PIN_SR_OUT) \
          -DPORT_SR_OUT=$(PORT_SR_OUT) \
          -DSPI_HOST

include ptc_rules.inc
MCLR  = OFF


# --------------------------------------------------------------------------
