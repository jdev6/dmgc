#include <stdio.h>
#include <string.h>
#include "gb.h"

const char* rom_type_str[0x100] = {
	[0x00] = "NO MBC",
	[0x01] = "MBC1",
	[0x02] = "MBC1+RAM",
	[0x03] = "MBC1+RAM+BATTERY",
	[0x05] = "MBC2",
	[0x06] = "MBC2+BATTERY",
	[0x08] = "ROM+RAM",
	[0x09] = "ROM+RAM+BATTERY",
	[0x0B] = "MMM01",
	[0x0C] = "MMM01+RAM",
	[0x0D] = "MMM01+RAM+BATTERY",
	[0x0F] = "MBC3+TIMER+BATTERY",
	[0x10] = "MBC3+TIMER+RAM+BATTERY",
	[0x11] = "MBC3",
	[0x12] = "MBC3+RAM",
	[0x13] = "MBC3+RAM+BATTERY",
	[0x15] = "MBC4",
	[0x16] = "MBC4+RAM",
	[0x17] = "MBC4+RAM+BATTERY",
	[0x19] = "MBC5",
	[0x1A] = "MBC5+RAM",
	[0x1B] = "MBC5+RAM+BATTERY",
	[0x1C] = "MBC5+RUMBLE",
	[0x1D] = "MBC5+RUMBLE+RAM",
	[0x1E] = "MBC5+RUMBLE+RAM+BATTERY",
	[0xFC] = "POCKET CAMERA",
	[0xFD] = "BANDAI TAMA5",
	[0xFE] = "HuC3",
	[0xFF] = "HuC1+RAM+BATTERY"
};

int gb_get_header(FILE* romfile, gb_header* header) {
	//retrieve cartridge header info
	uint8_t buffer[0x0150];
	if(!fread(buffer, 1, 0x150, romfile) || feof(romfile) || ferror(romfile)) {
		return 0;
	}
	//checksum
	/* x=0:FOR i=0134h TO 014Ch:x=x-MEM[i]-1:NEXT */
	uint8_t x = 0;
	for (size_t i = 0x0134; i <= 0x014C; i++) {
		x = x - buffer[i]-1;
	}
	if (x != buffer[0x014D]) {
		dprintf("checksum doesnt match, calculated %.4X, BUT header says %.4X", x, buffer[0x014D]);
		return 0;
	} else {
		dprintf("checkksum verified.");
	}
	memcpy(header->logo, buffer+0x104, 0x30);
	memcpy(header->title, buffer+0x134, 0x10);
	header->type = buffer[0x147];
	header->rom_size = buffer[0x148];
	header->ram_size = buffer[0x149];
	return 1;
}

