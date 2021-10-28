#include <stdio.h>
#include "vs1053_types.h"

/* PRIVATE FUNCTIONS HEADERS */
static void _sci_rd(sci_registers_t reg);
static void _sci_wr(sci_registers_t reg, uint16_t value);


/* PRIVATE FUNCTIONS IMPLEMENTATION */
static void _sci_rd(sci_registers_t reg){
    /* buffer  = READ + ADDRESS + 0xff + 0xff */
    /* spi_write_readinto */
}

static void _sci_wr(sci_registers_t reg, uint16_t value){
    /* buffer = WR + ADDRESS + MSB_value + LSB_value */
    /* spi_write */
}


/* PUBLIC FUNCTIONS IMPLEMENATION */
void vs1053_init(){}



