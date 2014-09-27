#include <stdio.h>
#include "genpat.h"
#include "include/utils.c"

const int ATRASO = 1;

int cur_vect = 0, clk = 0;


void test_reg(int d, char en) {
	AFFECT(inttostr(cur_vect), "d", inttohex(d));
	AFFECT(inttostr(cur_vect), "en", inttostr(en));
	
	cur_vect += ATRASO;
	clk = !clk;
	AFFECT(inttostr(cur_vect), "clk", inttostr(clk));
	
	if( ATRASO > 1 ) {
		cur_vect += ATRASO;
		if( en ) AFFECT(inttostr(cur_vect), "q", inttohex(d));
		AFFECT(inttostr(cur_vect), "vdd", "1");
	} else {
		if( en ) AFFECT(inttostr(cur_vect), "q", inttohex(d));
		AFFECT(inttostr(cur_vect), "vdd", "1");
		cur_vect += ATRASO;
		AFFECT(inttostr(cur_vect), "clk", inttostr(clk));	
	}
	
	clk = !clk;
	cur_vect++;
	AFFECT(inttostr(cur_vect), "clk", inttostr(clk));
	
}


main () {
  
	DEF_GENPAT("dpt_reg_genpat");

	DECLAR("clk", ":2", "B", IN , "", "");
	DECLAR("en" , ":2", "B", IN , "", "");
	DECLAR("rst", ":2", "B", IN , "", "");

	DECLAR("d", ":2", "X", IN , "31 down to 0", "");
	DECLAR("q", ":2", "X", OUT, "31 down to 0", "");

	DECLAR("vdd", ":2", "B", IN , "", "" );
	DECLAR("vss", ":2", "B", IN , "", "" );

	LABEL ("reg");

	AFFECT("0", "vdd", "0b1");
	AFFECT("0", "vss", "0b0");
	
	AFFECT("0", "en" , "0b1");
	AFFECT("0", "rst", "0b0");
	AFFECT("0", "clk", inttostr(clk));
	AFFECT("0", "d", "0");


	AFFECT(inttostr(cur_vect), "rst", "1");
	clk = !clk;
	cur_vect++;
	AFFECT(inttostr(cur_vect), "clk", inttostr(clk));
	AFFECT(inttostr(cur_vect), "q", "0");
	cur_vect++;
	AFFECT(inttostr(cur_vect), "q", "0");
	
	cur_vect++;
	clk = !clk;
	AFFECT(inttostr(cur_vect), "clk", inttostr(clk));
	AFFECT(inttostr(cur_vect), "rst", "0");
	
		
//	test_reg(0x00000000, 1);
	test_reg(0xFFFFFFFF, 1);
	test_reg(0x00000000, 0);
	test_reg(0x00000000, 1);
	test_reg(0xFFFFFFFF, 0);
	test_reg(0xFFFFFFFF, 1);


	
	SAV_GENPAT();
}
