#include <genlib.h>
#include "include/utils.c"

#define POWER "Vdd", "Vss", NULL


int main() {
	int i;

	GENLIB_DEF_LOFIG("datapath_genlib");
	
	GENLIB_LOCON("CLK"		, IN , "CLK");
	GENLIB_LOCON("Reset"	, IN , "Reset");
	
	GENLIB_LOCON("ReadData[31:0]"	, IN , "ReadData[31:0]");
	GENLIB_LOCON("WriteData[31:0]"	, OUT, "WriteData[31:0]");
	GENLIB_LOCON("MemAdr[31:0]"		, OUT, "MemAdr[31:0]");
	
	GENLIB_LOCON("OpCode[5:0]"		, OUT, "Instr[31:26]");
	GENLIB_LOCON("Funct[5:0]"		, OUT, "Funct[5:0]");
	
	GENLIB_LOCON("IorD"		, IN , "IorD");
	GENLIB_LOCON("IRWrite"	, IN , "IRWrite");
	GENLIB_LOCON("RegDst"	, IN , "RegDst");
	GENLIB_LOCON("MemtoReg"	, IN , "MemtoReg");
	GENLIB_LOCON("RegWrite"	, IN , "RegWrite");
	GENLIB_LOCON("ALUSrcA"	, IN , "ALUSrcA");
	GENLIB_LOCON("ALUSrcB[1:0]"		, IN , "ALUSrcB[1:0]");
	GENLIB_LOCON("ALUControl[2:0]"	, IN , "ALUControl[2:0]");
	GENLIB_LOCON("ALUZero"	, OUT, "ALUZero");
	GENLIB_LOCON("PCSrc[1:0]", IN , "PCSrc[1:0]");
	GENLIB_LOCON("PCEn"		, IN , "PCEn");
	
	GENLIB_LOCON("Vdd" 	, IN, "Vdd");
	GENLIB_LOCON("Vss" 	, IN, "Vss");
	
	// Program Counter
	GENLIB_LOINS("dpt_reg", "pcreg", "CLK", "Reset", "PCEn", "PCNext[31:0]", "pc[31:0]", POWER);
	GENLIB_LOINSE("dpt_mux4", "pcmux",
			"d0[31:0] => ALUResult[31:0]",
			"d1[31:0] => ALUOut[31:0]",
			"d2[31:28] => PC[31:28]", 
			"d2[27:0] => JumpSh[27:0]",
			"d3[31:0] => FourVect[31:0]",
			"s[1:0] => PCSrc[1:0]",
			"y[31:0] => PCNext[31:0]",
			"vdd => Vdd", "vss => Vss", NULL);
	GENLIB_LOINS("dpt_pcsl2", "pcsl2", "Instr[25:0]", "JumpSh[27:0]", POWER);
	GENLIB_LOINS("dpt_mux2" , "MemAdrMux", "pc[31:0]", "ALUOut[31:0]", "IorD", "MemAdr[31:0]", POWER);
	
	// Instr and Data registers
	GENLIB_LOINS("dpt_reg", "instrreg", "CLK", "Reset", "IRWrite", "ReadData[31:0]", "Instr[31:0]", POWER);
	GENLIB_LOINS("dpt_reg", "datareg", "CLK", "Reset", "Vdd", "ReadData[31:0]", "Data[31:0]", POWER);
	
	// Register File
	GENLIB_LOINS("dpt_mux2_5b", "rfwamux", "Instr[20:16]", "Instr[15:11]", "RegDst", "rfwa[4:0]", POWER);
	GENLIB_LOINS("dpt_mux2", "rfwdmux", "ALUOut[31:0]", "Data[31:0]", "MemtoReg", "rfwd[31:0]", POWER);
	GENLIB_LOINS("dpt_regfile", "rf", "CLK", "RegWrite", "Instr[25:21]", "Instr[20:16]", "rfwa[4:0]", "rfwd[31:0]", "rfd1[31:0]", "rfd2[31:0]", POWER);
	
	// ALU
	GENLIB_LOINS("dpt_signext", "signext", "Instr[15:0]", "signimm[31:0]", POWER);
	GENLIB_LOINS("dpt_sl2", "shift2", "signimm[31:0]", "signimmsh[31:0]", POWER);
	GENLIB_LOINS("dpt_mux2", "srcamux", "pc[31:0]", "rfd1[31:0]", "ALUSrcA", "srca[31:0]", POWER);
	GENLIB_LOINS("dpt_four", "four", "FourVect[31:0]", POWER);
	GENLIB_LOINS("dpt_mux4", "srcbmux", "rfd2[31:0]", "FourVect[31:0]", "signimm[31:0]", "signimmsh[31:0]", "ALUSrcB[1:0]", "srcb[31:0]", POWER);
	GENLIB_LOINS("dpt_alu", "alu", "srca[31:0]", "srcb[31:0]", "ALUControl[2:0]", "ALUResult[31:0]", "ALUZero", POWER);
	GENLIB_LOINS("dpt_reg", "alureg", "CLK", "Reset", "Vdd", "ALUResult[31:0]", "ALUOut[31:0]", POWER);
	
	// Output buffers
	for(i = 0; i < 6; i++) {
		GENLIB_LOINS("dpt_buffer", GENLIB_NAME("Funct_%d", i), GENLIB_ELM("instr", i), GENLIB_ELM("Funct", i), POWER);
	}
	
	for(i = 0; i < 32; i++) {
		GENLIB_LOINS("dpt_buffer", GENLIB_NAME("WriteData_%d", i), GENLIB_ELM("rfd2", i), GENLIB_ELM("WriteData", i), POWER);
	}
	
	GENLIB_SAVE_LOFIG();
	
	return 0;
}
