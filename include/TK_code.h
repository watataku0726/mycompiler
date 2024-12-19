#if defined(TK_ENUMDEF_KEYWORD)
#define KEYWORD(name_, word_)       name_,
#define OPERATOR(name_, word_)
#define PREPROCESSOR(name_, word_)
#elif defined(TK_ENUMDEF_OPERATOR)
#define KEYWORD(name_, word_)   
#define OPERATOR(name_, word_)      name_,
#define PREPROCESSOR(name_, word_)
#elif defined(TK_ENUMDEF_PREPROCESSOR)
#define KEYWORD(name_, word_)   
#define OPERATOR(name_, word_)      
#define PREPROCESSOR(name_, word_)  name_,
#elif defined(TK_CONST_KEYWORD)
#define KEYWORD(name_, word_)       #word_,
#define OPERATOR(name_, word_)
#define PREPROCESSOR(name_, word_)
#elif defined(TK_CONST_OPERATOR)
#define KEYWORD(name_, word_)   
#define OPERATOR(name_, word_)      #word_,
#define PREPROCESSOR(name_, word_)
#elif defined(TK_CONST_PREPROCESSOR)
#define KEYWORD(name_, word_)   
#define OPERATOR(name_, word_)      
#define PREPROCESSOR(name_, word_)  #word_,
#else
#define KEYWORD(name_, word_)   
#define OPERATOR(name_, word_)   
#define PREPROCESSOR(name_, word_)
#endif

OPERATOR(TK_LOGAND, &&)
OPERATOR(TK_LOGOR, ||)
OPERATOR(TK_EQ, ==)
OPERATOR(TK_NE, !=)
OPERATOR(TK_GE, >=)
OPERATOR(TK_LE, <=)
OPERATOR(TK_LSHIFT, <<)
OPERATOR(TK_RSHIFT, >>)
OPERATOR(TK_ADD_ASSIGN, +=)
OPERATOR(TK_SUB_ASSIGN, -=)
OPERATOR(TK_MUL_ASSIGN, *=)
OPERATOR(TK_DIV_ASSIGN, /=)
OPERATOR(TK_MOD_ASSIGN, %=)
OPERATOR(TK_AND_ASSIGN, &=)
OPERATOR(TK_OR_ASSIGN, |=)
OPERATOR(TK_EXOR_ASSIGN, ^=)
OPERATOR(TK_LSHIFT_ASSIGN, <<=)
OPERATOR(TK_RSHIFT_ASSIGN, >>=)
OPERATOR(TK_INCREMENT, ++)
OPERATOR(TK_DECREMENT, --)
OPERATOR(TK_ARROW, ->)
OPERATOR(TK_DOUBLECOLON, ::)
OPERATOR(TK_DOUBLEHASH,  ##)

KEYWORD(TK_AUTO, auto)
KEYWORD(TK_BREAK, break)
KEYWORD(TK_CASE, case)
KEYWORD(TK_CHAR, char)
KEYWORD(TK_CONST, const)
KEYWORD(TK_CONTINUE, continue)
KEYWORD(TK_DEFAULT, default)
KEYWORD(TK_DO, do)
KEYWORD(TK_DOUBLE, double)
KEYWORD(TK_ELSE, else)
KEYWORD(TK_ENUM, enum)
KEYWORD(TK_EXTERN, extern)
KEYWORD(TK_FLOAT, float)
KEYWORD(TK_FOR, for)
KEYWORD(TK_GOTO, goto)
KEYWORD(TK_IF, if)
KEYWORD(TK_INT, int)
KEYWORD(TK_LONG, long)
KEYWORD(TK_REGISTER, register)
KEYWORD(TK_RETURN, return)
KEYWORD(TK_SIGNED, signed)
KEYWORD(TK_SIZEOF, sizeof)
KEYWORD(TK_SHORT, short)
KEYWORD(TK_STATIC, static)
KEYWORD(TK_STRUCT, struct)
KEYWORD(TK_SWITCH, switch)
KEYWORD(TK_TYPEDEF, typedef)
KEYWORD(TK_UNION, union)
KEYWORD(TK_UNSIGNED, unsigned)
KEYWORD(TK_VOID, void)
KEYWORD(TK_VOLATILE, volatile)
KEYWORD(TK_WHILE, while)
KEYWORD(TK_TRUE, true)
KEYWORD(TK_FALSE, false)
KEYWORD(TK_BOOL, bool)
KEYWORD(TK_NULLPTR, nullptr)

PREPROCESSOR(TK_DEFINE, define)
PREPROCESSOR(TK_UNDEF, undef)
PREPROCESSOR(TK_ELIF, elif)
PREPROCESSOR(TK_IFDEF, ifdef)
PREPROCESSOR(TK_IFNDEF, ifndef)
PREPROCESSOR(TK_ENDIF, endif)
PREPROCESSOR(TK_INCLUDE, include)

#undef KEYWORD
#undef OPERATOR
#undef PREPROCESSOR