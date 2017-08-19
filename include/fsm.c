

enum FsmModes {MODE_FSM = 1, MODE_CONTROL, MODE_DATAPATH} FsmModes;

char FsmOpcode = 0, FsmFunct = 0, FsmMode = 0, FsmNextState = 0, FsmCurState = 0;

char FsmPCEn = 0, FsmIorD = 0, FsmIRWrite = 0, FsmRegDst = 0, FsmMemtoReg = 0,
	 FsmRegWrite = 0, FsmALUSrcA = 0, FsmALUSrcB = 0, FsmALUOp = 0, FsmALUControl = 0,
	 FsmALUZero = 0, FsmPCSrc = 0, FsmMemWrite = 0, FsmBranch = 0, FsmPCWrite = 0;


void FsmAffectAll() {
	
	/*
	  First, we unaffect all signals that are non-Write-Enable
	*/
	
	if(FsmMode == MODE_FSM || FsmMode == MODE_CONTROL) {
	
		AFFECT(cvect(), "IorD", "0b*");
		AFFECT(cvect(), "RegDst", "0b*");
		AFFECT(cvect(), "MemtoReg", "0b*");
		AFFECT(cvect(), "ALUSrcA", "0b*");
		AFFECT(cvect(), "ALUSrcB", "0b**");
		
		if(FsmMode == MODE_FSM) {
			AFFECT(cvect(), "ALUOp", "0b**");
		} else {
			AFFECT(cvect(), "ALUControl", "0b***");
		}
		AFFECT(cvect(), "PCSrc", "0b**");
		
	} else {
	
		AFFECT(cvect(), "IorD",     inttostr(FsmIorD));
		AFFECT(cvect(), "RegDst",   inttostr(FsmRegDst));
		AFFECT(cvect(), "MemtoReg", inttostr(FsmMemtoReg));
		AFFECT(cvect(), "ALUSrcA",  inttostr(FsmALUSrcA));
		AFFECT(cvect(), "ALUSrcB",  inttostr(FsmALUSrcB));
		AFFECT(cvect(), "ALUControl", inttostr(FsmALUControl));
		AFFECT(cvect(), "PCSrc",    inttostr(FsmPCSrc));
	}
	
	/*
	  This switch below updates signals for mux and
	  ALU that are relevant for each state. Other signals are "don't care"
	  
	  I.e.: states 1, 2, 6, 9 and 11 change ALU signals;
			states 4, 7 and 10 change RegDst and MemtoReg signals;
			and so on.
	*/
	
	switch(FsmCurState) {
		case 0:
			AFFECT(cvect(), "IorD"	    , inttostr(FsmIorD));
		
		case 8:
			AFFECT(cvect(), "PCSrc"	    , inttostr(FsmPCSrc));
			
		case 1:
		case 2:
		case 6:
		case 9:
		case 11:
			AFFECT(cvect(), "ALUSrcA"   , inttostr(FsmALUSrcA));
			AFFECT(cvect(), "ALUSrcB"   , inttostr(FsmALUSrcB));
			
			if(FsmMode == MODE_FSM) {
				AFFECT(cvect(), "ALUOp"     , inttostr(FsmALUOp));
			} else {
				FsmALUControl = ALUDec(FsmALUOp, FsmFunct);
				AFFECT(cvect(), "ALUControl", inttostr( FsmALUControl ) );
			}
			
			break;
			
		case 3:
		case 5:
			AFFECT(cvect(), "IorD"	    , inttostr(FsmIorD));
			break;
		
		case 4:
		case 7:
		case 10:
			AFFECT(cvect(), "RegDst"    , inttostr(FsmRegDst));
			AFFECT(cvect(), "MemtoReg"  , inttostr(FsmMemtoReg));
			break;
			
	}
	
	
	/*
	  This switch below updates Write-Enable signals.
	*/
	
	switch(FsmMode) {
		case MODE_FSM:
			AFFECT(cvect(), "Branch"    , inttostr(FsmBranch));
			AFFECT(cvect(), "PCWrite"   , inttostr(FsmPCWrite));
			AFFECT(cvect(), "State"     , inttostr(FsmCurState));
			break;
			
		case MODE_CONTROL:
			AFFECT(cvect(), "ALUZero"   , inttostr(FsmALUZero));
			AFFECT(cvect(), "State"     , inttostr(FsmCurState));
			
		case MODE_DATAPATH:
			AFFECT(cvect(), "PCEn"      , inttostr(FsmPCEn));
			break;
	}
	
	AFFECT(cvect(), "IRWrite"   , inttostr(FsmIRWrite));
	AFFECT(cvect(), "RegWrite"   , inttostr(FsmRegWrite));
	
	if(FsmMode != MODE_DATAPATH) {
		AFFECT(cvect(), "MemWrite"   , inttostr(FsmMemWrite));
	}
}

