#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "libconverter/headers.h"
#include <cstdio>
#include <cstring>
TEST_CASE("headers") {
  char in[80];
  char out[80];
  char check[80];
  
  strcpy(in, "#header1");
  Header(in, out);
  strcpy(check, "<h1>header1</h1>\n");
  CHECK(strcmp(out, check) == 0);
  
  strcpy(in, "##header2");
  Header(in, out);
  strcpy(check, "<h2>header2</h2>\n");
  CHECK(strcmp(out, check) == 0);
  
  strcpy(in, "###header3");
  Header(in, out);
  strcpy(check, "<h3>header3</h3>\n");
  CHECK(strcmp(out, check) == 0);

  strcpy(in, "####header4");
  Header(in, out);
  strcpy(check, "<h4>header4</h4>\n");
  CHECK(strcmp(out, check) == 0);

  strcpy(in, "#####header5");
  Header(in, out);
  strcpy(check, "<h5>header5</h5>\n");
  CHECK(strcmp(out, check) == 0);

  strcpy(in, "######header6");
  Header(in, out);
  strcpy(check, "<h6>header6</h6>\n");
  CHECK(strcmp(out, check) == 0);

  strcpy(in, "#######header7");
  Header(in, out);
  strcpy(check, "#######h");
  CHECK(strcmp(out, check) == 0);
}
