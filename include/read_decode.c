

char DecOpcode, DecFunct, DecRs, DecRt, DecRd;

unsigned int DecInstr;
signed int DecImm;

char chOpcode[7], chFunct[7], chBuffer[9], chInstr[100], DecLine = 1;

char getNextInstr(FILE *fInstr) {
    int i;

    fgets( chInstr, 100, fInstr );
    chInstr[32] = '\0';
    
    if( feof(fInstr) ) return 0;
    
    if( strlen(chInstr) != 32 ) {
        fprintf(stderr, "Dec Error on line %d: Instr size mismatch (%d)\n", DecLine, strlen(chInstr));
        exit(1);
    }
	
    DecInstr = 0;
    
    for(i = 0; i < 32; i++) {
        if( chInstr[i] != '0' && chInstr[i] != '1' ) {
            fprintf(stderr, "Dec Error on line %d, col %d: invalid character '%c'\n", DecLine, i+1, chInstr[i]);
            exit(1);
        }
        
        DecInstr = (DecInstr << 1) | ( chInstr[i] - '0' );
    }
    
    DecOpcode = 0;
    DecFunct = 0;
    
    for(i = 0; i < 6; i++) {
        chOpcode[i] = chInstr[i];           // opcode = instr[0:5] (inverted order)
        chFunct[i]  = chInstr[26 + i];      // funct  = instr[26:31]
        
        DecOpcode = (DecOpcode << 1) | ( chOpcode[i] - '0' );
        DecFunct  = (DecFunct  << 1) | ( chFunct[i]  - '0' );
    }

    chOpcode[6] = '\0';
    chFunct[6]  = '\0';
    
    DecRs = 0;
    DecRt = 0;
    DecRd = 0;
    for(i = 0; i < 5; i++) {
        DecRs = (DecRs << 1) | ( chInstr[i + 6] - '0' );        // rs = instr[6:10]
        DecRt = (DecRt << 1) | ( chInstr[i + 11] - '0' );       // rt = instr[11:15]
        DecRd = (DecRd << 1) | ( chInstr[i + 16] - '0' );       // rd = instr[16:20]
    }
    
    DecImm = 0;
    for(i = 0; i < 16; i++) {
        DecImm = (DecImm << 1) | ( chInstr[i + 16] - '0' );     // imm = instr[16:31]
    }
    
    if(DecImm > 32767) {
        DecImm = DecImm - 1;
        DecImm = ( ~DecImm ) & 0x0000FFFF;
        DecImm = -DecImm;
    }

    DecLine++;
    
    return 1;
    
}