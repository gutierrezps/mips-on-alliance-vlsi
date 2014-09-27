#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genpat.h"
#include "include/utils.c"


#define ATRASO 1


int curvect = 0;
char clk = 0;

char OpCode[7], Funct[7], buffer[9], Instr[100];

char* cvect() { return inttostr(curvect); }

int presentState(int s) {
	int next = 0;
	
	AFFECT(cvect(), "clk", inttostr(clk));
	curvect++;
	clk = !clk;
	AFFECT(cvect(), "clk", inttostr(clk));
	AFFECT(cvect(), "State", inttostr(s));
	
	switch(s) {
		case  0: next =  state0(); break;
		case  1: next =  state1(); break;
		case  2: next =  state2(); break;
		case  3: next =  state3(); break;
		case  4: next =  state4(); break;
		case  5: next =  state5(); break;
		case  6: next =  state6(); break;
		case  7: next =  state7(); break;
		case  8: next =  state8(); break;
		case  9: next =  state9(); break;
		case 10: next = state10(); break;
		case 11: next = state11(); break;
	}
	
	curvect++;
	clk = !clk;
	AFFECT(cvect(), "clk", inttostr(clk));
	
	return next;
}

void reset() {
	LABEL("Reset");
	AFFECT(cvect(), "Reset", "1");
	
	AFFECT(cvect(), "State", "0");
	
	AFFECT(cvect(), "IorD"	 , "0");
	AFFECT(cvect(), "ALUSrcA", "0");
	AFFECT(cvect(), "ALUSrcB", "1");
	AFFECT(cvect(), "ALUOp"	 , "0");
	AFFECT(cvect(), "PCSrc"	 , "0");
	AFFECT(cvect(), "IRWrite", "0");
	AFFECT(cvect(), "PCWrite", "0");
	AFFECT(cvect(), "RegWrite", "0");
	AFFECT(cvect(), "MemWrite", "0");
	AFFECT(cvect(), "Branch", "0");

	curvect++;
	AFFECT(cvect(), "Reset", "0");
}

int state0() {

	LABEL("Fetch");

	AFFECT(cvect(), "IorD"	 , "0");
	AFFECT(cvect(), "ALUSrcA", "0");
	AFFECT(cvect(), "ALUSrcB", "1");
	AFFECT(cvect(), "ALUOp"	 , "0");
	AFFECT(cvect(), "PCSrc"	 , "0");
	AFFECT(cvect(), "IRWrite", "1");
	AFFECT(cvect(), "PCWrite", "1");
	AFFECT(cvect(), "RegWrite", "0");
	AFFECT(cvect(), "MemWrite", "0");
	AFFECT(cvect(), "Branch", "0");
	
	return 1;
}

int state1() {

	LABEL("Decode");
	
	AFFECT(cvect(), "PCWrite", "0");
	AFFECT(cvect(), "IRWrite", "0");
	
	AFFECT(cvect(), "ALUSrcA", "0");
	AFFECT(cvect(), "ALUSrcB", "3");
	AFFECT(cvect(), "ALUOp"	 , "0");

	if(!strcmp(OpCode ,"100011") || !strcmp(OpCode ,"101011"))		// LW or SW
		return 2;
		
	else if(!strcmp(OpCode ,"000000"))		// R-type
		return 6;
		
	else if(!strcmp(OpCode ,"000100"))		// BEQ
		return 8;
		
	else if (!strcmp(OpCode ,"001000"))		// ADDI
		return 9;
		
	else if (!strcmp(OpCode ,"000010"))		// Jump
		return 11;
		
	else {
		fprintf(stderr, "OpCode unknown (0b%s)\n", OpCode);
		exit(1);
	}
}

int state2() {
	
	LABEL("MemAdr");
	
	AFFECT(cvect(), "ALUSrcA", "1");
	AFFECT(cvect(), "ALUSrcB", "2");
	AFFECT(cvect(), "ALUOp"	 , "0");

	if(!strcmp(OpCode ,"100011"))		// LW
		return 3;
		
	else if(!strcmp(OpCode ,"101011"))	// SW
		return 5;
		
}

int state3() {

	LABEL("MemRead");
	
	AFFECT(cvect(), "IorD", "1");
	
	return 4;
	
}

int state4() {

	LABEL("Mem Writeback");
	
	AFFECT(cvect(), "RegDst"	, "0");
	AFFECT(cvect(), "MemtoReg"  , "1");
	AFFECT(cvect(), "RegWrite"  , "1");
	
	return 0;
}

int state5() {
	
	LABEL("Mem Write");
	
	AFFECT(cvect(), "IorD"	  , "1");
	AFFECT(cvect(), "MemWrite", "1");
	
	return 0;
	
}

int state6() {

	LABEL("Execute");
	
	AFFECT(cvect(), "ALUSrcA", "1");
	AFFECT(cvect(), "ALUSrcB", "0");
	AFFECT(cvect(), "ALUOp"  , "0");
	
	return 7;

}

