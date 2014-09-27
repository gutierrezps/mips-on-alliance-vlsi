
int RegFile[32], RegD1, RegD2;
char RegWE3, RegA1, RegA2, RegInit[32];

void RegInit() {
    char i;
    
    for(i = 0; i < 32; i++) {
        RegInit[i] = 0;
    }
}

void UpdateStatus() {
    
}

void RegWrite(char A3, int WD3) {
    
}
