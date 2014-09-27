

char ALUDec(char ALUOp, char Funct) {
	
	char ALUControl = 1;
	
	if(ALUOp == 0) {
		ALUControl = 0b010;     // add
		
	} else if( ALUOp == 1) {
		ALUControl = 0b110;     // sub
		
	} else if( ALUOp == 2) {
		switch(Funct) {
			case 0b100000: ALUControl = 0b010; break;       // add
			case 0b100010: ALUControl = 0b110; break;       // sub
			case 0b100100: ALUControl = 0b000; break;       // and
			case 0b100101: ALUControl = 0b001; break;       // or
			case 0b101010: ALUControl = 0b111; break;       // set on less than
            default:
                fprintf(stderr, "ALUDec error: unknown Funct code / not implemented (%d)\n", Funct);
                exit(1);
		}
	} else {
        fprintf(stderr, "ALUDec error: invalid ALUOp (%d)\n", ALUOp);
        exit(1);
    }
    
    return ALUControl;
}