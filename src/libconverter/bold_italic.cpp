#include "bold_italic.h"
#include <cstring>
#include <iostream>
int bold(char* in, char* out)
{
    int i = 0, j = 0, count_symbol_l = 0, count_symbol_r = 0, pos_l = 0;
    char su;
    while (in[i] != '\n' && in[i] != '\0' && in[i] != EOF) {
        count_symbol_l = 0;
        while (in[i] != '*' && in[i] != '\0' && in[i] != EOF && in[i] != '_') {
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

        if (count_symbol_l == 1 && count_symbol_r == 1) {
            out[j] = '\0';
            strcat(out, "<em>");
            j += strlen("<em>");
            i = pos_l + 1;
            while (in[i] != su) {
                out[j] = in[i];
                j++;
                i++;
            }
            out[j] = '\0';
            strcat(out, "</em>");
            j += strlen("</em>");
        } else if (count_symbol_l == 2 && count_symbol_r == 2) {
            out[j] = '\0';
            strcat(out, "<strong>");
            j += strlen("<strong>");
            i = pos_l + 1;
            while (in[i] != su) {
                out[j] = in[i];
                j++;
                i++;
            }
            out[j] = '\0';
            strcat(out, "</strong>");
            j += strlen("</strong>");
        } else if (count_symbol_l == 3 && count_symbol_r == 3) {
            out[j] = '\0';
            strcat(out, "<strong><em>");
            j += strlen("<strong><em>");
            i = pos_l + 1;
            while (in[i] != su) {
                out[j] = in[i];
                j++;
                i++;
            }
            out[j] = '\0';
            strcat(out, "</em></strong>");
            j += strlen("</em></strong>");
        } else if (count_symbol_l > 3 && count_symbol_r > 3) {
            out[j] = '\0';
            j += strlen("<strong><em>");
            strcat(out, "<strong><em>");
            for (int k = 3; k < count_symbol_l; k++) {
                out[j] = su;
                j++;
            }
            i = pos_l + 1;
            while (in[i] != su) {
                out[j] = in[i];
                j++;
                i++;
            }
            for (int k = 3; k < count_symbol_r; k++) {
                out[j] = su;
                j++;
            }
            out[j] = '\0';
            j += strlen("</em></strong>");
            strcat(out, "</em></strong>");
        } else {
            i = 0;
            while (in[i] != '\n' && in[i] != '\0' && in[i] != EOF) {
                out[j] = in[i];
                i++;
                j++;
            }
        }
        i += count_symbol_r;
        count_symbol_r = 0;
        count_symbol_l = 0;
    }
    out[j] = '\0';
    return 0;
}
