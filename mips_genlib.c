#include <genlib.h>

#define POWER "Vdd", "Vss", NULL

int main() {

	GENLIB_DEF_LOFIG("mips_genlib");
	
	GENLIB_LOCON("CLK"		, IN , "CLK");
	GENLIB_LOCON("Reset"	, IN , "Reset");
	
	GENLIB_LOCON("ReadData[31:0]"	, IN , "ReadData[31:0]");
	GENLIB_LOCON("WriteData[31:0]"	, OUT, "WriteData[31:0]");
	GENLIB_LOCON("MemAdr[31:0]"		, OUT, "MemAdr[31:0]");
	GENLIB_LOCON("State[3:0]"		, OUT, "State[3:0]");

	
	GENLIB_LOCON("Vdd" 	, IN, "Vdd");
	GENLIB_LOCON("Vss" 	, IN, "Vss");
	
	
	GENLIB_LOINS("control_genlib", "control", "CLK", "Reset", "OpCode[5:0]", "Funct[5:0]", "IorD",
				"IRWrite", "RegDst", "MemtoReg", "RegWrite", "ALUSrcA", "ALUSrcB[1:0]", 
				"ALUControl[2:0]", "ALUZero", "PCSrc[1:0]", "PCEn", "MemWrite", "State[3:0]", POWER);
	
	GENLIB_LOINS("datapath_genlib", "datapath", "nCLK", "Reset", "ReadData[31:0]", 
			"WriteData[31:0]", "MemAdr[31:0]", "OpCode[5:0]", "Funct[5:0]", "IorD",
			"IRWrite", "RegDst", "MemtoReg", "RegWrite", "ALUSrcA", "ALUSrcB[1:0]",
			"ALUControl[2:0]", "ALUZero", "PCSrc[1:0]", "PCEn", POWER);
	
	GENLIB_LOINS("nt", "notClock", "CLK", "nCLK", POWER);
	
	GENLIB_SAVE_LOFIG();
}
