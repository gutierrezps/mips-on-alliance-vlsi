

char DecOpcode, DecFunct, DecRd, DecRt, DecRs, DecImm;

int DecInstr;

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
        chOpcode[i] = chInstr[i];
        chFunct[i]  = chInstr[26 + i];
        
        DecOpcode = (DecOpcode << 1) | ( chOpcode[i] - '0' );
        DecFunct  = (DecFunct  << 1) | ( chFunct[i]  - '0' );
    }
    
    chOpcode[6] = '\0';
    chFunct[6]  = '\0';
    
    DecLine++;
    
    return 1;
    
}