#include "genpat.h"

int main() {
	
	DEF_GENPAT("dpt_buffer_genpat");
	
	DECLAR("a", ":2", "B", IN , "", "");
	DECLAR("y", ":2", "B", OUT, "", "");
	DECLAR("vdd", ":2", "B", IN, "", "");
	DECLAR("vss", ":2", "B", IN, "", "");
	
	AFFECT("0", "vdd", "1");
	AFFECT("0", "vss", "0");
	AFFECT("0", "a", "1");
	
	AFFECT("0", "y", "1");
	
	AFFECT("1", "a", "0");
	AFFECT("1", "y", "0");
	
	SAV_GENPAT();
	
	return 0;
}
