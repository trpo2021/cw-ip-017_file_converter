#include "libconverter/url.h"
#include <cstring>
#include <stdio.h>
int onURL(char* in, char* out)
{
    char link_name[400], link_url[400], buf[900];

    int i = 0, j = 0;

    while (in[i] != '[') {
        out[j] = in[i];

        i++;

        j++;
    }

    out[j] = '\0';

    int z = 0;

    while (in[i] == '[') {
        i++;
    }

    while (in[i] != ']' && in[i] != '\n' && in[i] != EOF && i < 399) {
        link_name[z] = in[i];

        i++;

        z++;
    }

    link_name[z] = '\0';

    if (in[i] == '\n' || in[i] == EOF) {
        strcpy(out, in);
    }

    i++;

    while (in[i] == ' ') {
        i++;
    }

    if (in[i] == '(') {
        i++;

        z = 0;

        while (in[i] != ')' && in[i] != '\n' && in[i] != EOF && i < 399) {
            link_url[z] = in[i];

            z++;

            i++;
        }

        if (in[i] != ')') {
            strcpy(out, in);

        }

        else if (in[i] == ')') {
            link_url[z] = '\0';

            sprintf(buf, "<a href=\"%s\">%s</a>", link_url, link_name);

            strcat(out, buf);

            j += strlen(buf);

            i++;

            while (in[i] != '\n' && in[i] != EOF && in[i] != '\0') {
                out[j] = in[i];

                j++;

                i++;
            }

            out[j] = '\0';
        }
    }

    else
        strcpy(out, in);

    return 0;
}
