%{
#include <string>
#include <cstdlib>
#include <cerrno>
#include <climits>
#include <cfloat>
#include "Token.h"

#define yyterminate() 
//character   [ !"#$%&()*+,\-./0-9:;<=>\?@A-Z\[\]\^_`a-z{|}~]
%}

%option noyywrap

id          [a-zA-Z_][a-zA-Z_0-9]*
decimal     0|([1-9][0-9]*)
hex         0[xX][0-9a-fA-F]+
octal       0[0-7]+
float       [0-9]*"."[0-9]+([eE][+-]?[0-9]+)?
blank       [ \t]

unsigned    [uU]
long        [lL]
ulong       ({unsigned}{long}?)|({long}(unsigned))
llong       {long}{long}
ullong      ({unsigned}{llong})|({llong}{unsigned})

character   [^\n]


%x C_COMMENT
%x CPP_COMMENT
%x STRING

%%
%{
    typedef Token::Type token;
    std::string string_buffer;
%}
<INITIAL>{
    \0              return;
    \n              {list->LineBreak();}
    "//"            {BEGIN(CPP_COMMENT);}
    "/*"            {BEGIN(C_COMMENT);}

    "auto"          { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_AUTO, str); }
    "break"         { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_BREAK, str); }
    "case"          { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_CASE, str); }
    "char"          { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_CHAR, str); }
    "const"         { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_CONST, str); }
    "continue"      { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_CONTINUE, str); }
    "default"       { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_DEFAULT, str); }
    "do"            { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_DO, str); }
    "double"        { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_DOUBLE, str); }
    "else"          { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_ELSE, str); }
    "enum"          { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_ENUM, str); }
    "extern"        { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_EXTERN, str); }
    "float"         { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_FLOAT, str); }
    "for"           { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_FOR, str); }
    "goto"          { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_GOTO, str); }
    "if"            { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_IF, str); }
    "int"           { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_INT, str); }
    "long"          { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_LONG, str); }
    "register"      { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_REGISTER, str); }
    "return"        { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_RETURN, str); }
    "signed"        { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_SIGNED, str); }
    "sizeof"        { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_SIZEOF, str); }
    "short"         { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_SHORT, str); }
    "static"        { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_STATIC, str); }
    "struct"        { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_STRUCT, str); }
    "switch"        { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_SWITCH, str); }
    "typedef"       { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_TYPEDEF, str); }
    "union"         { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_UNION, str); }
    "unsigned"      { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_UNSIGNED, str); }
    "void"          { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_VOID, str); }
    "volatile"      { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_VOLATILE, str); }
    "while"         { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_WHILE, str); }
        
    "true"          { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_TRUE, str); }
    "false"         { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_FALSE, str); }
    "bool"          { std::string* str = new std::string(yytext); list->AddKEYWORD(token::TK_BOOL, str); }

    \\\n            {list->LineBreak(); }

    [!#%&()*+,\-./:;<=>?\[\]\^{|}~]     {list->AddToken((token)yytext[0]);}
    
    "&&"            { list->AddToken(token::TK_LOGAND); }
    "||"            { list->AddToken(token::TK_LOGOR); }
    "=="            { list->AddToken(token::TK_EQ); }
    "!="            { list->AddToken(token::TK_NE); }
    ">="            { list->AddToken(token::TK_GE); }
    "<="            { list->AddToken(token::TK_LE); }
    "<<"            { list->AddToken(token::TK_LSHIFT); }
    ">>"            { list->AddToken(token::TK_RSHIFT); }
    "+="            { list->AddToken(token::TK_ADD_ASSIGN); }
    "-="            { list->AddToken(token::TK_SUB_ASSIGN); }
    "*="            { list->AddToken(token::TK_MUL_ASSIGN); }
    "/="            { list->AddToken(token::TK_DIV_ASSIGN); }
    "%="            { list->AddToken(token::TK_MOD_ASSIGN); }
    "&="            { list->AddToken(token::TK_AND_ASSIGN); }
    "|="            { list->AddToken(token::TK_OR_ASSIGN); }
    "^="            { list->AddToken(token::TK_EXOR_ASSIGN); }
    "<<="           { list->AddToken(token::TK_LSHIFT_ASSIGN); }
    ">>="           { list->AddToken(token::TK_RSHIFT_ASSIGN); }
    "++"            { list->AddToken(token::TK_INCREMENT); }
    "--"            { list->AddToken(token::TK_DECREMENT); }
    "->"            { list->AddToken(token::TK_ARROW); }
    "::"            { list->AddToken(token::TK_DOUBLECOLON); }
    "##"            { list->AddToken(token::TK_DOUBLEHASH); }

    {blank}+   

    {decimal}{long}?  {   
                        errno = 0;
                        long n = strtol(yytext, NULL, 10);
                        if(n < LONG_MIN || n > LONG_MAX || errno == ERANGE)
                            list->Error("Out of 32bit");
                        list->AddINT32(n);
                    }

    {decimal}{ulong}    {   
                            errno = 0;
                            unsigned long n = strtoul(yytext, NULL, 10);
                            if(n < 0 || n > ULONG_MAX || errno == ERANGE)
                                list->Error("Out of 32bit");
                            list->AddUINT32(n);
                        }

    {decimal}{llong}    {   
                            errno = 0;
                            long long n = strtoll(yytext, NULL, 10);
                            if(n < LONG_LONG_MIN || n > LONG_LONG_MAX || errno == ERANGE)
                                list->Error("Out of 64bit");
                            list->AddINT64(n);
                        } 

    {decimal}{ullong}   {   
                            errno = 0;
                            unsigned long long n = strtoull(yytext, NULL, 10);
                            if(n < 0 || n > ULONG_LONG_MAX || errno == ERANGE)
                                list->Error("Out of 64bit");
                            list->AddUINT64(n);
                        }

    {hex}{long}?  {   
                    errno = 0;
                    long n = strtol(yytext, NULL, 16);
                    if(n < LONG_MIN || n > LONG_MAX || errno == ERANGE)
                        list->Error("Out of 32bit");
                    list->AddINT32(n);
                }

    {hex}{ulong}    {   
                        errno = 0;
                        unsigned long n = strtoul(yytext, NULL, 16);
                        if(n < 0 || n > ULONG_MAX || errno == ERANGE)
                            list->Error("Out of 32bit");
                        list->AddUINT32(n);
                    }

    {hex}{llong}    {   
                        errno = 0;
                        long long n = strtoll(yytext, NULL, 16);
                        if(n < LONG_LONG_MIN || n > LONG_LONG_MAX || errno == ERANGE)
                            list->Error("Out of 64bit");
                        list->AddINT64(n);
                    }  

    {hex}{ullong}   {   
                        errno = 0;
                        unsigned long long n = strtoull(yytext, NULL, 16);
                        if(n < 0 || n > ULONG_LONG_MAX || errno == ERANGE)
                            list->Error("Out of 64bit");
                        list->AddUINT64(n);
                    }                          

    {octal}{long}?  {   
                        errno = 0;
                        long n = strtol(yytext, NULL, 8);
                        if(n < LONG_MIN || n > LONG_MAX || errno == ERANGE)
                            list->Error("Out of 32bit");
                        list->AddINT32(n);
                    }

    {octal}{ulong}  {   
                        errno = 0;
                        unsigned long n = strtoul(yytext, NULL, 8);
                        if(n < 0 || n > ULONG_MAX || errno == ERANGE)
                            list->Error("Out of 32bit");
                        list->AddUINT32(n);
                    }

    {octal}{llong}  {   
                        errno = 0;
                        long long n = strtoll(yytext, NULL, 8);
                        if(n < LONG_LONG_MIN || n > LONG_LONG_MAX || errno == ERANGE)
                            list->Error("Out of 64bit");
                        list->AddINT64(n);
                    }  

    {octal}{ullong} {   
                        errno = 0;
                        unsigned long long n = strtoull(yytext, NULL, 8);
                        if(n < 0 || n > ULONG_LONG_MAX || errno == ERANGE)
                            list->Error("Out of 64bit");
                        list->AddUINT64(n);
                    }

    {float}         {
                        errno = 0;
                        double n = strtod(yytext, NULL);
                        if(n < DBL_MIN || n > DBL_MAX || errno == ERANGE)
                            list->Error("Out of 64bit");
                        list->AddFLOAT64(n);
                    }

    {float}[lL]     {
                        errno = 0;
                        long double n = strtold(yytext, NULL);
                        if(n < LDBL_MIN || n > LDBL_MAX || errno == ERANGE)
                            list->Error("Out of 64bit");
                        list->AddFLOAT64(n);
                    }

    {float}[fF]     {
                        errno = 0;
                        float n = strtof(yytext, NULL);
                        if(n < FLT_MIN || n > FLT_MAX || errno == ERANGE)
                            list->Error("Out of 32bit");
                        list->AddFLOAT32(n);
                    }

    '{character}'   {
                        list->AddCHARACTER(yytext[1]);
                    }
    
    '\\{character}' {
                        list->AddSPECIALCHAR(yytext[2]);
                    }

    {id}            {
                        std::string* str = new std::string(yytext);
                        list->AddIDENTIFIER(str);
                    }
    
    \"              {
                        string_buffer.clear();
                        BEGIN(STRING);
                    }
    .               { list->Error("Unknown character : \"" + std::string(yytext) + "\""); }
}
<STRING>{
    [^\\\n"]+       { string_buffer += yytext; }
    \n              {
                        list->LineBreak();
                        list->Error("String not closed.");
                        string_buffer.clear();
                        BEGIN(INITIAL);
                    }

    <<EOF>>         {
                        list->Error("File ended in the middle of string.");
                        string_buffer.clear();
                        BEGIN(INITIAL);
                    }

    ([\x81-\x9f\xe0-\xef][\x40-\x7e\x80-\xfc])+ { string_buffer += yytext; }

    \\\n            { list->LineBreak(); }

    \\[^\n]         {
                        char tmp = yytext[yyleng - 1];
                        switch(tmp) {
                            case 'a':   tmp = '\a'; break;
                            case 'b':   tmp = '\b'; break;
                            case 'f':   tmp = '\f'; break;
                            case 'n':   tmp = '\n'; break;
                            case 'r':   tmp = '\r'; break;
                            case 't':   tmp = '\t'; break;
                            case '0':   tmp = '\0'; break;
                            default:     break;
                        }
                        string_buffer += tmp;
                    }

    \"              {
                        BEGIN(INITIAL);
                        std::string* str = new std::string(string_buffer);
                        list->AddSTRING(str);
                    }
}
<CPP_COMMENT>{
    [^\n]*          
    \n              {
                        list->LineBreak();
                        BEGIN(INITIAL);
                    }
}
<C_COMMENT>{
    [^*\n]*         
    [^*\n]*\n       { list->LineBreak(); }
    "*"+[^*/\n]*
    "*"+[^*/\n]*\n  { list->LineBreak(); }
    <<EOF>>         { list->Error("File ended in the middle of comment."); }
    "*"+"/"         { BEGIN(INITIAL); }
}

%%

bool ScanBegin(const std::string& filename) {
    if((yyin = fopen(filename.c_str(), "r")) == 0)
        return false;
    return true;
}

void ScanEnd() {
    fclose(yyin);
    yylex_destroy();
}