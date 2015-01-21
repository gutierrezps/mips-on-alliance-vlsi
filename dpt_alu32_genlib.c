#include <genlib.h>
#include "include/utils.c"

#define POWER "Vdd", "Vss", NULL


int main() {
	int i;

	GENLIB_DEF_LOFIG("dpt_alu_genlib");
	
	GENLIB_LOCON("A[31:0]"	, IN , "A[31:0]");
	GENLIB_LOCON("B[31:0]"	, IN , "B[31:0]");
	GENLIB_LOCON("Ctrl[2:0]", IN , "Ctrl[2:0]");
	
	GENLIB_LOCON("Res[31:0]", OUT, "Res[31:0]");
	GENLIB_LOCON("Zero"     , OUT, "Zero");
	
	GENLIB_LOCON("Vdd" 	, IN, "Vdd");
	GENLIB_LOCON("Vss" 	, IN, "Vss");

	// program counter
	GENLIB_LOINS("dpt_reg", "pcreg", "CLK", "Reset", "PCEn", "PCNext[31:0]", "pc[31:0]", POWER);
	GENLIB_LOINS("dpt_pcsl2", "pcsl2", "Instr[25:0]", "JumpSh[27:0]", POWER);
	GENLIB_LOINS("dpt_mux2" , "MemAdrMux", "pc[31:0]", "ALUOut[31:0]", "IorD", "MemAdr[31:0]", POWER);
	
	for(i = 0; i < 32; i++) {
		GENLIB_LOINS("dpt_alu1", GENLIB_NAME("alu_%d", i ), GENLIB_ELM("rfd2", i), GENLIB_ELM("WriteData", i), POWER);
	}
	
	
	GENLIB_SAVE_LOFIG();
}
