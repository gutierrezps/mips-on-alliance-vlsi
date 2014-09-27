#include <stdio.h>
#include "genpat.h"

char *inttostr(unsigned int num, char format) {
	char *str;
	str = (char *) mbkalloc (32 * sizeof (char));
	if(format == 'x')
		sprintf (str, "0x%x", num);
	else 
		sprintf (str, "%d", num);
	return(str);
}

int cur_vect = 0;

main () {
	int i;
  
	DEF_GENPAT("dpt_sl2_genpat");

	DECLAR("a", ":2", "X", IN , "31 down to 0", "");
	
	DECLAR("y", ":2", "X", OUT, "31 down to 0", "");

	DECLAR("vdd", ":2", "B", IN , "", "" );
	DECLAR("vss", ":2", "B", IN , "", "" );

	LABEL ("sl2");

	AFFECT("0", "vdd", "0b1");
	AFFECT("0", "vss", "0b0");
	
	
	for(i = 0; i < 32; i++) {
		AFFECT(inttostr(cur_vect, 'd'), "a", inttostr( 1 << i , 'x') );
		AFFECT(inttostr(cur_vect, 'd'), "y", inttostr( (1 << (i+2)) & ~3 , 'x') );
		
		cur_vect++;
		
		AFFECT(inttostr(cur_vect, 'd'), "a", inttostr( ~(1 << i) , 'x') );
		AFFECT(inttostr(cur_vect, 'd'), "y", inttostr( ~(1 << (i+2)) & ~3 , 'x') );
		
		cur_vect++;
	}
	
	SAV_GENPAT();
}
