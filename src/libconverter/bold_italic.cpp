#include "bold_italic.h"
#include <cstring>
#include <iostream>
void bold(char *in, char *out) {
  int i = 0, j = 0, count_symbol = 0;
  char su;
  while (in[i] != '\n' && in[i] != '\0' && in[i] != EOF) {
    count_symbol = 0;
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
     count_symbol++;
      i++;
    }
    if (count_symbol == 1) {
      out[j] = '\0';
      strcat(out, "<em>");
      j += strlen("<em>");
      while (in[i] != su) {
        out[j] = in[i];
        j++;
        i++;
      }
      out[j] = '\0';
      strcat(out, "</em>");
      j += strlen("</em>");
      while (in[i] == su) {
        i++;
      }
    } else if (count_symbol == 2) {
      out[j] = '\0';
      strcat(out, "<strong>");
      j += strlen("<strong>");
      while (in[i] != su) {
        out[j] = in[i];
        j++;
        i++;
      }
      out[j] = '\0';
      strcat(out, "</strong>");
      j += strlen("</strong>");
      while (in[i] == su) {
        i++;
      }
    } else if (count_symbol == 3) {
      out[j] = '\0';
      strcat(out, "<strong><em>");
      j += strlen("<strong><em>");
      while (in[i] != su) {
        out[j] = in[i];
        j++;
        i++;
      }
      out[j] = '\0';
      strcat(out, "</em></strong>");
      j += strlen("<</em>/strong>");
      while (in[i] == su) {
        i++;
      }
    } else if (count_symbol > 3) {
      out[j] = '\0';
      strcat(out, "<strong><em>");
      j += strlen("<strong><em>");
      for (int k = 3; k < count_symbol; k++) {
        out[j] = su;
        j++;
      }
      while (in[i] != su) {
        out[j] = in[i];
        j++;
        i++;
      }
      count_symbol = 0;
      while (in[i] == su) {
        count_symbol++;
        i++;
      }
      for (int k = 3; k < count_symbol; k++) {
        out[j] = su;
        j++;
      }
      out[j] = '\0';
      strcat(out, "</em></strong>");
      j += strlen("</em></strong>");
    }
  }
  out[j] = '\0';
}
