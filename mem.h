#ifndef _MEM_H
#define _MEM_H

#include <stdio.h>

int mem_init(gb_header header, FILE* romfile);
void mem_free(void);

uint8_t* mem_get_ptr(uint16_t addr);
uint8_t mem_read(uint16_t addr);
void mem_write(uint16_t addr, uint8_t value);

#endif
