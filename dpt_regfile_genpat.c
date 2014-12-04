#include <stdio.h>
#include "genpat.h"

#include "include/utils.c"
#include "include/regfile.c"

char CLK = 0;
void toggleClock() {
    CLK = !CLK;
    AFFECT(cvect(), "CLK", inttostr(CLK));
}

int main () {
  
    DEF_GENPAT("dpt_regfile_genpat");

    // endereços de entrada
    DECLAR("CLK", ":2", "B", IN , "", "");

    DECLAR("A3" , ":2", "X", IN , "4 down to 0" , "");
    DECLAR("WD3", ":2", "X", IN , "31 down to 0", "");
    DECLAR("WE3", ":2", "B", IN , "", "");

    DECLAR("A1" , ":2", "X", IN , "4 down to 0" , "");
    DECLAR("RD1", ":2", "X", OUT, "31 down to 0", "");

    DECLAR("A2" , ":2", "X", IN , "4 down to 0" , "");
    DECLAR("RD2", ":2", "X", OUT, "31 down to 0", "");

    DECLAR("Vdd", ":2", "B", IN , "", "" );
    DECLAR("Vss", ":2", "B", IN , "", "" );

    LABEL ("regfile");

    AFFECT(cvect(), "Vdd", "0b1");
    AFFECT(cvect(), "Vss", "0b0");
    AFFECT(cvect(), "CLK", inttostr(CLK));
  
    RegInit();
    RegAffect();
    
    RegA3 = 0;
    RegWD3 = 0xFFFFFFFF;
    RegWE3 = 1;
    RegAffect();
    
    curvect++;
    toggleClock();
    RegWrite();

    curvect++;
    toggleClock();
    
    int reg;

    for(reg = 1; reg < 32; reg++) {
        RegA1 = reg - 1;
        RegA2 = reg;
        RegA3 = reg;
        
        RegWD3 = 0x00000000;
        RegWE3 = 1;
        RegAffect();
        
        curvect++; toggleClock();
        RegWrite();
        curvect++; toggleClock();
        
        RegWD3 = 0xFFFFFFFF;
        RegWE3 = 0;
        RegAffect();
        
        curvect++; toggleClock();
        RegWrite();
        curvect++; toggleClock();
        
        RegWE3 = 1;
        RegAffect();
        
        curvect++; toggleClock();
        RegWrite();
        curvect++; toggleClock();
        
        RegWD3 = 0x00000000;
        RegWE3 = 0;
        RegAffect();
        
        curvect++; toggleClock();
        RegWrite();
        curvect++; toggleClock();
        
        RegWE3 = 1;
        RegAffect();
        
        curvect++; toggleClock();
        RegWrite();
        curvect++; toggleClock();
        
        if(reg % 2 == 1) {
            RegWD3 = 0xFFFFFFFF;
            RegWE3 = 1;
            RegAffect();
            
            curvect++; toggleClock();
            RegWrite();
            curvect++; toggleClock();
        }
        
    }  

    SAV_GENPAT ();

    return 0;
}
