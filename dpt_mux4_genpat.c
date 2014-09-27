#include <stdio.h>
#include "genpat.h"
#include "include/utils.c"

char *mux_name(int index) {
	char *str;
	str = (char *) mbkalloc(32 * sizeof(char));
	sprintf(str, "d%d", index);
	return str;
}

int cur_vect = 0, i, j;

main () {
  
	DEF_GENPAT("dpt_mux4_genpat");

	DECLAR("d0", ":2", "X", IN , "31 down to 0", "");
	DECLAR("d1", ":2", "X", IN , "31 down to 0", "");
	DECLAR("d2", ":2", "X", IN , "31 down to 0", "");
	DECLAR("d3", ":2", "X", IN , "31 down to 0", "");
	
	DECLAR("s" , ":2", "X", IN ,  "1 down to 0", "");
	
	DECLAR("y" , ":2", "X", OUT, "31 down to 0", "");

	DECLAR("vdd", ":2", "B", IN , "", "" );
	DECLAR("vss", ":2", "B", IN , "", "" );

	LABEL ("mux4");

	AFFECT("0", "vdd", "0b1");
	AFFECT("0", "vss", "0b0");
	
	for(i = 0; i < 4; i++) {
		AFFECT(inttostr(cur_vect), "s", inttostr(i));
		
		AFFECT(inttostr(cur_vect), mux_name(i), "0");
		for(j = 0; j < 4; j++) {
			if(j != i)
				AFFECT(inttostr(cur_vect), mux_name(j), "0xFFFFFFFF");
		}
		AFFECT(inttostr(cur_vect), "y", "0");
		
		cur_vect++;
		
		AFFECT(inttostr(cur_vect), mux_name(i), "0xFFFFFFFF");
		for(j = 0; j < 4; j++) {
			if(j != i)
				AFFECT(inttostr(cur_vect), mux_name(j), "0");
		}
		AFFECT(inttostr(cur_vect), "y", "0xFFFFFFFF");
		
		cur_vect++;
	}

	
	SAV_GENPAT();
}
