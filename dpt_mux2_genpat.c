#include <stdio.h>
#include "genpat.h"
#include "include/utils.c"

int cur_vect = 0;

main () {
  
	DEF_GENPAT("dpt_mux2_genpat");

	DECLAR("d0", ":2", "X", IN , "31 down to 0", "");
	DECLAR("d1", ":2", "X", IN , "31 down to 0", "");

	DECLAR("s" , ":2", "B", IN ,  "", "");
	
	DECLAR("y" , ":2", "X", OUT, "31 down to 0", "");

	DECLAR("vdd", ":2", "B", IN , "", "" );
	DECLAR("vss", ":2", "B", IN , "", "" );

	LABEL ("mux2");

	AFFECT("0", "vdd", "0b1");
	AFFECT("0", "vss", "0b0");
	
	AFFECT(inttostr(cur_vect), "d0", "0");
	AFFECT(inttostr(cur_vect), "d1", "0xFFFFFFFF");
	AFFECT(inttostr(cur_vect), "s" , "0");
	AFFECT(inttostr(cur_vect), "y" , "0");
	
	cur_vect++;
	AFFECT(inttostr(cur_vect), "d0", "0xFFFFFFFF");
	AFFECT(inttostr(cur_vect), "d1", "0");
	AFFECT(inttostr(cur_vect), "y" , "0xFFFFFFFF");
	
	cur_vect++;
	
	AFFECT(inttostr(cur_vect), "s" , "1");
	AFFECT(inttostr(cur_vect), "y" , "0");
	
	cur_vect++;
	AFFECT(inttostr(cur_vect), "d0", "0");
	AFFECT(inttostr(cur_vect), "d1", "0xFFFFFFFF");
	AFFECT(inttostr(cur_vect), "y" , "0xFFFFFFFF");

	SAV_GENPAT();
}
