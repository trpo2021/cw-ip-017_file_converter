#include "libconverter/headers.h"
#include <stdio.h>
#include <string.h>
int Header(char *in, char *out) {
  int i = 0, j = 0, hash = 0;
  while (in[i] == '#') {
    hash++;
    i++;
  }
  if (hash > 6) {
    for (j = 0; j < hash; j++) {
      out[j] = '#';
    }
    while (in[i] != '\0') {
      out[j++] = in[i++];
    }
    out[j] = '\0';
    return 1;
  }
  sprintf(out, "<h%d>%c", hash, in[i]);
  j = 5;
  i++;
  while (in[i] != '\0' && in[i] != '\n' && in[i] != EOF) {
    out[j] = in[i];
    i++;
    j++;
  }
  out[j] = '\0';
  char buf[10];
  sprintf(buf, "</h%d>\n", hash);
  strcat(out, buf);
  return 0;
}
