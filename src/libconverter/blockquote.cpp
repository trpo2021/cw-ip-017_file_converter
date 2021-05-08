#include "libconverter/blockquote.h"
#include <cstring>
#include <iostream>
void blockquote(char *in, char *out) {
  int i = 0, j = 0, hash = 0;
  char su;
  while (in[i] != '\n' && in[i] != '\0' && in[i] != EOF) {
    hash = 0;
    while (in[i] != '>' && in[i] != '\n' && in[i] != '\0' && in[i] != EOF) {
      out[j] = in[i];
      i++;
      j++;
    }
    su = in[i];
    while (in[i] == su) {
      hash++;
      i++;
    }
    out[j] = '\0';
    for (int k = 0; k < hash; k++) {
      out[j] = '\0';
      strcat(out, "<blockquote> ");
      j += strlen("<blockquote> ");
    }
    while (in[i] != su && in[i] != '\0' && in[i] != '\n') {
      out[j] = in[i];
      j++;
      i++;
    }
    for (int k = 0; k < hash; k++) {
      out[j] = '\0';
      strcat(out, " </blockquote> ");
      j += strlen("</blockquote> ");
    }
    hash = 0;
  }
  out[j] = '\0';
}
