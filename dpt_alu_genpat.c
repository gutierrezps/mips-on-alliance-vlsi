#include <time.h>
#include <stdlib.h>
#include "genpat.h"
#include "include/utils.c"


void ALU(int A, int B, char Ctrl) {
	int Res;
	
	AFFECT(cvect(), "A", inttohex(A));
	AFFECT(cvect(), "B", inttohex(B));
	AFFECT(cvect(), "Ctrl", inttostr(Ctrl));
	
	switch(Ctrl) {
		case 0b000: Res = A & B; break;
		case 0b001: Res = A | B; break;
		case 0b010: Res = A + B; break;
		case 0b100: Res = A & ~B; break;
		case 0b101: Res = A | ~B; break;
		case 0b110: Res = A - B; break;
		case 0b111: Res = A < B; break;
	}
	
	AFFECT(cvect(), "Res", inttohex(Res));
	AFFECT(cvect(), "Zero", inttostr(Res == 0));
	AFFECT(cvect(), "Vdd", "1");
	
	curvect++;
}

int main () {
	int i;
	
	srand(time(NULL));
	
	DEF_GENPAT("dpt_alu_genpat");

	DECLAR("A"   , ":2", "X", IN , "31 down to 0", "");
	DECLAR("B"   , ":2", "X", IN , "31 down to 0", "");
	DECLAR("Ctrl", ":2", "X", IN ,  "2 down to 0", "");
	
	DECLAR("Res" , ":2", "X", OUT, "31 down to 0", "");
	DECLAR("Zero", ":2", "B", OUT, "", "" );
	
	DECLAR("Vdd" , ":2", "B", IN , "", "" );
	DECLAR("Vss" , ":2", "B", IN , "", "" );

	LABEL ("ALU");

	AFFECT("0", "Vdd", "0b1");
	AFFECT("0", "Vss", "0b0");
	
	
	// AND : Ctrl = 0
	ALU(0x00000000, 0x00000000, 0);
	ALU(0x00000000, 0xFFFFFFFF, 0);
	ALU(0xFFFFFFFF, 0x00000000, 0);
	ALU(0xFFFFFFFF, 0xFFFFFFFF, 0);
	
	
	// OR : Ctrl = 1
	ALU(0x00000000, 0x00000000, 1);
	ALU(0x00000000, 0xFFFFFFFF, 1);
	ALU(0xFFFFFFFF, 0x00000000, 1);
	ALU(0xFFFFFFFF, 0xFFFFFFFF, 1);	
	
	
	// add : ctrl = 2 (0b010)
	ALU(0xFFFFFFFF, 1, 2);		// test all carry bits, overflow and zero flag
	
	for(i = 0; i < 10; i++) {
		ALU(rand(), rand(), 2);
	}
	
	
	// A AND ~B : Ctrl = 4
	ALU(0x00000000, 0x00000000, 4);
	ALU(0x00000000, 0xFFFFFFFF, 4);
	ALU(0xFFFFFFFF, 0x00000000, 4);
	ALU(0xFFFFFFFF, 0xFFFFFFFF, 4);

	// A OR ~B : Ctrl = 5
	ALU(0x00000000, 0x00000000, 5);
	ALU(0x00000000, 0xFFFFFFFF, 5);
	ALU(0xFFFFFFFF, 0x00000000, 5);
	ALU(0xFFFFFFFF, 0xFFFFFFFF, 5);

	// sub : ctrl = 6 (0b110)
	ALU(0x0F0F0F0F, 0x00F00F00, 6);
	ALU(0xFFFFFFFF, 0xFFFFFFFF, 6);
	ALU(0x00000000, 0x00000001, 6);
	
	for(i = 0; i < 10; i++) {
		ALU(rand(), rand(), 6);
	}
	
	
	// slt : ctrl = 7 (0b111)
	ALU(-300, 255, 7);
	ALU(25, -30, 7);
	
	for(i = 0; i < 10; i++) {
		ALU(rand(), rand(), 7);
	}
	
	SAV_GENPAT();
	
	return 0;
}
