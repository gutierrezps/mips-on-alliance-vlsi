#include <genlib.h>

#define POWER "Vdd", "Vss", NULL

int main() {
	int i;

	GENLIB_DEF_LOFIG("control_genlib");
	
	GENLIB_LOCON("CLK"		, IN , "CLK");
	GENLIB_LOCON("Reset"	, IN , "Reset");
	
	GENLIB_LOCON("Opcode[5:0]"		, IN , "Opcode[5:0]");
	GENLIB_LOCON("Funct[5:0]"		, IN , "Funct[5:0]");
	
	GENLIB_LOCON("IorD"		, OUT, "IorD");
	GENLIB_LOCON("IRWrite"	, OUT, "IRWrite");
	GENLIB_LOCON("RegDst"	, OUT, "RegDst");
	GENLIB_LOCON("MemtoReg"	, OUT, "MemtoReg");
	GENLIB_LOCON("RegWrite"	, OUT, "RegWrite");
	GENLIB_LOCON("ALUSrcA"	, OUT, "ALUSrcA");
	GENLIB_LOCON("ALUSrcB[1:0]"		, OUT, "ALUSrcB[1:0]");
	GENLIB_LOCON("ALUControl[2:0]"	, OUT, "ALUControl[2:0]");
	GENLIB_LOCON("ALUZero"	, IN , "ALUZero");
	GENLIB_LOCON("PCSrc[1:0]", OUT, "PCSrc[1:0]");
	GENLIB_LOCON("PCEn"		, OUT, "PCEn");
	GENLIB_LOCON("MemWrite"	, OUT, "MemWrite");
	
	GENLIB_LOCON("State[3:0]"	, OUT, "State[3:0]");

	GENLIB_LOCON("Vdd" 	, IN, "Vdd");
	GENLIB_LOCON("Vss" 	, IN, "Vss");
	
	GENLIB_LOINS("ctrl_fsm", "fsm", "CLK", "Reset", "Opcode[5:0]", "IorD", "IRWrite", 
				"RegDst", "MemtoReg", "RegWrite", "ALUSrcA", "ALUSrcB[1:0]", "ALUOp[1:0]",
				"PCSrc[1:0]", "PCWrite", "Branch", "MemWrite", "State[3:0]", POWER);
	
	GENLIB_LOINS("ctrl_aludec", "aludec", "Funct[5:0]", "ALUOp[1:0]", "ALUControl[2:0]", POWER);
	
	GENLIB_LOINS("and2", "pcen_and", "ALUZero", "Branch", "ZeroANDBranch", POWER);
	GENLIB_LOINS("or2", "pcen_or", "PCWrite", "ZeroANDBranch", "PCEn", POWER);
	
	GENLIB_SAVE_LOFIG();
}
