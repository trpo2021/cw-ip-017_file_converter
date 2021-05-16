#include "libconverter/code.h"
#include <cstring>
#include <iostream>
void code(char* in, char* out)
{
    int i = 0, j = 0, bactick = 0;
    char su;
    while (in[i] != '\n' && in[i] != '\0' && in[i] != EOF) {
        bactick = 0;
        while (in[i] != '`' && in[i] != '\n' && in[i] != '\0' && in[i] != EOF) {
            out[j] = in[i];
            i++;
            j++;
        }
        if (in[i] == '\0' || in[i] == EOF) {
            out[j] = '\0';
            break;
        }
        su = in[i];
        while (in[i] == su) {
            bactick++;
            i++;
        }
        if (bactick == 1) {
            out[j] = '\0';
            strcat(out, "<code>");
            j += strlen("<code>");
            while (in[i] != su) {
                out[j] = in[i];
                j++;
                i++;
            }
            out[j] = '\0';
            strcat(out, "</code>");
            j += strlen("</code>");
            while (in[i] == su) {
                i++;
            }
        } else if (bactick == 2) {
            out[j] = '\0';
            strcat(out, "<code>");
            j += strlen("<code>");
            while (in[i] != su) {
                out[j] = in[i];
                j++;
                i++;
            }
            out[j] = '\0';
            strcat(out, "</code>");
            j += strlen("</code>");
            while (in[i] == su) {
                i++;
            }
        } else if (bactick > 2) {
            out[j] = '\0';
            strcat(out, "<code>");
            j += strlen("<code>");
            for (int k = 2; k < bactick; k++) {
                out[j] = su;
                j++;
            }
            while (in[i] != su) {
                out[j] = in[i];
                j++;
                i++;
            }
            bactick = 0;
            while (in[i] == su) {
                bactick++;
                i++;
            }
            for (int k = 2; k < bactick; k++) {
                out[j] = su;
                j++;
            }
            out[j] = '\0';
            strcat(out, "</code>");
            j += strlen("</code>");
        }
    }
    out[j] = '\0';
}
