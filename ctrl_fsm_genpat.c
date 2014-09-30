#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genpat.h"
#include "include/utils.c"

int curvect = 0;
char CLK = 0;

char * cvect() { return inttostr(curvect); }

void toggleClock() {
    CLK = !CLK;
    AFFECT(cvect(), "CLK", inttostr(CLK));
}

#include "include/read_decode.c"
#include "include/aludec.c"
#include "include/fsm.c"


int main() {
	FILE *arq = NULL;
    
    char patFilename[] = __FILE__;
    patFilename[ strlen(patFilename)-2 ] = '\0';

	arq = fopen("instructions/control.txt", "r+");
	
	if( !arq ) {
		fprintf(stderr, "\nCouldn't open 'instructions/control.txt' file.\n");
		return 1;
	}
	
	DEF_GENPAT(patFilename);
	
	DECLAR("CLK"	, ":2", "B", IN , "", "");
	DECLAR("Reset"	, ":2", "B", IN , "","");

	DECLAR("State"		, ":2", "X", OUT, "3 down to 0", "");

	DECLAR("Opcode"	, ":2", "B", IN , "5 down to 0", "");
	
	// Multiplexer Selects
	DECLAR("MemtoReg"	, ":2", "B", OUT, "", "");
	DECLAR("RegDst"		, ":2", "B", OUT, "", "");
	DECLAR("IorD"		, ":2", "B", OUT, "", "");
	DECLAR("PCSrc"		, ":2", "B", OUT, "1 down to 0", "");
	DECLAR("ALUSrcA"	, ":2", "B", OUT, "", "");
	DECLAR("ALUSrcB"	, ":2", "B", OUT, "1 down to 0", "");
	DECLAR("ALUOp"	    , ":2", "B", OUT, "1 down to 0", "");
	
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
    AFFECT ("0", "Reset", "1");
    AFFECT ("0", "Opcode", "0");
    
    FsmMode = MODE_FSM;
    
    curvect++;
    toggleClock();
    FsmReset();
    
    curvect++;
    toggleClock();
    
    AFFECT (cvect(), "Reset", "0");
    curvect++;
    
	while(1) {
    
        toggleClock();
        
        FsmRunState();
        
        curvect++;
        toggleClock();
        
        if(FsmNextState == 1) {
            if( !getNextInstr(arq) ) {
                break;
            }
            
            AFFECT(cvect(), "Opcode", inttostr(DecOpcode));
            FsmOpcode = DecOpcode;
        }
        curvect++;
        
	}
	
	SAV_GENPAT();
	
	return 0;
}
