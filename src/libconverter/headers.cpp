#include "libconverter/headers.h"
#include <stdio.h>
#include <string.h>
int Header(char* in, char* out)
{
    int i = 0, j = 0, hash = 0;
    while (in[i] == '#') {
        hash++;
        i++;
    }
    if (hash > 6) {
        strcpy(out, in);
        return 1;
    }
    sprintf(out, "<h%d>%c", hash, in[i]);
    j = 5;
    i++;
    while (in[i] != '\0' && in[i] != '\n' && in[i] != EOF) {
        out[j] = in[i];
        i++;
        j++;
    }
    out[j] = '\0';
    char buf[10];
    sprintf(buf, "</h%d>\n", hash);
    strcat(out, buf);
    return 0;
}
