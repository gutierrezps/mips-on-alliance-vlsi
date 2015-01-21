#include <genlib.h>
#include "include/utils.c"

#define POWER "Vdd", "Vss", NULL


int main() {
	int i;

	GENLIB_DEF_LOFIG("dpt_alu32");
	
	GENLIB_LOCON("A[31:0]"	, IN , "A[31:0]");
	GENLIB_LOCON("B[31:0]"	, IN , "B[31:0]");
	GENLIB_LOCON("Ctrl[2:0]", IN , "Ctrl[2:0]");
	
	GENLIB_LOCON("Res[31:0]", OUT, "Res[31:0]");
	GENLIB_LOCON("Zero"     , OUT, "Zero");
	
	GENLIB_LOCON("Vdd" 	, IN, "Vdd");
	GENLIB_LOCON("Vss" 	, IN, "Vss");	
	
	/*
	ALU1 pins: A, B, Cin, Less, Binv, Op, Res, Cout, Set, Vdd, Vss
	*/
	
	
	GENLIB_LOINS("dpt_alu1", "alu_0",
						"A[0]", "B[0]",
						"Ctrl[2]", "Set[31]",
						"Ctrl[2]", "Ctrl[1:0]",
						"Res_i[0]", "Cout[0]",
						"Set[0]", POWER);
	
	for(i = 1; i < 31; i++) {
		GENLIB_LOINS("dpt_alu1", GENLIB_NAME("alu_%d", i ),
						GENLIB_ELM("A", i),			// A
						GENLIB_ELM("B", i),			// B
						GENLIB_ELM("Cout", i-1),	// Cin
						"Vss",						// Less
						"Ctrl[2]",					// Binv
						"Ctrl[1:0]",				// Op
						GENLIB_ELM("Res_i", i),		// Res
						GENLIB_ELM("Cout", i),		// Cout
						GENLIB_ELM("Set", i),		// Set
						POWER);
	}
	
	GENLIB_LOINS("dpt_alu1", "alu_31",
						"A[31]", "B[31]",
						"Cout[30]", "Vss",
						"Ctrl[2]", "Ctrl[1:0]",
						"Res_i[31]", "Cout[31]",
						"Set[31]", POWER);

	GENLIB_LOINS("dpt_alu32_zero", "alu_zero", "Res_i[31:0]", "Zero", POWER);
	
	for(i = 0; i < 32; i++) {
		GENLIB_LOINS("dpt_buffer", GENLIB_NAME("res_buff_%d", i), GENLIB_ELM("Res_i", i), GENLIB_ELM("Res", i), POWER);
	}
	
	GENLIB_SAVE_LOFIG();
}
