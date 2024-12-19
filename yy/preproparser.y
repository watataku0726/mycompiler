%skeleton "lalr1.cc"
%define api.namespace {yy1}
%defines
%code requires {
#include "IntNode.h"
class TokenList;


}
%parse-param    { TokenList* list } 
%parse-param    { Integer& ret  }
%lex-param      { TokenList* list }

%union {
    bool                    boolean;
    char                    int8;
    int                     int32;
    unsigned int            uint32;
    long long int           int64;
    unsigned long long int  uint64;

    IntNode* expr;
}

%token	END_OF_FILE 0 "end of file"
%token	TK_LOGOR      "||"
%token	TK_LOGAND     "&&"
%token	TK_EQ         "=="
%token	TK_NE         "!="
%token	TK_GE         ">="
%token	TK_LE         "<="
%token  TK_LSHIFT     "<<"
%token  TK_RSHIFT     ">>"

%token <boolean>    TK_BOOLEAN  "boolean"
%token <int8>       TK_INT8     "int8"
%token <int32>      TK_INT32    "int32"
%token <uint32>     TK_UINT32   "uint32"
%token <int64>      TK_INT64    "int64"
%token <uint64>     TK_UINT64   "uint64"

%type <expr>  expr

%destructor { delete $$; } expr

%right COND;
%left "||";
%left "&&";
%nonassoc "==" "!=" '>' '<' ">=" "<=";
%left '&' '^' '|';
%left "<<" ">>";
%left '+' '-';
%left '*' '/' '%';
%left NEG POS NOT LOGNOT;

%code {
#include <string>
#include <cstdlib>
#include <cerrno>
#include <climits>
#include <vector>
#include "Token.h"
#include "TokenList.h"

static yy1::parser::token_type yylex(yy1::parser::semantic_type* yylval, TokenList* list);
}
%%
%start unit;

unit    : expr error                    { delete $1; }
        | expr                          { ret = $1->Calculate(list); delete $1; }
    
expr    : expr "&&" expr                { $$ = new IntNode(IntNode::OPCODE::OP_LOGAND, $1, $3); }
        | expr "||" expr                { $$ = new IntNode(IntNode::OPCODE::OP_LOGOR, $1, $3); }
        | expr "==" expr                { $$ = new IntNode(IntNode::OPCODE::OP_EQ, $1, $3); }
        | expr "!=" expr                { $$ = new IntNode(IntNode::OPCODE::OP_NE, $1, $3); }
        | expr '>' expr                 { $$ = new IntNode(IntNode::OPCODE::OP_GT, $1, $3); }
        | expr ">=" expr                { $$ = new IntNode(IntNode::OPCODE::OP_GE, $1, $3); }
        | expr '<' expr                 { $$ = new IntNode(IntNode::OPCODE::OP_LT, $1, $3); }
        | expr "<=" expr                { $$ = new IntNode(IntNode::OPCODE::OP_LE, $1, $3); }
        | expr '&' expr                 { $$ = new IntNode(IntNode::OPCODE::OP_AND, $1, $3); }
        | expr '^' expr                 { $$ = new IntNode(IntNode::OPCODE::OP_EXOR, $1, $3); }
        | expr '|' expr                 { $$ = new IntNode(IntNode::OPCODE::OP_OR, $1, $3); }
        | expr "<<" expr                { $$ = new IntNode(IntNode::OPCODE::OP_LSHIFT, $1, $3); }
        | expr ">>" expr                { $$ = new IntNode(IntNode::OPCODE::OP_RSHIFT, $1, $3); }
        | expr '-' expr                 { $$ = new IntNode(IntNode::OPCODE::OP_SUB, $1, $3); }
        | expr '+' expr                 { $$ = new IntNode(IntNode::OPCODE::OP_ADD, $1, $3); }
        | expr '*' expr                 { $$ = new IntNode(IntNode::OPCODE::OP_MUL, $1, $3); }
        | expr '/' expr                 { $$ = new IntNode(IntNode::OPCODE::OP_DIV, $1, $3); }
        | expr '%' expr                 { $$ = new IntNode(IntNode::OPCODE::OP_MOD, $1, $3); }
        | '-' expr %prec NEG            { $$ = new IntNode(IntNode::OPCODE::OP_NEG, $2); }
        | '+' expr %prec POS            { $$ = new IntNode(IntNode::OPCODE::OP_POS, $2); }
        | '!' expr %prec LOGNOT         { $$ = new IntNode(IntNode::OPCODE::OP_LOGNOT, $2); }
        | '~' expr %prec NOT            { $$ = new IntNode(IntNode::OPCODE::OP_NOT, $2); } 
        | '(' expr ')'                  { $$ = $2; } 
        | expr '?' expr ':' expr %prec COND    { $$ = new IntNode(IntNode::OPCODE::OP_COND, $1, $3, $5); }
        | "boolean"                     { $$ = new IntNode($1); }
        | "int8"                        { $$ = new IntNode($1); }
        | "int32"                       { $$ = new IntNode($1); }
        | "uint32"                      { $$ = new IntNode($1); }
        | "int64"                       { $$ = new IntNode($1); }
        | "uint64"                      { $$ = new IntNode($1); }
