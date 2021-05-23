#include "hr.h"
#include <stdio.h>
#include <string.h>
void Hr(char* in, char* out)
{
    int i = 0, sign_count = 0;
    char sign = in[0];
    while (in[i] == sign) {
        sign_count++;
        i++;
    }
    if (sign_count >= 3 && (in[i] == '\0' || in[i] == '\n' || in[i] == EOF)) {
        strcpy(out, "<hr>\n");
    } else {
        strcpy(out, in);
    }
}
