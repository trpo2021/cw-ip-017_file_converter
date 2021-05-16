#include "libconverter/images.h"
#include <cstdio>
#include <cstring>
int Image(char* in, char* out)
{
    int i = 0, j = 0, left_sqbr, right_sqbr, left_br, right_br;
    char src[200], alt[200], title[200], buf[700];
    while (in[i] != '!') {
        out[j] = in[i];
        i++, j++;
    }
    out[j] = '\0';
    i++;
    if (in[i] != '[') {
        strcpy(out, in);
        return 1;
    }
    left_sqbr = i;
    while (in[i] != '\0' && in[i] != EOF) {
        if (in[i] == ']') {
            right_sqbr = i;
            break;
        }
        i++;
    }
    if (in[i] != ']') {
        strcpy(out, in);
        return 1;
    }
    int k = 0;
    for (i = left_sqbr + 1; i < right_sqbr; i++) {
        alt[k] = in[i];
        k++;
    }
    alt[k] = '\0';
    i = right_sqbr + 1;
    if (in[i] != '(') {
        strcpy(out, in);
        return 2;
    }
    left_br = i;
    while (in[i] != '\0' && in[i] != EOF) {
        if (in[i] == ')') {
            right_br = i;
            break;
        }
        i++;
    }
    if (in[i] != ')') {
        strcpy(out, in);
        return 2;
    }
    k = 0;
    i = left_br + 1;
    bool have_title = false;
    while (i < right_br) {
        if (in[i] == '\"') {
            have_title = true;
            break;
        } else if (in[i] != ' ') {
            src[k] = in[i];
            k++;
        }
        i++;
    }
    src[k] = '\0';
    if (have_title) {
        int left_quote = i, right_quote;
        i++;
        while (i < right_br) {
            if (in[i] == '\"') {
                right_quote = i;
                break;
            }
            i++;
        }
        if (in[i] == ')') {
            strcpy(out, in);
            return 3;
        }
        k = 0;
        for (i = left_quote + 1; i < right_quote; i++) {
            title[k] = in[i];
            k++;
        }
        title[k] = '\0';
        sprintf(buf,
                "<img src=\"%s\" alt=\"%s\" title=\"%s\">",
                src,
                alt,
                title);
    } else {
        sprintf(buf, "<img src=\"%s\" alt=\"%s\">", src, alt);
    }
    strcat(out, buf);
    j += strlen(buf);
    i = right_br + 1;
    while (in[i] != '\0') {
        out[j] = in[i];
        j++, i++;
    }
    out[j] = '\0';
    return 0;
}
