#define op(n, cc, instr, ...) case n: dprintf("pc: %.4X -> %s %s", *REG_PC, #instr, #__VA_ARGS__); {instr(__VA_ARGS__);} cpu_cycles += cc; break

//flags
#define RESET_FLAGS *(REG_F.value) = 0
#define flag(f) ((REG_F).flags->f)
#define fzero(a) flag(z) = (a) == 0 //set if a is 0
#define fhalfcarry8(a,b) flag(h) = (((((a) & 0xF) + ((b) & 0xF)) & 0x10) == 0x10 ) //carry from bit 3 to bit 4
#define fhalfcarry16(a,b) flag(h) = (((((a) & 0xFFF) + ((b) & 0xFFF)) & 0x1000) == 0x1000 ) //carry from bit 11 to bit 12
#define fcarry(a) flag(c) = (a) > 0xFF //carry

//immediate values and other..
#define d8  mem_get_ptr((*REG_PC)++)
#define d16 (uint16_t*)d8
#define a16 mem_get_ptr(*d16)
#define AT(reg) mem_get_ptr(*(reg))

//INSTructions
#define NOP()
#define STOP() cpu_stopped = 1
#define LD(a,b) *(a) = *(b)
#define INC_16(a) (*(a))++
#define INC_8(a) fzero((*(a))++); flag(n) = 0; fhalfcarry8(*(a), *(a)-1)
#define DEC_16(a) (*(a))--
#define DEC_8(a) fzero((*(a))--); flag(n) = 1; fhalfcarry8(*(a), *(a)+1)
#define RLC(a) RESET_FLAGS; uint8_t bit7 = !!(*(a) & 0x80); fzero( (*(a)) = ((*(a)) << 1) | bit7 ); flag(c) = bit7
#define RL(a) RESET_FLAGS; uint8_t c = flag(c); flag(c) = !!((*(a)) && 0x80); fzero( (*(a)) = (((*(a)) << 1) | c ) );
#define RRC(a) RESET_FLAGS; uint8_t bit0 = !!(*(a) & 0x01); fzero( (*(a)) = ((*(a)) >> 1) | bit0 ); flag(c) = bit0
#define RR(a) RESET_FLAGS; uint8_t c = flag(c); flag(c) = !!((*(a)) && 0x01); fzero( (*(a)) = (((*(a)) >> 1) | (c << 7) ) );
#define ADD_16(a,b) fhalfcarry16(*(a), *(b)); (*(a)) += (*(b)); flag(n) = 0; flag(c) = (*(a)) > 0xFFFF
#define JR() *REG_PC += (int8_t)mem_read(*REG_PC)+1
#define JR_nf(f) if (!flag(f)) {JR();}
#define JR_f(f) if (flag(f)) {JR();}
inline void DAA(void) {
	//TODO DADADADAaa
}
#define LD_A_ATHL(sign) LD(REG_A, AT(REG_HL)); *REG_HL = sign 1
#define LD_ATHL_A(sign) LD(AT(REG_HL), REG_A); *REG_HL = sign 1
#define CPL() *REG_A = ~*REG_A

//OPCODES decoding
op(0x00, 4,  NOP);
op(0x01, 12, LD, REG_BC, d16);
op(0x02, 8,  LD, AT(REG_BC), REG_A);
op(0x03, 8,  INC_16, REG_BC);
op(0x04, 4,  INC_8, REG_B);
op(0x05, 4,  DEC_8, REG_B);	
op(0x06, 8,  LD, REG_B, d8);
op(0x07, 4,  RLC, REG_A);
op(0x08, 20, LD, a16, REG_SP);
op(0x09, 8,  ADD_16, REG_HL, REG_BC);
op(0x0A, 8,  LD, REG_A, AT(REG_BC));
op(0x0B, 8,  DEC_16, REG_BC);
op(0x0C, 4,  INC_8, REG_C);
op(0x0D, 4,  DEC_8, REG_C);
op(0x0E, 8,  LD, REG_C, d8);
op(0x0F, 4,  RRC, REG_A);
op(0x10, 4,  STOP);
op(0x11, 12, LD, REG_DE, d16);
op(0x12, 8,  LD, AT(REG_DE), REG_A);
op(0x13, 8,  INC_16, REG_DE);
op(0x14, 4,  INC_8, REG_D);
op(0x15, 4,  DEC_8, REG_D);
op(0x16, 8,  LD, REG_D, d8);
op(0x17, 4,  RL, REG_A);
op(0x18, 12, JR);
op(0x19, 8,  ADD_16, REG_HL, REG_DE);
op(0x1A, 8,  LD, REG_A, AT(REG_DE));
op(0x1B, 8,  DEC_16, REG_DE);
op(0x1C, 4,  INC_8, REG_E);
op(0x1D, 4,  DEC_8, REG_E);
op(0x1E, 8,  LD, REG_E, d8);
op(0x1F, 4,  RR, REG_A);
op(0x20, 8,  JR_nf, z);
op(0x21, 12, LD, REG_HL, d16);
op(0x22, 8,  LD_ATHL_A, +);
op(0x23, 8,  INC_16, REG_HL);
op(0x24, 4,  INC_8, REG_H);
op(0x25, 4,  DEC_8, REG_H);
op(0x26, 8,  LD, REG_H, d8);
op(0x27, 4,  DAA);
op(0x28, 8,  JR_f, z);
op(0x29, 8,  ADD_16, REG_HL, REG_HL);
op(0x2A, 8,  LD_A_ATHL, +);
op(0x2B, 8,  DEC_16, REG_HL);
op(0x2C, 4,  INC_8, REG_L);
op(0x2D, 4,  DEC_8, REG_L);
op(0x2E, 8,  LD, REG_L, d8);
op(0x2F, 4,  CPL);
