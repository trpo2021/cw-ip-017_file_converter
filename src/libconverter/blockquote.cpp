#include "libconverter/blockquote.h"
#include <cstring>
#include <iostream>
void blockquote(char* in, char* out)
{
    int i = 0, j = 0, R_angel_bracets = 0;
    char su;
    while (in[i] != '\n' && in[i] != '\0' && in[i] != EOF) {
        R_angel_bracets = 0;
        while (in[i] != '>' && in[i] != '\n' && in[i] != '\0' && in[i] != EOF) {
            out[j] = in[i];
            i++;
            j++;
        }
        su = in[i];
        while (in[i] == su) {
            R_angel_bracets++;
            i++;
        }
        out[j] = '\0';
        for (int k = 0; k < R_angel_bracets; k++) {
            out[j] = '\0';
            strcat(out, "<blockquote>\n");
            j += strlen("<blockquote>\n");
        }
        while (in[i] != su && in[i] != '\0' && in[i] != '\n') {
            out[j] = in[i];
            j++;
            i++;
        }
        for (int k = 0; k < R_angel_bracets; k++) {
            out[j] = '\0';
            strcat(out, " </blockquote>\n");
            j += strlen(" </blockquote>\n");
        }
        R_angel_bracets = 0;
    }
    out[j] = '\0';
}
