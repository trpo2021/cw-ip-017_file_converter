#include "libconverter/list.h"
#include <cstring>
#include <locale.h>
#include <stdio.h>

int List(char* in, char* out)
{
    char common[250];

    int j = 0, i = 2;

	if (in[0] == '-' || in[0] == '*' || in[0] == '+') {
    	if (in[1] != ' ') {
        	strcpy(out, in);
        	return 1;
    	}
	}
	
	else if (((in[0] >= '0' && in[0] <= '9') && in[1] == '.')) {
		if (in[2] != ' ') {
        strcpy(out, in);
        return 1;
    	}
	}
	
    while (in[i] == ' ') {
        i++;
    }

    while (j < 100 && in[i] != '\n' && in[i] != EOF && in[i] != '\0') {
        common[j] = in[i];

        j++;

        i++;
    }

    common[j] = '\0';

    sprintf(out, "<li>%s</li>", common);

    return 0;
}
