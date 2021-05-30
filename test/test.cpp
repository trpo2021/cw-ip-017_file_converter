#define CATCH_CONFIG_MAIN
#include "../thirdparty/catch.hpp"
#include "libconverter/blockquote.h"
#include "libconverter/bold_italic.h"
#include "libconverter/code.h"
#include "libconverter/headers.h"
#include "libconverter/hr.h"
#include "libconverter/images.h"
#include "libconverter/list.h"
#include "libconverter/strikethrough.h"
#include "libconverter/url.h"
#include <cstdio>
#include <cstring>
TEST_CASE("headers")
{
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
TEST_CASE("Bold and Italic")
{
    SECTION("check text with *")
    {
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

        strcpy(in, "***Ystrebov**");
        bold(in, out);
        strcpy(check, "***Ystrebov**");
        CHECK(strcmp(out, check) == 0);
    }
    SECTION("check text with _")
    {
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
TEST_CASE("Blockquote")
{
    char in[200];
    char out[200];
    char check[200];

    strcpy(in, ">Zhurin");
    blockquote(in, out);
    strcpy(check, "<blockquote>\nZhurin </blockquote>\n");
    CHECK(strcmp(out, check) == 0);

    strcpy(in, ">>Krivosheev");
    blockquote(in, out);
    strcpy(check,
           "<blockquote>\n<blockquote>\nKrivosheev </blockquote>\n "
           "</blockquote>\n");
    CHECK(strcmp(out, check) == 0);

    strcpy(in, ">>>Ystrebov");
    blockquote(in, out);
    strcpy(check,
           "<blockquote>\n<blockquote>\n<blockquote>\nYstrebov "
           "</blockquote>\n </blockquote>\n </blockquote>\n");
    CHECK(strcmp(out, check) == 0);

    strcpy(in, ">");
    blockquote(in, out);
    strcpy(check, "<blockquote>\n </blockquote>\n");
    CHECK(strcmp(out, check) == 0);
}
TEST_CASE("Images")
{
    char in[300];
    char out[500];
    char check[500];
    SECTION("with title")
    {
        strcpy(in, "![alt image](src/image \"image title\")");
        Image(in, out);
        strcpy(check,
               "<img src=\"src/image\" alt=\"alt image\" title=\"image "
               "title\">");
        CHECK(strcmp(out, check) == 0);

        strcpy(in, "!alt image](src/image \"image title\")");
        Image(in, out);
        strcpy(check, "!alt image](src/image \"image title\")");
        CHECK(strcmp(out, check) == 0);

        strcpy(in, "![alt image(src/image \"image title\")");
        Image(in, out);
        strcpy(check, "![alt image(src/image \"image title\")");
        CHECK(strcmp(out, check) == 0);

        strcpy(in, "![alt image]src/image \"image title\")");
        Image(in, out);
        strcpy(check, "![alt image]src/image \"image title\")");
        CHECK(strcmp(out, check) == 0);

        strcpy(in, "![alt image](src/image \"image title\"");
        Image(in, out);
        strcpy(check, "![alt image](src/image \"image title\"");
        CHECK(strcmp(out, check) == 0);

        strcpy(in, "![alt image](src/image \"image title)");
        Image(in, out);
        strcpy(check, "![alt image](src/image \"image title)");
        CHECK(strcmp(out, check) == 0);
    }
    SECTION("no title")
    {
        strcpy(in, "![alt image](src/image image title\")");
        Image(in, out);
        strcpy(check, "![alt image](src/image image title\")");
        CHECK(strcmp(out, check) == 0);

        strcpy(in, "![alt image](src/image)");
        Image(in, out);
        strcpy(check, "<img src=\"src/image\" alt=\"alt image\">");
        CHECK(strcmp(out, check) == 0);
    }
}
TEST_CASE("code")
{
    char in[80];
    char out[80];
    char check[80];

    strcpy(in, "`krivosheev`");
    code(in, out);
    strcpy(check, "<code>krivosheev</code>");
    CHECK(strcmp(out, check) == 0);

    strcpy(in, "``Zhurin``");
    code(in, out);
    strcpy(check, "<code>Zhurin</code>");
    CHECK(strcmp(out, check) == 0);

    strcpy(in, "```KZYa```");
    code(in, out);
    strcpy(check, "<code>`KZYa`</code>");
    CHECK(strcmp(out, check) == 0);

    strcpy(in, "````YastrebovS````");
    code(in, out);
    strcpy(check, "<code>``YastrebovS``</code>");
    CHECK(strcmp(out, check) == 0);
}

TEST_CASE("hr")
{
    char in[80];
    char out[80];
    char check[80];
    SECTION("*")
    {
        strcpy(in, "***");
        Hr(in, out);
        strcpy(check, "<hr>\n");
        CHECK(strcmp(out, check) == 0);

        strcpy(in, "********");
        Hr(in, out);
        strcpy(check, "<hr>\n");
        CHECK(strcmp(out, check) == 0);
    }
    SECTION("-")
    {
        strcpy(in, "---");
        Hr(in, out);
        strcpy(check, "<hr>\n");
        CHECK(strcmp(out, check) == 0);

        strcpy(in, "---------");
        Hr(in, out);
        strcpy(check, "<hr>\n");
        CHECK(strcmp(out, check) == 0);
    }
    SECTION("_")
    {
        strcpy(in, "___");
        Hr(in, out);
        strcpy(check, "<hr>\n");
        CHECK(strcmp(out, check) == 0);

        strcpy(in, "___________");
        Hr(in, out);
        strcpy(check, "<hr>\n");
        CHECK(strcmp(out, check) == 0);
    }
    SECTION("no hr")
    {
        strcpy(in, "**");
        Hr(in, out);
        strcpy(check, "**");
        CHECK(strcmp(out, check) == 0);

        strcpy(in, "a****");
        Hr(in, out);
        strcpy(check, "a****");
        CHECK(strcmp(out, check) == 0);

        strcpy(in, "**_");
        Hr(in, out);
        strcpy(check, "**_");
        CHECK(strcmp(out, check) == 0);
    }
}

TEST_CASE("URL")
{
    char in[200];
    char out[200];
    char check[200];

    strcpy(in, "[Zhurin](http://Zhurin/link.com)");
    onURL(in, out, 0);
    strcpy(check, "<a href=\"http://Zhurin/link.com\">Zhurin</a>");
    CHECK(strcmp(out, check) == 0);

    strcpy(in, "[Krivosheev](http://Krivosheev.com)");
    onURL(in, out, 0);
    strcpy(check, "<a href=\"http://Krivosheev.com\">Krivosheev</a>");
    CHECK(strcmp(out, check) == 0);

    strcpy(in, "[Zhurin(Zhurin.com)");
    onURL(in, out, 0);
    strcpy(check, "[Zhurin(Zhurin.com)");
    CHECK(strcmp(out, check) == 0);

    strcpy(in, "[Krivosheev]");
    onURL(in, out, 0);
    strcpy(check, "[Krivosheev]");
    CHECK(strcmp(out, check) == 0);

    strcpy(in, "[Ystrebov]Ystrebov.com)");
    onURL(in, out, 0);
    strcpy(check, "[Ystrebov]Ystrebov.com)");
    CHECK(strcmp(out, check) == 0);
}

TEST_CASE("LIST")
{
    char in[1000];
    char out[1000];
    char check[1000];

    strcpy(in, "1. Zhurin");
    List(in, out);
    strcpy(check, "<ol><li>1.Zhurin</li></oi>");
    CHECK(strcmp(out, check) == 0);

    strcpy(in, "2. Krivosheev");
    List(in, out);
    strcpy(check, "<ol><li>2.Krivosheev</li></oi>");
    CHECK(strcmp(out, check) == 0);

    strcpy(in, "+ Ystrebov");
    List(in, out);
    strcpy(check, "<ul><li>Ystrebov</li></ul>");
    CHECK(strcmp(out, check) == 0);

    strcpy(in, "- Zhurin");
    List(in, out);
    strcpy(check, "<ul><li>Zhurin</li></ul>");
    CHECK(strcmp(out, check) == 0);

    strcpy(in, "* Krivosheev");
    List(in, out);
    strcpy(check, "<ul><li>Krivosheev</li></ul>");
    CHECK(strcmp(out, check) == 0);
}

TEST_CASE("strlkethrough")
{
    char in[200];
    char out[200];
    char check[200];

    strcpy(in, "~Zhurin~");
    strikethrough(in, out);
    strcpy(check, "~Zhurin~");
    CHECK(strcmp(out, check) == 0);

    strcpy(in, "~~Krivosheev~~");
    strikethrough(in, out);
    strcpy(check, "<del>Krivosheev</del>");
    CHECK(strcmp(out, check) == 0);

    strcpy(in, "~~~Ystrebov~~~");
    strikethrough(in, out);
    strcpy(check, "<del>~Ystrebov~</del>");
    CHECK(strcmp(out, check) == 0);
}
