#include <stdio.h>
#include "genpat.h"
#include "include/utils.c"

int cur_vect = 0;

main () {
  
	DEF_GENPAT("dpt_signext_genpat");

	DECLAR("a", ":2", "X", IN , "15 down to 0", "");
	
	DECLAR("y", ":2", "X", OUT, "31 down to 0", "");

	DECLAR("vdd", ":2", "B", IN , "", "" );
	DECLAR("vss", ":2", "B", IN , "", "" );

	LABEL ("signext");

	AFFECT("0", "vdd", "0b1");
	AFFECT("0", "vss", "0b0");
	
	AFFECT(inttostr(cur_vect), "a", "0x0FFF");
	AFFECT(inttostr(cur_vect), "y", "0x00000FFF");
	
	cur_vect++;
	
	AFFECT(inttostr(cur_vect), "a", "0xF000");
	AFFECT(inttostr(cur_vect), "y", "0xFFFFF000");
	
	SAV_GENPAT();
}
