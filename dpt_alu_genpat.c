#include <stdio.h>
#include "genpat.h"
#include "include/utils.c"


void alu(int a, int b, char ctrl) {
	int res;
	
	AFFECT(cvect(), "ctrl", inttostr(ctrl));
	AFFECT(cvect(), "a", inttohex(a));
	AFFECT(cvect(), "b", inttohex(b));
	
	switch(ctrl) {
		case 0b000: res = a & b; break;
		case 0b001: res = a | b; break;
		case 0b010: res = a + b; break;
		case 0b110: res = a - b; break;
		case 0b111: res = (a < b); break;
	}
	
	AFFECT(cvect(), "res", inttohex(res));
	AFFECT(cvect(), "zero", inttostr(res == 0));
	AFFECT(cvect(), "vdd", "1");
	
	curvect++;
}

int main () {
  
	DEF_GENPAT("dpt_alu_genpat");

	DECLAR("a"   , ":2", "X", IN , "31 down to 0", "");
	DECLAR("b"   , ":2", "X", IN , "31 down to 0", "");
	DECLAR("ctrl", ":2", "X", IN ,  "2 down to 0", "");
	
	DECLAR("res" , ":2", "X", OUT, "31 down to 0", "");
	DECLAR("zero", ":2", "B", OUT, "", "" );
	
	DECLAR("vdd" , ":2", "B", IN , "", "" );
	DECLAR("vss" , ":2", "B", IN , "", "" );

	LABEL ("alu");

	AFFECT("0", "vdd", "0b1");
	AFFECT("0", "vss", "0b0");
	
	
	// and : ctrl = 0 (0b000)
	alu(0xF0F0F0F0, 0x0F0F0F0F, 0);
	alu(0xFFFF0000, 0xFFFFFFFF, 0);
	alu(0xFFFFFFFF, 0x0000FFFF, 0);
	
	
	// or : ctrl = 1 (0b001)
	alu(0xF0F0F0F0, 0x0F0F0F0F, 1);
	alu(0x00FF000F, 0xF0F00F00, 1);	
	
	
	// add : ctrl = 2 (0b010)
	alu(255, 255, 2);
	alu(-300, -20, 2);
	alu(0xFFFFFFFF, 1, 2);


	// sub : ctrl = 6 (0b110)
	alu(0x0F0F0F0F, 0x00F00F00, 6);
	alu(0xFFFFFFFF, 0xFFFFFFFF, 6);
	alu(0x00000000, 0x00000001, 6);
	
	
	// slt : ctrl = 7 (0b111)
	alu(-300, 255, 7);
	alu(25, -30, 7);
	
	SAV_GENPAT();
	
	return 0;
}
