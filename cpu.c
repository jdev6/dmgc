#include <stdio.h>

#include "gb.h"
#include "cpu.h"
#include "mem.h"

uint16_t REG_SP[] = {0xFFFE};
uint16_t REG_PC[] = {0x0100};

//value of afbcdehl registers are in array, indivudual reigisters accesed with pointers
uint8_t registers[] = {0x01, 0xB0, 0x00, 0x13, 0x00, 0xD8, 0x01, 0x4D};

uint16_t* REG_AF = 0+(uint16_t*)registers;
uint16_t* REG_BC = 1+(uint16_t*)registers;
uint16_t* REG_DE = 2+(uint16_t*)registers;
uint16_t* REG_HL = 3+(uint16_t*)registers;

//assummed little- endian
uint8_t* REG_A = registers+1;
union {
	uint8_t* value;
	struct {
		uint8_t unused : 4; //bits 0-3
		uint8_t c : 1; //bit 4, carry
		uint8_t h : 1; //bit 5, half carry
		uint8_t n : 1; //bit 6, subtract
		uint8_t z : 1; //bit 7, zero
	}* flags;
} REG_F = {.value = registers+0};
uint8_t* REG_B = registers+3;
uint8_t* REG_C = registers+2;
uint8_t* REG_D = registers+5;
uint8_t* REG_E = registers+4;
uint8_t* REG_H = registers+7;
uint8_t* REG_L = registers+6;

uint8_t cpu_halted = 0;
uint8_t cpu_stopped = 0;
unsigned int cpu_cycles = 0;

void cpu_cycle(void) {
	if (cpu_halted || cpu_stopped) {
		cpu_cycles++;
		return;
	}

	//TODO: interrupt stuff

	uint8_t op = mem_read((*REG_PC)++);	
	switch (op) {
		#include "opcodes.h"
		default: dprintf("UNIMPLEMENTED OPCODE: %X. expect bug. or sudden crash!!! at %.4X", op, *REG_PC);
	}
}
