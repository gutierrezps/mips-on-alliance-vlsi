#include <stdio.h>
#include "genpat.h"
#include "include/utils.c"

int clk = 0;

void test_reg(int d, char en, char rst) {
	AFFECT(cvect(), "d"  , inttohex(d));
	AFFECT(cvect(), "en" , inttostr(en));
    AFFECT(cvect(), "rst", inttostr(rst));
	
	curvect++;
	clk = !clk;
	AFFECT(cvect(), "clk", inttostr(clk));
	
    if( rst ) {
        AFFECT(cvect(), "q", "0");
    } else if( en ) {
        AFFECT(cvect(), "q", inttohex(d));
    }
    
    curvect++;
    clk = !clk;
    AFFECT(cvect(), "clk", inttostr(clk));
}


void main () {
  
	DEF_GENPAT("dpt_reg_genpat");

	DECLAR("clk", ":2", "B", IN , "", "");
	DECLAR("en" , ":2", "B", IN , "", "");
	DECLAR("rst", ":2", "B", IN , "", "");

	DECLAR("d", ":2", "X", IN , "31 down to 0", "");
	DECLAR("q", ":2", "X", OUT, "31 down to 0", "");

	DECLAR("vdd", ":2", "B", IN , "", "" );
	DECLAR("vss", ":2", "B", IN , "", "" );

	LABEL ("reg");

	AFFECT("0", "vdd", "1");
	AFFECT("0", "vss", "0");
	AFFECT("0", "clk", inttostr(clk));
    
    // reset register
	test_reg(0x00000000, 0, 1);
    
    // test EN (low, high word)
	test_reg(0xFFFFFFFF, 0, 0);
    
    // update register (high word)
	test_reg(0xFFFFFFFF, 1, 0);
    
    // test EN (low, low word)
	test_reg(0x00000000, 0, 0);
    
    // update register (low word)
    test_reg(0x00000000, 1, 0);
    
    // update register (high word)
	test_reg(0xFFFFFFFF, 1, 0);
    
    // reset register
	test_reg(0x00000000, 1, 1);

	SAV_GENPAT();
}