int state7() {

	LABEL("ALU Writeback");
	
	AFFECT(cvect(), "RegDst"  , "1");
	AFFECT(cvect(), "MemtoReg", "0");
	AFFECT(cvect(), "RegWrite", "1");
	
	
	return 0;
}

int state8() {

	LABEL("Branch");
	
	AFFECT(cvect(), "ALUSrcA", "1");
	AFFECT(cvect(), "ALUSrcB", "0");
	AFFECT(cvect(), "ALUOp"  , "1");
	AFFECT(cvect(), "PCSrc"  , "1");
	AFFECT(cvect(), "Branch" , "1");
	
	return 0;
}

int state9() {

	LABEL("ADDI Execute");
	
	AFFECT(cvect(), "ALUSrcA", "1");
	AFFECT(cvect(), "ALUSrcB", "2");
	AFFECT(cvect(), "ALUOp"  , "0");
	
	return 10;
}

int state10() {

	LABEL("ADDI Writeback");
	
	AFFECT(cvect(), "RegDst"  , "0");
	AFFECT(cvect(), "MemtoReg", "0");
	AFFECT(cvect(), "RegWrite", "1");
	
	return 0;
}

int state11() {

	LABEL("Jump");
	
	AFFECT(cvect(), "PCSrc"  , "2");
	AFFECT(cvect(), "PCWrite", "1");

	return 0;

}



int main() {
	int next, line = 1, i;
	FILE *arq = NULL;

	
	arq = fopen("instructions_control.txt", "r+");
	
	if( !arq ) {
		fprintf(stderr, "\nCouldn't open 'instructions' file.\n");
		return 1;
	}
	
	
	DEF_GENPAT("ctrl_fsm_genpat");
	
	
	DECLAR("CLK"	, ":2", "B", IN , "", "");
	DECLAR("Reset"	, ":2", "B", IN , "","");

	DECLAR("State"		, ":2", "X", OUT, "3 down to 0", "");

	DECLAR("OpCode"	, ":2", "B", IN , "5 down to 0", "");
	//DECLAR("Funct"	, ":2", "B", IN , "5 down to 0", "");
	
	// Multiplexer Selects
	DECLAR("MemtoReg"	, ":2", "B", OUT, "", "");
	DECLAR("RegDst"		, ":2", "B", OUT, "", "");
	DECLAR("IorD"		, ":2", "B", OUT, "", "");
	DECLAR("PCSrc"		, ":2", "B", OUT, "1 down to 0", "");
	DECLAR("ALUSrcA"	, ":2", "B", OUT, "", "");
	DECLAR("ALUSrcB"	, ":2", "B", OUT, "1 down to 0", "");
	DECLAR("ALUOp"	, ":2", "B", OUT, "1 down to 0", "");
	
	// Registers Enables
	DECLAR("IRWrite"	, ":2", "B", OUT, "", "");
	DECLAR("MemWrite"	, ":2", "B", OUT, "", "");	
	DECLAR("PCWrite"	, ":2", "B", OUT, "", "");
	DECLAR("RegWrite"	, ":2", "B", OUT, "", "");
	DECLAR("Branch"		, ":2", "B", OUT, "", "");

	DECLAR ("Vdd"		, ":2", "B", IN , "", "");
	DECLAR ("Vss"		, ":2", "B", IN , "", "");


	AFFECT ("0", "Vdd", "1");
	AFFECT ("0", "Vss", "0");
	AFFECT ("0", "CLK", "0");
	AFFECT ("0", "OpCode", "0");
	//AFFECT ("0", "Funct", "0");
	
	reset();
	next = 0;
	
	while(1) {
	
		fgets(Instr, 100, arq);
		Instr[32] = '\0';
		
		if( feof(arq) ) break;	
		
		if( strlen(Instr) != 32 ) {
			fprintf(stderr, "\nError while parsing Instr on line %d: size mismatch (%d)\n", line, strlen(Instr));
			return 1;
		}
		
		for(i = 0; i < 32; i++) {
			if(Instr[i] != '0' && Instr[i] != '1') {
				fprintf(stderr, "\nInvalid character on line %d, col %d: '%c'\n", line, i+1, Instr[i]);
				exit(1);
			}
		}
				
		for(i = 0; i < 6; i++) {
			OpCode[i] = Instr[i];
			Funct[i]  = Instr[26 + i];
		}
		
		OpCode[6] = '\0';
		Funct[6]  = '\0';
		
		
		sprintf(buffer, "0b%s", OpCode);
		AFFECT(cvect(), "OpCode", buffer);
				
		sprintf(buffer, "0b%s", Funct);
		//AFFECT(cvect(), "Funct", buffer);
		
		
		do {
			next = presentState(next);
		} while( next != 0 );
		

		
		line++;
	}
	
	SAV_GENPAT();
	
	return 0;
}
