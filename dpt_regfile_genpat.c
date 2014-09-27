#include <stdio.h>
#include "genpat.h"
#include "include/utils.c"

int main () {

  int cur_vect = 0, clk = 0;
  
  DEF_GENPAT("dpt_regfile_genpat");
  
  // endereços de entrada
  DECLAR("clk", ":2", "B", IN , "", "");

  DECLAR("a3" , ":2", "X", IN , "4 down to 0" , "");
  DECLAR("wd3", ":2", "X", IN , "31 down to 0", "");
  DECLAR("we3", ":2", "B", IN , "", "");

  DECLAR("a1" , ":2", "X", IN , "4 down to 0" , "");
  DECLAR("rd1", ":2", "X", OUT, "31 down to 0", "");

  DECLAR("a2" , ":2", "X", IN , "4 down to 0" , "");
  DECLAR("rd2", ":2", "X", OUT, "31 down to 0", "");
  
  DECLAR("vdd", ":2", "B", IN , "", "" );
  DECLAR("vss", ":2", "B", IN , "", "" );
  
  LABEL ("regfile");
  
  AFFECT ("0", "vdd", "0b1");
  AFFECT ("0", "vss", "0b0");
  AFFECT ("0", "clk", inttostr(clk));
  
  //AFFECT (inttostr(cur_vect), "a", inttostr(i) );
  
  // teste do registrador $0
  AFFECT("0", "a1",  "0");
  AFFECT("0", "a2",  "0");
  AFFECT("0", "rd1", "0");
  AFFECT("0", "rd2", "0");

  AFFECT("0", "a3",  "0");
  AFFECT("0", "we3", "1");
  AFFECT("0", "wd3", "0xFFFFFFFF");
  
  cur_vect++;
  clk = !clk;

  AFFECT(inttostr(cur_vect), "clk", inttostr(clk));

  cur_vect++;
  AFFECT(inttostr(cur_vect), "clk", inttostr(clk));
  cur_vect++;

  clk = !clk;
  AFFECT(inttostr(cur_vect), "clk", inttostr(clk));

  // teste dos demais registradores
  int reg;
  
  for(reg = 1; reg < 32; reg++) {

   
    // escreve FFFFFFFF
    AFFECT(inttostr(cur_vect), "a3",  inttostr(reg));
    AFFECT(inttostr(cur_vect), "wd3", "0xFFFFFFFF");
    AFFECT(inttostr(cur_vect), "we3", "1");
    
    cur_vect++;
    clk = !clk;

    // lê FFFFFFFF em RD1 e RD2
    AFFECT(inttostr(cur_vect), "clk", inttostr(clk));

    AFFECT(inttostr(cur_vect), "a1",  inttostr(reg));
    AFFECT(inttostr(cur_vect), "a2",  inttostr(reg));
    AFFECT(inttostr(cur_vect), "rd1", "0xFFFFFFFF");  
    AFFECT(inttostr(cur_vect), "rd2", "0xFFFFFFFF");

		cur_vect++;
    AFFECT(inttostr(cur_vect), "clk", inttostr(clk));
    cur_vect++;
    clk = !clk;
    AFFECT(inttostr(cur_vect), "clk", inttostr(clk));

    // escreve 00000000
    AFFECT(inttostr(cur_vect), "a3",  inttostr(reg));
    AFFECT(inttostr(cur_vect), "wd3", "0");
    AFFECT(inttostr(cur_vect), "we3", "1");
    
    cur_vect++;
    clk = !clk;

    AFFECT (inttostr(cur_vect), "clk", inttostr(clk));

    // lê 00000000 em RD1 e RD2
    AFFECT(inttostr(cur_vect), "a1", inttostr(reg));
    AFFECT(inttostr(cur_vect), "a2", inttostr(reg));
    AFFECT(inttostr(cur_vect), "rd1", "0");
    AFFECT(inttostr(cur_vect), "rd2", "0");

		cur_vect++;
    AFFECT(inttostr(cur_vect), "clk", inttostr(clk));
    cur_vect++;
    clk = !clk;
    AFFECT(inttostr(cur_vect), "clk", inttostr(clk));
  }  
  
  SAV_GENPAT ();
  
  return 0;
}
