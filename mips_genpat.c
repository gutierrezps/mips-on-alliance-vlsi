#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genpat.h"
#include "include/utils.c"

#define ATRASO 1

int curvect = 0;
char clk = 0;

char Instr[33], binInstr[35], OpCode[7], cycles;

char* cvect() { return inttostr(curvect); }

int main() {
	
	int next, line = 1, i;
	FILE *arq = NULL;

	
	arq = fopen("instructions/datapath.txt", "r+");
	
	if( !arq ) {
		fprintf(stderr, "\nCouldn't open file 'instructions/datapath.txt'.\n");
		return 1;
	}
	
	
	DEF_GENPAT("mips_genpat");
	
	
	DECLAR("CLK"	, ":2", "B", IN , "", "");
	DECLAR("Reset"	, ":2", "B", IN , "","");

	DECLAR("ReadData"	, ":2", "X", IN , "31 down to 0", "");
	DECLAR("WriteData"	, ":2", "X", OUT, "31 down to 0", "");
	DECLAR("MemAdr"		, ":2", "X", OUT, "31 down to 0", "");
	
	DECLAR("State"	, ":2", "X", OUT, "3 down to 0", "");
	
	DECLAR ("Vdd"		, ":2", "B", IN , "", "");
	DECLAR ("Vss"		, ":2", "B", IN , "", "");


	AFFECT ("0", "Vdd", "1");
	AFFECT ("0", "Vss", "0");
	AFFECT ("0", "Reset", "1");
	AFFECT ("0", "CLK", "0");
	AFFECT ("0", "ReadData", "0");
	
	curvect++;
	clk = !clk;
	AFFECT(cvect(), "CLK", inttostr(clk));
	curvect++;
	clk = !clk;
	AFFECT(cvect(), "CLK", inttostr(clk));
	AFFECT(cvect(), "Reset", "0");
	
	
	while(1) {
	
		fgets(Instr, 34, arq);
		Instr[32] = '\0';
		
		if( feof(arq) ) break;	
		
		
		if( strlen(Instr) != 32 ) {
			fprintf(stderr, "\nError while parsing Instr on line %d: size mismatch (%d)\n", line, strlen(Instr));
			return 1;
		}
		
		for(i = 0; i < 32; i++) {
			if( (Instr[i] != '0') && (Instr[i] != '1') ) {
				fprintf(stderr, "\nError while parsing Instr on line %d: invalid character '%c'\n", line, Instr[i]);
				exit(1);
			}
		}
		
		sprintf(binInstr, "0b%s", Instr);
		
		AFFECT(cvect(), "ReadData", binInstr);
		
		for(i = 0; i < 6; i++) {
			OpCode[i] = Instr[i];
		}
		OpCode[6] = '\0';
		
		
		if( !strcmp(OpCode ,"100011") )		// LW
			cycles = 5;
			
		else if( !strcmp(OpCode ,"101011") )		// SW
			cycles = 4;
		
		else if(!strcmp(OpCode ,"000000"))		// R-type
			cycles = 4;
		
		else if(!strcmp(OpCode ,"000100"))		// BEQ
			cycles = 3;
		
		else if (!strcmp(OpCode ,"001000"))		// ADDI
			cycles = 4;
		
		else if (!strcmp(OpCode ,"000010"))		// Jump
			cycles = 3;
		
		else {
			fprintf(stderr, "OpCode unknown (0b%s)\n", OpCode);
			exit(1);
		}
		
		for(i = 0; i < cycles; i++) {
			AFFECT(cvect(), "CLK", inttostr(clk));
			curvect++;
			clk = !clk;
			AFFECT(cvect(), "CLK", inttostr(clk));
			curvect++;
			clk = !clk;
		}
		
		line++;
	}
	
	SAV_GENPAT();
	
	return 0;
}
