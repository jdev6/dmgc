#include <stdio.h>
#include <stdlib.h>
#include "gb.h"
#include "mem.h"

uint8_t* rom_banks[128]; //each bank is 16KB, max 128 banks
uint8_t rom_bank_count;

uint8_t* wram; //8KB of interlan work ram
uint8_t* vram; //8KB video ram
uint8_t* hram; //high ram.
uint8_t iereg; //interrrurpt enable regisetr

int mem_init(gb_header header, FILE* romfile) {
	/* init rom */
	rom_bank_count = 0;
	if (header.type != 0) {
		//TODO implernent mbcs
		dprintf("MBC NOT IMPLEMENTED");
		return 0;
	} else {
		rom_bank_count = 2; //no MBC -> 2 16kb banks
		for (int i = 0; i < rom_bank_count; i++) {
			rom_banks[i] = malloc(1024*16);
			if (rom_banks[i] == NULL) {
				dprintf("couldnt ALLOCATE 16kb memory. mayber your computer IS on fire,");
				return 0;
			}

			if (feof(romfile) || !fread(rom_banks[i], 1, 1024*16, romfile) || ferror(romfile)) {
				dprintf("COUldnt fread to bank %i. bye", i);
				return 0;
			}
		}
	}
	
	/* init ram */
	wram = malloc(1024*8); //its 8kb
	if (wram == NULL) {
		dprintf("coan't allocate 8K of wram.. maybe broked computer");
		return 0;
	}

	/* init vram */
	vram = malloc(1024*8); //8KB
	if (vram == NULL) {
		dprintf("cant allocate 8K of VIDEOram.. maybe broke computer");
		return 0;
	}

	/* init hram */
	hram = malloc(126); //126 uint8_ts.
	if (hram == NULL) {
		dprintf("wath");
		return 0;
	}

	return 1;	
}

void mem_free(void) {
	dprintf("freeing memory");
	/* free rom */
	for (int i = 0; i < rom_bank_count; i++) {
		if (rom_banks[i] != NULL) {
			free(rom_banks[i]);
		}
	}
	/* free ram */
	if (wram != NULL) {
		free(wram);
	}

	if (vram != NULL) {
		free(vram);
	}

	if (hram != NULL) {
		free(hram);
	}
}

uint8_t* mem_get_ptr(uint16_t addr) {
	#define range(l, u) (addr >= (l) && addr <= (u))
	#define UNIMPLEMENTED return NULL

	//rom bank 0
	if (range(0x0000, 0x3FFF))
		return rom_banks[0]+addr;

	//rom bank n
	else if (range(0x4000, 0x7FFF))
		return rom_banks[1]+addr-0x4000; //TODO: implenent MBC And bank switching

	//vram
	else if (range(0x8000, 0x9FFF))
		return vram+addr-0x8000;

	//TODO: external ram
	else if (range(0xA000, 0xBFFF))
		UNIMPLEMENTED;

	//work ram
	else if (range(0xC000, 0xDFFF))
		return wram+addr-0xC000;

	//echo of work ram
	else if (range(0xE000, 0xFDFF))
		return wram+addr-0xE000;

	//TODO: oam
	else if (range(0xFE00, 0xFE9F))
		UNIMPLEMENTED;
	
	//nintendo marcked this as unusable..
	else if (range(0xFEA0, 0xFEFF))
		return NULL;

	//I/O ports
	else if (range(0xFF00, 0xFF7F))
		UNIMPLEMENTED;

	//HRAM
	else if (range(0xFF80, 0xFFFE))
		return hram+addr-0xFF80;
	
	//IE
	else if (addr == 0xFFFF)
		return &iereg;

	return NULL;
	#undef range
	#undef UNIMPLEMENTED
}

uint8_t mem_read(uint16_t addr) {
	uint8_t* ptr = mem_get_ptr(addr);
	if (ptr == NULL) {
		dprintf("cant get value at addr %.4x", addr);
		return 0xFF;
	}
	return *ptr;
}

void mem_write(uint16_t addr, uint8_t value) {
	uint8_t* ptr = mem_get_ptr(addr);
	if (ptr == NULL) {
		dprintf("cant set value at addr %.4x", addr);
		return;
	}
	*ptr = value;
}
