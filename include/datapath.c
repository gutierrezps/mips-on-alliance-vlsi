

char DptOpcode = 0, DptFunct = 0, DptRs = 0, DptRt = 0, DptRd = 0;

signed int DptRegFile[32] = {0}, DptRegA = 0, DptRegB = 0,
        DptInstr = 0, DptData = 0, DptALUOut = 0, DptPC = 0,
        DptReadData = 0, DptWriteData = 0, DptMemAdr = 0,
        DptALUSrcA = 0, DptALUSrcB = 0, DptALUResult = 0,
        DptALUZero = 0, DptPCNext = 0, DptImm = 0,
		DptPCJump = 0;


		
		
char ALUZero = 0;
int ALU(int A, int B, char Ctrl) {
	int Res = 0;
	
	switch(Ctrl) {
		case 0b000: Res = A & B;  break;
		case 0b001: Res = A | B;  break;
		case 0b010: Res = A + B;  break;
		case 0b100: Res = A & ~B; break;
		case 0b101: Res = A | ~B; break;
		case 0b110: Res = A - B;  break;
		case 0b111: Res = A < B;  break;
	}
	
	ALUZero = Y == 0;
	
	return Y;
}

void DptUpdateComb() {

    DptMemAdr = FsmIorD ? DptALUOut : DptPC;    // MemAdr mux
    
    DptWriteData = DptRegB;
    
    // 16-bit two's complement and sign extending
    if(DptImm > 32767) {
        DptImm = DptImm - 1;
        DptImm = ( ~DptImm ) & 0x0000FFFF;
        DptImm = -DptImm;
    }
    
    DptALUSrcA = FsmALUSrcA ? DptRegA : DptPC;	// ALU SrcA mux
    
    switch(FsmALUSrcB) {		// ALU SrcB mux
        case 0: DptALUSrcB = DptRegB; break;
        case 1: DptALUSrcB = 4; break;
        case 2: DptALUSrcB = DptImm; break;
        case 3: DptALUSrcB = (DptImm << 2) & 0x0FFFFFFFF; break;
        default: printf("Error\n");
    }
    
    DptALUResult = ALU(DptALUSrcA, DptALUSrcB, FsmALUControl);
    DptALUZero = ALUZero;
    
	//                Instr[25:0]                  PC[32:28]
    DptPCJump = ((DptInstr & 0x3FFFFFF) << 2) | (DptPC & 0xF0000000);
    
    switch(FsmPCSrc) {				// PC mux
        case 0: DptPCNext = DptALUResult; break;
        case 1: DptPCNext = DptALUOut; break;
        case 2: DptPCNext = DptPCJump; break;
        default: printf("Error\n");
    }
}


void DptUpdateSeq() {
    unsigned int data = 0;
	char addr = 0;
    
    if(FsmIRWrite) {			// Instr reg
        DptInstr = DptReadData;
		DptOpcode = ( DptInstr >> 26 ) & 0x3F;	// 6-bit mask
		DptFunct  = DptInstr & 0x3F;
		DptImm = DptInstr & 0x0FFFF;			// 16-bit mask
		DptRs = (DptInstr >> 21) & 0x1F;		// 5-bit mask
		DptRt = (DptInstr >> 16) & 0x1F;
		DptRd = (DptInstr >> 11) & 0x1F;
    }
    
    // Register File output registers
    DptRegA = DptRegFile[DptRs];
    DptRegB = DptRegFile[DptRt];
    
    if(FsmRegWrite) {
		data = FsmMemtoReg ? DptData : DptALUOut;
		addr = FsmRegDst ? DptRd : DptRt;
		DptRegFile[addr] = data;
    }
	
	DptData = DptReadData;		// Data reg
    
    DptALUOut = DptALUResult;		// ALU Out reg
    
    if(FsmPCEn) DptPC = DptPCNext;
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
