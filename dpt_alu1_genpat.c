#include <stdio.h>
#include "genpat.h"
#include "include/utils.c"


void alu(char a, char b_in, char binv, char cin, char f) {
	char y[3];
	char b = (binv == 1)?(~b_in & 1):b_in;
	
	AFFECT(cvect(), "Op", inttostr(f));
	AFFECT(cvect(), "A", inttostr(a));
	AFFECT(cvect(), "B", inttostr(b_in));
	AFFECT(cvect(), "Binv", inttostr(binv));
	AFFECT(cvect(), "Cin", inttostr(cin));
	
	y[0] = a & b;
	y[1] = a | b;
	y[2] = a + b + cin;
	
	AFFECT(cvect(), "Res", inttostr(y[f] & 1));
	
	AFFECT(cvect(), "Set", inttostr(y[2] & 1));				// add result
	AFFECT(cvect(), "Cout", inttostr((y[2] >> 1) & 1));		// bit 1 of sum
	
	AFFECT(cvect(), "Vdd", "1");
	
	curvect++;
}

int main() {
	char a, b, cin, binv, f;
	
	DEF_GENPAT("dpt_alu_1b_genpat");

	DECLAR("A"   , ":2", "B", IN , "", "");
	DECLAR("B"   , ":2", "B", IN , "", "");
	DECLAR("Cin" , ":2", "B", IN , "", "");
	DECLAR("Binv", ":2", "B", IN , "", "");
	DECLAR("Less", ":2", "B", IN , "", "");
	DECLAR("Op"   , ":2", "B", IN ,  "1 down to 0", "");
	
	DECLAR("Res"   , ":2", "B", OUT, "", "");
	DECLAR("Cout", ":2", "B", OUT, "", "");
	DECLAR("Set", ":2", "B", OUT, "", "");
	
	DECLAR("Vdd" , ":2", "B", IN , "", "" );
	DECLAR("Vss" , ":2", "B", IN , "", "" );

	AFFECT("0", "Vdd", "1");
	AFFECT("0", "Vss", "0");
	AFFECT("0", "Less", "0");
	
	
	/******
	F | OP
	--+----
	0	AND
	1	OR
	2	ADD
	******/
	
	for(f = 0; f <= 2; f++)
		for(cin = 0; cin < 2; cin++)
			for(binv = 0; binv < 2; binv++)
				for(b = 0; b < 2; b++)
					for(a = 0; a < 2; a++)
						alu(a, b, binv, cin, f);
	
	SAV_GENPAT();
	
	return 0;
}
