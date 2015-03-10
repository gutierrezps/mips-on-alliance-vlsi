#include <stdio.h>
#include "genpat.h"
#include "include/utils.c"

void aludec(char aluop, char funct) {
	
	char alucontrol;
	
	if( aluop == 0 ) alucontrol = 0b010;
		
	else if( aluop == 1 ) alucontrol = 0b110;

	else if( aluop == 2 ) {
		switch( funct ) {
			case 0b100000: alucontrol = 0b010; break;
			case 0b100010: alucontrol = 0b110; break;
			case 0b100100: alucontrol = 0b000; break;
			case 0b100101: alucontrol = 0b001; break;
			case 0b101010: alucontrol = 0b111; break;
		}
	}
	else {
		AFFECT(cvect(), "alucontrol", "0b***");
	}
	
	AFFECT(cvect(), "aluop", inttostr(aluop));
	AFFECT(cvect(), "funct", inttostr(funct));
	
	if(aluop != 3)
		AFFECT(cvect(), "alucontrol", inttostr(alucontrol));
	
	curvect++;
}

int main () {
  
	DEF_GENPAT("ctrl_aludec_genpat");

	DECLAR("funct"		, ":2", "B", IN , "5 down to 0", "");
	DECLAR("aluop"		, ":2", "B", IN , "1 down to 0", "");
	DECLAR("alucontrol"	, ":2", "B", OUT, "2 down to 0", "");
	
	DECLAR("vdd", ":2", "B", IN , "", "" );
	DECLAR("vss", ":2", "B", IN , "", "" );

	LABEL ("aludec");

	AFFECT("0", "vdd", "0b1");
	AFFECT("0", "vss", "0b0");
	
	aludec(0, 0);
	aludec(1, 0);
	
	aludec(2, 0b100000);
	aludec(2, 0b100010);
	aludec(2, 0b100100);
	aludec(2, 0b100101);
	aludec(2, 0b101010);
	
	aludec(3, 0b101010);
	
	SAV_GENPAT();
	
	return 0;
}