%%

static yy1::parser::token_type yylex(yy1::parser::semantic_type* yylval, TokenList* list) {
    while(1) {
        Token* token = list->Dequeue();
        if(token == nullptr) 
            return yy1::parser::token_type::END_OF_FILE;
        //std::cout << token->GetType() << std::endl;
        switch(token->GetType()) {
            case Token::Type::TK_EXCLAMATION:   delete token; return (yy1::parser::token_type)'!';
            case Token::Type::TK_PERCENT:       delete token; return (yy1::parser::token_type)'%';
            case Token::Type::TK_AMPERSAND:     delete token; return (yy1::parser::token_type)'&';
            case Token::Type::TK_OPENPAREN:     delete token; return (yy1::parser::token_type)'(';
            case Token::Type::TK_CLOSEDPAREN:   delete token; return (yy1::parser::token_type)')';
            case Token::Type::TK_ASTER:         delete token; return (yy1::parser::token_type)'*';
            case Token::Type::TK_PLUS:          delete token; return (yy1::parser::token_type)'+';
            case Token::Type::TK_MINUS:         delete token; return (yy1::parser::token_type)'-';
            case Token::Type::TK_SLASH:         delete token; return (yy1::parser::token_type)'/';
            case Token::Type::TK_COLON:         delete token; return (yy1::parser::token_type)':';
            case Token::Type::TK_LT:            delete token; return (yy1::parser::token_type)'<';
            case Token::Type::TK_GT:            delete token; return (yy1::parser::token_type)'>';
            case Token::Type::TK_QUESTION:      delete token; return (yy1::parser::token_type)'?';
            case Token::Type::TK_HAT:           delete token; return (yy1::parser::token_type)'^';
            case Token::Type::TK_VERTICAL:      delete token; return (yy1::parser::token_type)'|';
            case Token::Type::TK_TILDE:         delete token; return (yy1::parser::token_type)'~';
            case Token::Type::TK_LOGAND:        delete token; return yy1::parser::token_type::TK_LOGAND; // &&
            case Token::Type::TK_LOGOR:         delete token; return yy1::parser::token_type::TK_LOGOR;  // ||
            case Token::Type::TK_EQ:            delete token; return yy1::parser::token_type::TK_EQ; // ==
            case Token::Type::TK_NE:            delete token; return yy1::parser::token_type::TK_NE; // !=
            case Token::Type::TK_GE:            delete token; return yy1::parser::token_type::TK_GE; // >=
            case Token::Type::TK_LE:            delete token; return yy1::parser::token_type::TK_LE; // <=
            case Token::Type::TK_LSHIFT:        delete token; return yy1::parser::token_type::TK_LSHIFT; // <<
            case Token::Type::TK_RSHIFT:        delete token; return yy1::parser::token_type::TK_RSHIFT; // >>
            case Token::Type::TK_INT32_DEC: {
                errno = 0;
                long n = strtol(token->GetSTRING().c_str(), NULL, 10);
                if(n < LONG_MIN || n > LONG_MAX || errno == ERANGE)
                    list->Error("Out of 32bit");
                yylval->int32 = n;
                delete token;
                return yy1::parser::token_type::TK_INT32;
            }
            case Token::Type::TK_INT32_HEX: {
                errno = 0;
                long n = strtol(token->GetSTRING().c_str(), NULL, 16);
                if(n < LONG_MIN || n > LONG_MAX || errno == ERANGE)
                    list->Error("Out of 32bit");
                yylval->int32 = n;
                delete token;
                return yy1::parser::token_type::TK_INT32;
            }
            case Token::Type::TK_INT32_OCT: {
                errno = 0;
                long n = strtol(token->GetSTRING().c_str(), NULL, 8);
                if(n < LONG_MIN || n > LONG_MAX || errno == ERANGE)
                    list->Error("Out of 32bit");
                yylval->int32 = n;
                delete token;
                return yy1::parser::token_type::TK_INT32;
            }
            case Token::Type::TK_UINT32_DEC: {
                errno = 0;
                unsigned long n = strtoul(token->GetSTRING().c_str(), NULL, 10);
                if(n < 0 || n > ULONG_MAX || errno == ERANGE)
                    list->Error("Out of 32bit");
                yylval->uint32 = n;
                delete token;
                return yy1::parser::token_type::TK_UINT32;
            }
            case Token::Type::TK_UINT32_HEX: {
                errno = 0;
                unsigned long n = strtoul(token->GetSTRING().c_str(), NULL, 16);
                if(n < 0 || n > ULONG_MAX || errno == ERANGE)
                    list->Error("Out of 32bit");
                yylval->uint32 = n;
                delete token;
                return yy1::parser::token_type::TK_UINT32;
            }
            case Token::Type::TK_UINT32_OCT: {
                errno = 0;
                unsigned long n = strtoul(token->GetSTRING().c_str(), NULL, 8);
                if(n < 0 || n > ULONG_MAX || errno == ERANGE)
                    list->Error("Out of 32bit");
                yylval->uint32 = n;
                delete token;
                return yy1::parser::token_type::TK_UINT32;
            }
            case Token::Type::TK_INT64_DEC:{
                errno = 0;
                long long n = strtoll(token->GetSTRING().c_str(), NULL, 10);
                if(n < LONG_LONG_MIN || n > LONG_LONG_MAX || errno == ERANGE)
                    list->Error("Out of 64bit");
                yylval->int64 = n;
                delete token;
                return yy1::parser::token_type::TK_INT64;
            }
            case Token::Type::TK_INT64_HEX: {
                errno = 0;
                long long n = strtoll(token->GetSTRING().c_str(), NULL, 16);
                if(n < LONG_LONG_MIN || n > LONG_LONG_MAX || errno == ERANGE)
                    list->Error("Out of 64bit");
                yylval->int64 = n;
                delete token;
                return yy1::parser::token_type::TK_INT64;
            }
            case Token::Type::TK_INT64_OCT: {
                errno = 0;
                long long n = strtoll(token->GetSTRING().c_str(), NULL, 8);
                if(n < LONG_LONG_MIN || n > LONG_LONG_MAX || errno == ERANGE)
                    list->Error("Out of 64bit");
                yylval->int64 = n;
                delete token;
                return yy1::parser::token_type::TK_INT64;
            }
            case Token::Type::TK_UINT64_DEC: {
                errno = 0;
                unsigned long long n = strtoull(token->GetSTRING().c_str(), NULL, 10);
                if(n < 0 || n > ULONG_LONG_MAX || errno == ERANGE)
                    list->Error("Out of 64bit");
                yylval->uint64 = n;
                delete token;
                return yy1::parser::token_type::TK_UINT64;
            }
            case Token::Type::TK_UINT64_HEX: {
                errno = 0;
                unsigned long long n = strtoull(token->GetSTRING().c_str(), NULL, 16);
                if(n < 0 || n > ULONG_LONG_MAX || errno == ERANGE)
                    list->Error("Out of 64bit");
                yylval->uint64 = n;
                delete token;
                return yy1::parser::token_type::TK_UINT64;
            }
            case Token::Type::TK_UINT64_OCT: {
                errno = 0;
                unsigned long long n = strtoull(token->GetSTRING().c_str(), NULL, 16);
                if(n < 0 || n > ULONG_LONG_MAX || errno == ERANGE)
                    list->Error("Out of 64bit");
                yylval->uint64 = n;
                delete token;
                return yy1::parser::token_type::TK_UINT64;
            }
            case Token::Type::TK_INT8: {
                yylval->int8 =token->GetINT8();
                delete token;
                return yy1::parser::token_type::TK_INT8;
            }
            case Token::Type::TK_TRUE: {
                yylval->boolean = true;
                delete token;
                return yy1::parser::token_type::TK_BOOLEAN;
            }
            case Token::Type::TK_FALSE: {
                yylval->boolean = false;
                delete token;
                return yy1::parser::token_type::TK_BOOLEAN;
            }
            default: {
                std::string str;
                token->GetContent(str);
                delete token;
                list->Error(token->GetLine(), token->GetStep(), "Unknown Token: " + str); 
                break;
            }
        }
    }
}

void yy1::parser::error(const std::string& m) {
    list->Error(0,0,m);
}
        