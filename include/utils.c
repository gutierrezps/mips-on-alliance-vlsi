#include <stdio.h>
#include <stdlib.h>

char *inttostr(int num) {
	char *str; 
	str = (char *) mbkalloc (32 * sizeof (char)); 
	sprintf (str, "%d", num); 
	return(str);
}

char *inttohex(int num) {
	char *str;
	str = (char *) mbkalloc (32 * sizeof (char));
	sprintf (str, "0x%x", num);
	return(str);
}

int pow(int base, int exp) {
	int i, res = 1;
	for(i = 1; i <= exp; i++) {
		res *= base;
	}
	return res;
}