void FsmReset() {
	FsmNextState = 0;
	FsmCurState = 15;
	state0();
	
	LABEL("FSM_Reset");
	
	FsmIRWrite = 0;
	FsmPCWrite = 0;
	FsmPCEn = 0;
	
	
	FsmAffectAll();
}

void FsmRunState() {
	FsmCurState = FsmNextState;
	
	if( FsmMode != MODE_FSM && FsmMode != MODE_CONTROL && FsmMode != MODE_DATAPATH ) {
		fprintf(stderr, "FSM error: invalid mode (%d)\n", FsmMode);
		exit(1);
	}
	
	switch(FsmCurState) {
		case  0:  state0(); break;
		case  1:  state1(); break;
		case  2:  state2(); break;
		case  3:  state3(); break;
		case  4:  state4(); break;
		case  5:  state5(); break;
		case  6:  state6(); break;
		case  7:  state7(); break;
		case  8:  state8(); break;
		case  9:  state9(); break;
		case 10: state10(); break;
		case 11: state11(); break;
		default:
			fprintf(stderr, "FSM error: invalid state (%d)\n", FsmCurState);
			exit(1);
	}
	
	FsmAffectAll();
}

void state0() {

	LABEL("Fsm_Fetch");

	FsmIorD    = 0;
	FsmALUSrcA = 0;
	FsmALUSrcB = 1;
	FsmPCSrc   = 0;
	FsmIRWrite = 1;
	FsmRegWrite = 0;
	FsmMemWrite = 0;
	FsmALUZero = 0;
	FsmALUOp   = 0;
	FsmBranch  = 0;
	FsmPCWrite = 1;
	FsmPCEn  = 1;
	
	FsmNextState = 1;
}

void state1() {

	LABEL("Fsm_Decode");
	
	FsmALUSrcA  = 0;
	FsmALUSrcB  = 3;
	FsmIRWrite  = 0;
	FsmPCWrite  = 0;
	FsmPCEn     = 0;
	
	// ALUOp / ALUControl already set to ADD by state0
	
	switch(FsmOpcode) {
		
		// LW or SW
		case 35:
		case 43: FsmNextState = 2;  break;
		
		// R-type
		case 0: FsmNextState = 6;  break;

		// BEQ
		case 4: FsmNextState = 8;  break;
		
		// ADDI
		case 8: FsmNextState = 9;  break;
		
		// Jump
		case 2: FsmNextState = 11; break;
		
		default:
			fprintf(stderr, "FSM Error: Opcode unknown / not implemented\n");
			exit(1);
	}
}

void state2() {
	
	LABEL("Fsm_Mem_Adr");
	
	FsmALUSrcA = 1;
	FsmALUSrcB = 2;
	
	// ALUOp / ALUControl already set to ADD by state0

	if(FsmOpcode == 35) FsmNextState = 3;      // LW
	else FsmNextState = 5;     // SW

}

void state3() {

	LABEL("Fsm_Mem_Read");
	
	FsmIorD = 1;
	
	FsmNextState = 4;
	
}

void state4() {

	LABEL("Fsm_Mem_Writeback");
	
	FsmRegDst   = 0;
	FsmMemtoReg = 1;
	FsmRegWrite = 1;
	
	FsmNextState = 0;
}

void state5() {
	
	LABEL("Fsm_Mem_Write");
	
	FsmIorD     = 1;
	FsmMemWrite = 1;
	
	FsmNextState = 0;
	
}

void state6() {

	LABEL("Fsm_Execute");
	
	FsmALUSrcA  = 1;
	FsmALUSrcB  = 0;
	FsmALUOp    = 2;
	
	FsmNextState = 7;

}

void state7() {

	LABEL("Fsm_ALU_Writeback");
	
	FsmRegDst   = 1;
	FsmMemtoReg = 0;
	FsmRegWrite = 1;
	
	FsmNextState = 0;
}

void state8() {

	LABEL("Fsm_Branch");
	
	FsmALUSrcA = 1;
	FsmALUSrcB = 0;
	FsmALUOp   = 1;    // subtracts to check zero flag
	
	FsmBranch  = 1;    // authorizes Branch
	
	// on MODE_CONTROL, always assumes ALUZero = 1 and authorizes write on PC
	FsmALUZero = 1;
	FsmPCEn    = 1;
	FsmPCSrc   = 1;
	
	FsmNextState = 0;
}

void state9() {

	LABEL("Fsm_ADDI_Execute");
	
	FsmALUSrcA = 1;
	FsmALUSrcB = 2;
	
	FsmNextState = 10;
}

void state10() {

	LABEL("Fsm_ADDI_Writeback");
	
	FsmRegDst   = 0;
	FsmMemtoReg = 0;
	FsmRegWrite = 1;
	
	FsmNextState = 0;
}

void state11() {

	LABEL("Fsm_Jump");
	
	FsmPCSrc    = 2;
	FsmPCEn     = 1;
	FsmPCWrite  = 1;

	FsmNextState = 0;

}

