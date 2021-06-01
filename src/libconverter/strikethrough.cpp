#include "libconverter/strikethrough.h"
#include <cstring>
#include <iostream>
int strikethrough(char* in, char* out)
{
    int i = 0, j = 0, count_symbol_l = 0, count_symbol_r = 0, pos_l = 0;
    char su;
    while (in[i] != '\n' && in[i] != '\0' && in[i] != EOF) {
        count_symbol_l = 0;
        while (in[i] != '~' && in[i] != '\0' && in[i] != EOF) {
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
            count_symbol_l++;
            i++;
        }
        pos_l = i - 1;
        while (in[i] != '\0' && in[i] != EOF) {
            if (in[i] == su) {
                break;
            }
            i++;
        }
        if (in[i] != su) {
            strcpy(out, in);
            return 1;
        }
        while (in[i] == su) {
            count_symbol_r++;
            i++;
        }

        if (count_symbol_l == 2 && count_symbol_r == 2) {
            out[j] = '\0';
            strcat(out, "<del>");
            j += strlen("<del>");
            i = pos_l + 1;
            while (in[i] != su) {
                out[j] = in[i];
                j++;
                i++;
            }
            out[j] = '\0';
            strcat(out, "</del>");
            j += strlen("</del>");
        } else if (count_symbol_l > 2 && count_symbol_r > 2) {
            out[j] = '\0';
            j += strlen("<del>");
            strcat(out, "<del>");
            for (int k = 2; k < count_symbol_l; k++) {
                out[j] = su;
                j++;
            }
            i = pos_l + 1;
            while (in[i] != su) {
                out[j] = in[i];
                j++;
                i++;
            }
            for (int k = 2; k < count_symbol_r; k++) {
                out[j] = su;
                j++;
            }
            out[j] = '\0';
            j += strlen("</del>");
            strcat(out, "</del>");
        } else {
            i = 0;
            while (in[i] != '\n' && in[i] != '\0' && in[i] != EOF) {
                out[j] = in[i];
                i++;
                j++;
            }
        }
        count_symbol_r = 0;
        count_symbol_l = 0;
        break;
    }
    out[j] = '\0';
    return 0;
}
