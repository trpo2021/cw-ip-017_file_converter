#include "libconverter/url.h"
#include <cstring>
#include <stdio.h>
int onURL(char* in, char* out)
{
    int i = 0, j = 0;
    char link_name[100], link_url[100], all[250];
    while (in[i] != '[') {
        i++;
    }
    i++;
    while (in[i] != ']' && in[i] != '\n' && in[i] != EOF && i < 99) {
        link_name[j] = in[i];
        i++;
        j++;
    }
    link_name[j] = '\0';
    i++;
    if (in[i] == '(') {
        j = 0;
        while (in[i + 1] != ')' && in[i] != '\n') {
            link_url[j] = in[i + 1];
            j++;
            i++;
        }
        link_url[j] = '\0';
    } else {
        sprintf(all, "[%s]\n", link_name);
        strcat(out, all);
        return 1;
    }
    sprintf(all, "<a href=\"%s\">%s</a>\n", link_url, link_name);
    strcat(out, all);
    return 0;
}
