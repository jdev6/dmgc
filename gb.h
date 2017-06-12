#ifndef _GB_H
#define _GB_H

#define dprintf(...) do {fprintf(stderr, "\e[1m[%s() in %s:%i]\e[0m ", __func__, __FILE__, __LINE__); fprintf(stderr, __VA_ARGS__); putc('\n', stderr);} while(0)

#include <stdint.h>

extern const char* rom_type_str[0x100];

typedef struct {
	uint8_t logo[0x30];
	uint8_t title[0x10];
	//some other stuff here..
	uint8_t type;
	uint8_t rom_size;
	uint8_t ram_size;
} gb_header;

int gb_get_header(FILE* romfile, gb_header* header); 

#endif
