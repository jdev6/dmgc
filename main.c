#include <stdio.h>

#include "gb.h"
#include "mem.h"
#include "cpu.h"

int main(int argc, char** argv) {
	if (argc >= 2) {
		FILE* romfile = fopen(argv[1], "rb");
		if (!romfile) {
			dprintf("cant open rom %s", argv[1]);
			return 1;
		}
		gb_header header;
		if (!gb_get_header(romfile, &header)) {
			dprintf("couldnt get header");
			fclose(romfile);
			return 1;
		}
		dprintf(
		"ROM %s\n"
		"title: '%s'\n"
		"cart type: %s\n"
		"rom size: %uKB\n"
		"ram size: %u", argv[1], header.title, rom_type_str[header.type], 32 << header.rom_size, header.ram_size);
		
		if (!mem_init(header, romfile)) {
			dprintf("coulndt init memory");
			mem_free();
			fclose(romfile);
			return 1;
		}
		dprintf("ready");

		while (1) {
			cpu_cycle();
			//ppu_cycle();
			//break;
		}
		
		mem_free();
		fclose(romfile);
	} else {
		dprintf("no rom provided");
		return 1;
	}
	return 0;
}
