%{
#include <string>
#include <cstdlib>
#include <cerrno>
#include <climits>
#include <cfloat>
#include "Token.h"

#define yyterminate() return;
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
%x PREPROCESSOR
%x MACRO
%x INCLUDE
%x IF
%x MACRO_CONTENT
%x ARGUMENT

%{
#define YY_USER_ACTION list->Step(yyleng);
%}
%%
%{
    typedef Token::Type token;
    std::string string_buffer;
%}
<INITIAL>{
    \n              { list->AddLineBreakToken(); list->LineBreak(); }
    "//"            { BEGIN(CPP_COMMENT); }
    "/*"            { BEGIN(C_COMMENT); }

    "auto"          { list->AddToken(token::TK_AUTO); }
    "break"         { list->AddToken(token::TK_BREAK); }
    "case"          { list->AddToken(token::TK_CASE); }
    "char"          { list->AddToken(token::TK_CHAR); }
    "const"         { list->AddToken(token::TK_CONST); }
    "continue"      { list->AddToken(token::TK_CONTINUE); }
    "default"       { list->AddToken(token::TK_DEFAULT); }
    "do"            { list->AddToken(token::TK_DO); }
    "double"        { list->AddToken(token::TK_DOUBLE); }
    "else"          { list->AddToken(token::TK_ELSE); }
    "enum"          { list->AddToken(token::TK_ENUM); }
    "extern"        { list->AddToken(token::TK_EXTERN); }
    "float"         { list->AddToken(token::TK_FLOAT); }
    "for"           { list->AddToken(token::TK_FOR); }
    "goto"          { list->AddToken(token::TK_GOTO); }
    "if"            { list->AddToken(token::TK_IF); }
    "int"           { list->AddToken(token::TK_INT); }
    "long"          { list->AddToken(token::TK_LONG); }
    "register"      { list->AddToken(token::TK_REGISTER); }
    "return"        { list->AddToken(token::TK_RETURN); }
    "signed"        { list->AddToken(token::TK_SIGNED); }
    "sizeof"        { list->AddToken(token::TK_SIZEOF); }
    "short"         { list->AddToken(token::TK_SHORT); }
    "static"        { list->AddToken(token::TK_STATIC); }
    "struct"        { list->AddToken(token::TK_STRUCT); }
    "switch"        { list->AddToken(token::TK_SWITCH); }
    "typedef"       { list->AddToken(token::TK_TYPEDEF); }
    "union"         { list->AddToken(token::TK_UNION); }
    "unsigned"      { list->AddToken(token::TK_UNSIGNED); }
    "void"          { list->AddToken(token::TK_VOID); }
    "volatile"      { list->AddToken(token::TK_VOLATILE); }
    "while"         { list->AddToken(token::TK_WHILE); }
        
    "true"          { list->AddToken(token::TK_TRUE); }
    "false"         { list->AddToken(token::TK_FALSE); }
    "bool"          { list->AddToken(token::TK_BOOL); }
    "nullptr"       { list->AddToken(token::TK_NULLPTR); }

    "define"        { list->AddToken(token::TK_DEFINE); }    
    "undef"         { list->AddToken(token::TK_UNDEF); }
    "elif"          { list->AddToken(token::TK_ELIF); }
    "ifdef"         { list->AddToken(token::TK_IFDEF); }
    "ifndef"        { list->AddToken(token::TK_IFNDEF); }
    "endif"         { list->AddToken(token::TK_ENDIF); }
    "defined"       { list->AddToken(token::TK_DEFINED); }
    "include"       { list->AddToken(token::TK_INCLUDE); }

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
                        /*errno = 0;
                        long n = strtol(yytext, NULL, 10);
                        if(n < LONG_MIN || n > LONG_MAX || errno == ERANGE)
                            list->Error("Out of 32bit");
                        list->AddINT32(n);*/
                        std::string* str = new std::string(yytext);
                        list->AddNUMBER(token::TK_INT32_DEC, str);
                    }

    {decimal}{ulong}    {   
                            /*errno = 0;
                            unsigned long n = strtoul(yytext, NULL, 10);
                            if(n < 0 || n > ULONG_MAX || errno == ERANGE)
                                list->Error("Out of 32bit");
                            list->AddUINT32(n);*/
                            std::string* str = new std::string(yytext);
                            list->AddNUMBER(token::TK_UINT32_DEC, str);
                        }

    {decimal}{llong}    {   
                            /*errno = 0;
                            long long n = strtoll(yytext, NULL, 10);
                            if(n < LONG_LONG_MIN || n > LONG_LONG_MAX || errno == ERANGE)
                                list->Error("Out of 64bit");
                            list->AddINT64(n);*/
                            std::string* str = new std::string(yytext);
                            list->AddNUMBER(token::TK_INT64_DEC, str);
                        } 

    {decimal}{ullong}   {   
                            /*errno = 0;
                            unsigned long long n = strtoull(yytext, NULL, 10);
                            if(n < 0 || n > ULONG_LONG_MAX || errno == ERANGE)
                                list->Error("Out of 64bit");
                            list->AddUINT64(n);*/
                            std::string* str = new std::string(yytext);
                            list->AddNUMBER(token::TK_UINT64_DEC, str);
                        }

    {hex}{long}?  {   
                    /*errno = 0;
                    long n = strtol(yytext, NULL, 16);
                    if(n < LONG_MIN || n > LONG_MAX || errno == ERANGE)
                        list->Error("Out of 32bit");
                    list->AddINT32(n);*/
                    std::string* str = new std::string(yytext);
                    list->AddNUMBER(token::TK_INT32_HEX, str);
                }

    {hex}{ulong}    {   
                        /*errno = 0;
                        unsigned long n = strtoul(yytext, NULL, 16);
                        if(n < 0 || n > ULONG_MAX || errno == ERANGE)
                            list->Error("Out of 32bit");
                        list->AddUINT32(n);*/
                        std::string* str = new std::string(yytext);
                        list->AddNUMBER(token::TK_UINT32_HEX, str);
                    }

    {hex}{llong}    {   
                        /*errno = 0;
                        long long n = strtoll(yytext, NULL, 16);
                        if(n < LONG_LONG_MIN || n > LONG_LONG_MAX || errno == ERANGE)
                            list->Error("Out of 64bit");
                        list->AddINT64(n);*/
                        std::string* str = new std::string(yytext);
                        list->AddNUMBER(token::TK_INT64_HEX, str);
                    }  

    {hex}{ullong}   {   
                        /*errno = 0;
                        unsigned long long n = strtoull(yytext, NULL, 16);
                        if(n < 0 || n > ULONG_LONG_MAX || errno == ERANGE)
                            list->Error("Out of 64bit");
                        list->AddUINT64(n);*/
                        std::string* str = new std::string(yytext);
                        list->AddNUMBER(token::TK_UINT64_HEX, str);
                    }                          

    {octal}{long}?  {   
                        /*errno = 0;
                        long n = strtol(yytext, NULL, 8);
                        if(n < LONG_MIN || n > LONG_MAX || errno == ERANGE)
                            list->Error("Out of 32bit");
                        list->AddINT32(n);*/
                        std::string* str = new std::string(yytext);
                        list->AddNUMBER(token::TK_INT32_OCT, str);
                    }

    {octal}{ulong}  {   
                        /*errno = 0;
                        unsigned long n = strtoul(yytext, NULL, 8);
                        if(n < 0 || n > ULONG_MAX || errno == ERANGE)
                            list->Error("Out of 32bit");
                        list->AddUINT32(n);*/
                        std::string* str = new std::string(yytext);
                        list->AddNUMBER(token::TK_UINT32_OCT, str);
                    }

    {octal}{llong}  {   
                        /*errno = 0;
                        long long n = strtoll(yytext, NULL, 8);
                        if(n < LONG_LONG_MIN || n > LONG_LONG_MAX || errno == ERANGE)
                            list->Error("Out of 64bit");
                        list->AddINT64(n);*/
                        std::string* str = new std::string(yytext);
                        list->AddNUMBER(token::TK_INT64_OCT, str);
                    }  

    {octal}{ullong} {   
                        /*errno = 0;
                        unsigned long long n = strtoull(yytext, NULL, 8);
                        if(n < 0 || n > ULONG_LONG_MAX || errno == ERANGE)
                            list->Error("Out of 64bit");
                        list->AddUINT64(n);*/
                        std::string* str = new std::string(yytext);
                        list->AddNUMBER(token::TK_UINT64_OCT, str);
                    }

    {float}         {
                        /*errno = 0;
                        double n = strtod(yytext, NULL);
                        if(n < DBL_MIN || n > DBL_MAX || errno == ERANGE)
                            list->Error("Out of 64bit");
                        list->AddFLOAT64(n);*/
                        std::string* str = new std::string(yytext);
                        list->AddNUMBER(token::TK_FLOAT64, str);
                    }

    {float}[lL]     {
                        /*errno = 0;
                        long double n = strtold(yytext, NULL);
                        if(n < LDBL_MIN || n > LDBL_MAX || errno == ERANGE)
                            list->Error("Out of 64bit");
                        list->AddFLOAT64(n);*/
                        std::string* str = new std::string(yytext);
                        list->AddNUMBER(token::TK_FLOAT64, str);
                    }

    {float}[fF]     {
                        /*errno = 0;
                        float n = strtof(yytext, NULL);
                        if(n < FLT_MIN || n > FLT_MAX || errno == ERANGE)
                            list->Error("Out of 32bit");
                        list->AddFLOAT32(n);*/
                        std::string* str = new std::string(yytext);
                        list->AddNUMBER(token::TK_FLOAT32, str);
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
    .               { list->AddUnknownToken(yytext[0]); /*list->Error("Unknown character : \"" + std::string(yytext) + "\"");*/ }
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