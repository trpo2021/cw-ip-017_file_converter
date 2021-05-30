#include "libconverter/url.h"
#include <cstring>
#include <stdio.h>
int onURL(char *in, char *out, int i)
{
    int j = 0, temp = 1, temp2;
    char all[500], link_name[200], link_url[200], common[200], common2[200];
    i++;
    common[0] = '[';
    common2[0] = '[';
    while (in[i + 1] == ']') {
        common[temp] = '[';
        common2[temp] = '[';
        i++;
        temp++;
    }

    while (in[i] != ']' && in[i] != '\n' && in[i] != EOF && i < 100) {
        link_name[j] = in[i];
        common[temp] = in[i];
        common2[temp] = in[i];
        i++;
        j++;
        temp++;
    }
    if (in[i] == ']') {
        common[temp] = in[i];
        common2[temp] = in[i];
        temp++;
    }
    link_name[j] = '\0';

    if (in[i] == '\n' || in[i] == EOF) {
        common[temp] = '\0';
        sprintf(all, "%s", common);
        strcpy(out, all);
        return 1;
    }

    while (in[i + 1] == ' ') {
        i++;
    }

    i++;
    j = i;
    temp2 = temp;
    while (in[j] != '\n' && in[j] != EOF && j < 100 && in[j] != '\0') {
        common2[temp2] = in[j];
        j++;
        temp2++;
    }

    if (in[i+1] == '(') {
        common[temp] = '(';
        i++;
        temp++;
        j = 0;
    while (in[i] != ')' && in[i] != '\n') {
        common[temp] = in[i];
        link_url[j] = in[i];
        j++;
        i++;
        temp++;
    }
    if (in[i+1] == ')'){
    	link_url[j] = '\0';
    	sprintf(all, "<a href=\"%s\">%s</a>", link_url, link_name);
    	strcpy(out, all);
    	return 0;
	}

    else if (in[i] == '\n') {
        common[temp] = '\0';
        sprintf(all, "%s", common);
        strcpy(out, all);
        return 2;
    }
    }
	else {
        common2[temp2] = '\0';
        sprintf(all, "%s", common2);
        strcpy(out, all);
        return 3;
    }
    return 4;
}

