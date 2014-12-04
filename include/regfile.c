
int RegFile[32], RegRD1, RegRD2, RegWD3;
char RegA3, RegWE3, RegA1, RegA2, RegHasValue[32];

void RegInit() {
    char i;
    
    for(i = 0; i < 32; i++) {
        RegHasValue[i] = 0;
    }
    
    RegA1 = 0;
    RegA2 = 0;
    RegRD1 = 0;
    RegRD2 = 0;
    
    RegWD3 = 0;
    RegWE3 = 0;
    RegA3 = 0;
    
}

void RegAffect() {
    if(RegA1 < 0 || RegA1 > 32 || RegA2 < 0 || RegA2 > 32 ||
        RegA3 < 0 || RegA3 > 32)
    {
        fprintf(stderr, "Invalid address value\n");
        exit(-1);
    }

    AFFECT(cvect(), "A1",  inttostr(RegA1));
    AFFECT(cvect(), "A2",  inttostr(RegA2));
    
    if(RegA1 == 0) {
        AFFECT(cvect(), "RD1", "0");
    } else if(RegHasValue[RegA1] == 1) {
        AFFECT(cvect(), "RD1", inttohex(RegFile[RegA1]));
    } else {
        AFFECT(cvect(), "RD1", "0x********");
    }
    
    if(RegA2 == 0) {
        AFFECT(cvect(), "RD2", "0");
    } else if(RegHasValue[RegA2] == 1) {
        AFFECT(cvect(), "RD2", inttohex(RegFile[RegA2]));
    } else {
        AFFECT(cvect(), "RD2", "0x********");
    }
    
    AFFECT(cvect(),  "A3",  inttostr(RegA3));
    AFFECT(cvect(), "WD3",  inttohex(RegWD3));
    AFFECT(cvect(), "WE3",  inttostr(RegWE3));
    
}



void RegWrite() {
    if(RegA3 < 0 || RegA3 > 32) {
        fprintf(stderr, "Invalid address value\n");
        exit(-1);
    }
    
    if(RegA3 > 0 && RegWE3 == 1) {
        RegFile[RegA3] = RegWD3 & 0xFFFFFFFF;
        RegHasValue[RegA3] = 1;
    }
    
    RegAffect();
}
