

char DptOpcode = 0, DptFunct = 0;

signed int DptRegFile[32] = {0}, DptRegA = 0, DptRegB = 0,
        DptInstr = 0, DptData = 0, DptALUOut = 0, DptPC = 0,
        DptReadData = 0, DptWriteData = 0, DptMemAdr = 0,
        DptALUSrcA = 0, DptALUSrcB = 0, DptALUResult = 0,
        DptALUZero = 0, DptPCNext = 0;

signed int DptImm = 0;

signed int alu(signed int a, signed int b, char ctrl) {
	signed int res = 0;
	
	switch(ctrl) {
		case 0b000: res = a & b; break;
		case 0b001: res = a | b; break;
		case 0b010: res = a + b; break;
		case 0b110: res = a - b; break;
		case 0b111: res = (a < b); break;
	}
    
    return res;
}

void DptUpdateComb() {

    // MemAdr mux
    if(FsmIorD == 0) {
        DptMemAdr = DptPC;
    } else {
        DptMemAdr = DptALUOut;
    }
    
    DptWriteData = DptRegB;
    
    
    // Immediate
    DptImm = DptInstr & 0x0000FFFF;
    
    if(DptImm > 32767) {
        DptImm = DptImm - 1;
        DptImm = ( ~DptImm ) & 0x0000FFFF;
        DptImm = -DptImm;
    }
    
    // ALU SrcA mux
    if(FsmALUSrcA == 0) {
        DptALUSrcA = DptPC;
    } else {
        DptALUSrcA = DptRegA;
    }
    
    // ALU SrcB mux
    switch(FsmALUSrcB) {
        case 0: DptALUSrcB = DptRegB; break;
        case 1: DptALUSrcB = 4; break;
        case 2: DptALUSrcB = DptImm; break;
        case 3: DptALUSrcB = DptImm << 2; break;
    }
    
    // ALU Result
    DptALUResult = alu(DptALUSrcA, DptALUSrcB, FsmALUControl);
    
    if(DptALUResult == 0) {
        DptALUZero = 1;
    } else {
        DptALUZero = 0;
    }
    
    
    // PC Next
    switch(FsmPCSrc) {
        case 0: DptPCNext = DptALUResult; break;
        case 1: DptPCNext = DptALUOut; break;
        //case 2: DptPCNext = DptPCJump; break;
    }
    
}


void DptUpdateSeq() {
    unsigned int data = 0;
    
    // Instr reg
    if(FsmIRWrite == 1) {
        DptInstr = DptReadData;
        
        DptOpcode = ( DptInstr >> 26 ) & 0b0111111;
        DptFunct  = DptInstr & 0b0111111;
    }
    
    // Data reg
    DptData = DptReadData;
    
    
    // Register File
    DptRegA = DptRegFile[DecRs];
    DptRegB = DptRegFile[DecRt];
    
    if(FsmRegWrite == 1) {
        if(FsmMemtoReg == 0) {
            data = DptALUOut;
        } else {
            data = DptData;
        }
        
        if(FsmRegDst == 0) {
            DptRegFile[DecRt] = data;
        } else {
            DptRegFile[DecRd] = data;
        }
    }
    
    // ALU Out reg
    DptALUOut = DptALUResult;
    
    if(FsmPCEn == 1) {
        DptPC = DptPCNext;
    }
}

void DptAffectAll() {

    AFFECT(cvect(), "MemAdr",    "0x********");
    AFFECT(cvect(), "WriteData", "0x********");
    AFFECT(cvect(), "ALUZero",   "0b*");
    
    AFFECT(cvect(), "Opcode",  inttostr(DptOpcode));
    AFFECT(cvect(), "Funct",   inttostr(DptFunct));
    
    
    switch(FsmCurState) {
    
        case 5:
            AFFECT(cvect(), "WriteData", inttohex(DptWriteData));
            
        case 3:
            AFFECT(cvect(), "MemAdr",    inttohex(DptMemAdr));
            break;
            
        case 8:
            AFFECT(cvect(), "ALUZero", inttostr(DptALUZero));
            break;
        default: ;
    }
}
