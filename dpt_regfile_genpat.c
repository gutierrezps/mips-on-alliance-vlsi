#include <stdio.h>
#include "genpat.h"
#include "include/utils.c"

int curvect = 0;
char CLK = 0;

char * cvect() { return inttostr(curvect); }

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
  
  AFFECT (cvect(), "Vdd", "0b1");
  AFFECT (cvect(), "Vss", "0b0");
  AFFECT (cvect(), "CLK", inttostr(CLK));
  AFFECT(cvect(), "A1",  "0");
  AFFECT(cvect(), "A2",  "0");
  AFFECT(cvect(), "A3",  "0");
  AFFECT(cvect(), "WD3",  "0");
  AFFECT(cvect(), "WE3",  "0");
  
  curvect++;
  toggleClock();
  
  AFFECT(cvect(), "RD1", "0");
  AFFECT(cvect(), "RD2", "0");
  
  curvect++;
  toggleClock();

  AFFECT(cvect(), "A3",  "0");
  AFFECT(cvect(), "WE3", "1");
  AFFECT(cvect(), "WD3", "0xFFFFFFFF");
  
  // write on rising edge
  curvect++;
  toggleClock();
  curvect++;
  toggleClock();
  
  // reads on rising edge
  curvect++;
  toggleClock();
  curvect++;
  toggleClock();
  

  // teste dos demais registradores
  int reg;
  
  for(reg = 1; reg < 32; reg++) {

    AFFECT(cvect(), "A3",  inttostr(reg));
    AFFECT(cvect(), "WD3", "0xFFFFFFFF");
    AFFECT(cvect(), "WE3", "1");
    
    curvect++;
    toggleClock();
    curvect++;
    toggleClock();
    
    AFFECT(cvect(), "A1",  inttostr(reg));
    AFFECT(cvect(), "A2",  inttostr(reg));
    
    curvect++;
    toggleClock();
    
    AFFECT(cvect(), "RD1", "0xFFFFFFFF"); 
    AFFECT(cvect(), "RD2", "0xFFFFFFFF");
    
    curvect++;
    toggleClock();
    
    AFFECT(cvect(), "A3",  inttostr(reg));
    AFFECT(cvect(), "WD3", "0");
    AFFECT(cvect(), "WE3", "1");
    
    curvect++;
    toggleClock();
    curvect++;
    toggleClock();
    

    AFFECT(cvect(), "A1", inttostr(reg));
    AFFECT(cvect(), "A2", inttostr(reg));
    
    curvect++;
    toggleClock();
    
    AFFECT(cvect(), "RD1", "0");
    AFFECT(cvect(), "RD2", "0");
    
    curvect++;
    toggleClock();
    
  }  
  
  SAV_GENPAT ();
  
  return 0;
}
