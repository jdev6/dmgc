#define opcode(op, name, wath) case op: dprintf("PC:%.4X: %s", *REG_PC, name); wath; break
#define cycles cpu_cycles+=

opcode(0x00, "NOP", {
	cycles 4;
});

#define LD_r_n(r) *REG_##r = mem_read((*REG_PC)++)

opcode(0x06, "LD B,n", {
	LD_r_n(B);
	cycles 8;
});

opcode(0x0E, "LD C,n", {
	LD_r_n(C);
	cycles 8;
});

opcode(0x16, "LD D,n", {
	LD_r_n(D);
	cycles 8;
});

opcode(0x1E, "LD E,n", {
	LD_r_n(E);
	cycles 8;
});

opcode(0x26, "LD H,n", {
	LD_r_n(H);
	cycles 8;
});

opcode(0x2E, "LD L,n", {
	LD_r_n(L);
	cycles 8;
});

//atr = (r)

#define LD_r_r(r1,r2) *REG_##r1 = *REG_##r2
#define LD_atr_r(atr,r) mem_write(*REG_##atr, *REG_##r)
#define LD_r_atr(r,atr) *REG_##r = mem_read(*REG_##atr)

opcode(0x7F, "LD A,A", {
	//LD_r_r(A,A);
	cycles 4;
});

opcode(0x78, "LD A,B", {
	LD_r_r(A,B);
	cycles 4;
});

opcode(0x79, "LD A,C", {
	LD_r_r(A,C);
	cycles 4;
});

opcode(0x7A, "LD A,D", {
	LD_r_r(A,D);
	cycles 4;
});

opcode(0x7B, "LD A,E", {
	LD_r_r(A,E);
	cycles 4;
});

opcode(0x7C, "LD A,H", {
	LD_r_r(A,H);
	cycles 4;
});

opcode(0x7D, "LD A,L", {
	LD_r_r(A,L);
	cycles 4;
});

opcode(0x7E, "LD A,(HL)", {
	LD_r_atr(A,HL);
	cycles 8;
});

opcode(0x40, "LD B,B", {
	//LD_r_r(r,t);
	cycles 4;
});

opcode(0x41, "LD B,C", {
	LD_r_r(B,C);
	cycles 4;
});

opcode(0x42, "LD B,D", {
	LD_r_r(B,D);
	cycles 4;
});

opcode(0x43, "LD B,E", {
	LD_r_r(B,E);
	cycles 4;
});

opcode(0x44, "LD B,H", {
	LD_r_r(B,H);
	cycles 4;
});

opcode(0x45, "LD B,L", {
	LD_r_r(B,L);
	cycles 4;
});

opcode(0x46, "LD B,(HL)", {
	LD_r_atr(B,HL);
	cycles 8;
});

opcode(0x48, "LD C,B", {
	LD_r_r(C,B);
	cycles 4;
});

opcode(0x49, "LD C,C", {
	//LD_r_r(C,C);
	cycles 4;
});

opcode(0x4A, "LD C,D", {
	LD_r_r(C,D);
	cycles 4;
});

opcode(0x4B, "LD C,E", {
	LD_r_r(C,E);
	cycles 4;
});

opcode(0x4C, "LD C,H", {
	LD_r_r(C,H);
	cycles 4;
});

opcode(0x4D, "LD C,L", {
	LD_r_r(C,L);
	cycles 4;
});

opcode(0x4E, "LD C,(HL)", {
	LD_r_atr(C,HL);
	cycles 8;
});

opcode(0x50, "LD D,B", {
	LD_r_r(D,B);
	cycles 4;
});

opcode(0x51, "LD D,C", {
	LD_r_r(D,C);
	cycles 4;
});

opcode(0x52, "LD D,D", {
	//LD_r_r(D,C);
	cycles 4;
});

opcode(0x53, "LD D,E", {
	LD_r_r(D,E);
	cycles 4;
});

opcode(0x54, "LD D,H", {
	LD_r_r(D,H);
	cycles 4;
});

opcode(0x55, "LD D,L", {
	LD_r_r(D,L);
	cycles 4;
});

opcode(0x56, "LD D,(HL)", {
	LD_r_atr(D,HL);
	cycles 8;
});

opcode(0x58, "LD E,B", {
	LD_r_r(E,B);
	cycles 4;
});

opcode(0x59, "LD E,C", {
	LD_r_r(E,C);
	cycles 4;
});

opcode(0x5A, "LD E,D", {
	LD_r_r(E,D);
	cycles 4;
});

opcode(0x5B, "LD E,E", {
//	LD_r_r(E,E);
	cycles 4;
});

opcode(0x5C, "LD E,H", {
	LD_r_r(E,H);
	cycles 4;
});

opcode(0x5D, "LD E,L", {
	LD_r_r(E,L);
	cycles 4;
});

opcode(0x5E, "LD E,(HL)", {
	LD_r_atr(E,HL);
	cycles 8;
});

opcode(0x60, "LD H,B", {
	LD_r_r(H,B);
	cycles 4;
});

opcode(0x61, "LD H,C", {
	LD_r_r(H,C);
	cycles 4;
});

opcode(0x62, "LD H,D", {
	LD_r_r(H,D);
	cycles 4;
});

opcode(0x63, "LD H,E", {
	LD_r_r(H,E);
	cycles 4;
});

opcode(0x64, "LD H,H", {
	//LD_r_r(H,H);
	cycles 4;
});

opcode(0x65, "LD H,L", {
	LD_r_r(H,L);
	cycles 4;
});

opcode(0x66, "LD H,(HL)", {
	LD_r_atr(H,HL);
	cycles 8;
});

opcode(0x68, "LD L,B", {
	LD_r_r(L,B);
	cycles 4;
});

opcode(0x69, "LD L,C", {
	LD_r_r(L,C);
	cycles 4;
});

opcode(0x6A, "LD L,D", {
	LD_r_r(L,D);
	cycles 4;
});

opcode(0x6B, "LD L,E", {
	LD_r_r(L,E);
	cycles 4;
});

opcode(0x6C, "LD L,H", {
	LD_r_r(L,H);
	cycles 4;
});

opcode(0x6D, "LD L,L", {
	//LD_r_r(L,L);
	cycles 4;
});

opcode(0x6E, "LD L,(HL)", {
	LD_r_atr(L,HL);
	cycles 8;
});


opcode(0x70, "LD (HL),B", {
	LD_atr_r(HL,B);
	cycles 8;
});

opcode(0x71, "LD (HL),C", {
	LD_atr_r(HL,C);
	cycles 8;
});

opcode(0x72, "LD (HL),D", {
	LD_atr_r(HL,D);
	cycles 8;
});

opcode(0x73, "LD (HL),E", {
	LD_atr_r(HL,E);
	cycles 8;
});

opcode(0x74, "LD (HL),H", {
	LD_atr_r(HL,B);
	cycles 8;
});

opcode(0x75, "LD (HL),L", {
	LD_atr_r(HL,B);
	cycles 8;
});

opcode(0x36, "LD (HL),n", {
	mem_write(*REG_HL, mem_read((*REG_PC)++));
	cycles 12;
});

