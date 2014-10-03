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

#include "include/datapath.c"

int main() {
	FILE *arq = NULL;
    
    char patFilename[] = __FILE__;
    patFilename[ strlen(patFilename)-2 ] = '\0';

	arq = fopen("instructions/datapath.txt", "r+");
	
	if( !arq ) {
		fprintf(stderr, "\nCouldn't open 'instructions_datapath.txt' file.\n");
		return 1;
	}
	
	DEF_GENPAT(patFilename);
	
	DECLAR("CLK"	, ":2", "B", IN , "", "");
	DECLAR("Reset"	, ":2", "B", IN , "","");

	DECLAR("ReadData"	, ":2", "X", IN , "31 down to 0", "");
	DECLAR("WriteData"	, ":2", "X", OUT, "31 down to 0", "");
	DECLAR("MemAdr"		, ":2", "X", OUT, "31 down to 0", "");
	
	DECLAR("Opcode"		, ":2", "X", OUT, "5 down to 0", "");
	DECLAR("Funct"		, ":2", "X", OUT, "5 down to 0", "");
	
	// Multiplexer Selects
	DECLAR("IorD"		, ":2", "B", IN , "", "");
	DECLAR("IRWrite"	, ":2", "B", IN , "", "");
	DECLAR("RegDst"		, ":2", "B", IN , "", "");
	DECLAR("MemtoReg"	, ":2", "B", IN , "", "");
	DECLAR("RegWrite"	, ":2", "B", IN , "", "");	
	DECLAR("ALUSrcA"	, ":2", "B", IN , "", "");
	DECLAR("ALUSrcB"	, ":2", "B", IN , "1 down to 0", "");
	
	DECLAR("ALUControl"	, ":2", "B", IN , "2 down to 0", "");
	DECLAR("ALUZero"	, ":2", "B", OUT, "", "");

	DECLAR("PCSrc"		, ":2", "B", IN , "1 down to 0", "");
	DECLAR("PCEn"		, ":2", "B", IN , "", "");

	DECLAR ("Vdd"		, ":2", "B", IN , "", "");
	DECLAR ("Vss"		, ":2", "B", IN , "", "");

	AFFECT ("0", "Vdd", "1");
	AFFECT ("0", "Vss", "0");
	AFFECT ("0", "CLK", "0");
	AFFECT ("0", "Reset", "1");
    
    AFFECT ("0", "ReadData", "0");
    
    FsmMode = MODE_DATAPATH;
    
    FsmReset();     // reset comes first because Control pins are inputs
    
    curvect++;
    toggleClock();
    
    
    curvect++;
    toggleClock();
    
    AFFECT (cvect(), "Reset", "0");
    curvect++;
    
	while(1) {
        
        FsmRunState();
        
        DptUpdateComb();
        DptAffectAll();
        
        if(FsmCurState == 0) {
            if( !getNextInstr(arq) ) {
                break;
            }
            AFFECT(cvect(), "ReadData", inttohex(DecInstr));
            DptReadData = DecInstr;
        }
        
        curvect++;
        toggleClock();
        
        DptUpdateSeq();
        FsmOpcode = DptOpcode;
        FsmFunct = DptFunct;
        DptAffectAll();
        
        curvect++;
        toggleClock();
        
        //printf(" - ALUOut = %d\n", DptALUOut);
        //printf(" - Regfile[$s0] = %s\n", inttostr(DptRegFile[16]));
        
	}
	
	SAV_GENPAT();
	
	return 0;
}
