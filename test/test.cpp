#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "libconverter/blockquote.h"
#include "libconverter/bold_italic.h"
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
  strcpy(check, "#######header7");
  CHECK(strcmp(out, check) == 0);

  strcpy(in, "#######header7#");
  Header(in, out);
  strcpy(check, "#######header7#");
  CHECK(strcmp(out, check) == 0);
  
  strcpy(in, "####header*italic*");
  Header(in, out);
  strcpy(check, "<h4>header*italic*</h4>\n");
  CHECK(strcmp(out, check) == 0);
}
TEST_CASE("Bold and Italic") {
  SECTION("check text with *") {
    char in[80];
    char out[80];
    char check[80];
    strcpy(in, "*Krivosheev*");
    bold(in, out);
    strcpy(check, "<em>Krivosheev</em>");
    CHECK(strcmp(out, check) == 0);

    strcpy(in, "**Zhurin**");
    bold(in, out);
    strcpy(check, "<strong>Zhurin</strong>");
    CHECK(strcmp(out, check) == 0);

    strcpy(in, "***Ystrebov***");
    bold(in, out);
    strcpy(check, "<strong><em>Ystrebov</em></strong>");
    CHECK(strcmp(out, check) == 0);
  }
  SECTION("check text with _") {
    char in[80];
    char out[80];
    char check[80];

    strcpy(in, "_Krivosheev_");
    bold(in, out);
    strcpy(check, "<em>Krivosheev</em>");
    CHECK(strcmp(out, check) == 0);

    strcpy(in, "__Zhurin__");
    bold(in, out);
    strcpy(check, "<strong>Zhurin</strong>");
    CHECK(strcmp(out, check) == 0);

    strcpy(in, "___Ystrebov___");
    bold(in, out);
    strcpy(check, "<strong><em>Ystrebov</em></strong>");
    CHECK(strcmp(out, check) == 0);
  }
}
TEST_CASE("Blockquote") {

  char in[200];
  char out[200];
  char check[200];

  strcpy(in, ">Zhurin");
  blockquote(in, out);
  strcpy(check, "<blockquote>\nZhurin </blockquote>\n");
  CHECK(strcmp(out, check) == 0);

  strcpy(in, ">>Krivosheev");
  blockquote(in, out);
  strcpy(
      check,
      "<blockquote>\n<blockquote>\nKrivosheev </blockquote>\n </blockquote>\n");
  CHECK(strcmp(out, check) == 0);

  strcpy(in, ">>>Ystrebov");
  blockquote(in, out);
  strcpy(check, "<blockquote>\n<blockquote>\n<blockquote>\nYstrebov "
                "</blockquote>\n </blockquote>\n </blockquote>\n");
  CHECK(strcmp(out, check) == 0);

  strcpy(in, ">");
  blockquote(in, out);
  strcpy(check, "<blockquote>\n </blockquote>\n");
  CHECK(strcmp(out, check) == 0);
}
