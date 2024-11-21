#include <string>
#include <iostream>
#include <sstream>

#define IS_TK_OPERATER(type) ((type) < Token::Type::OPERATER_END)
#define IS_TK_SHORT_OPERATER(type) ((type) < Token::Type::OPERATER_START)
#define IS_TK_LONG_OPERATER(type) ((Token::Type::OPERATER_START < (type)) && ((type) < Token::Type::OPERATER_END))
#define IS_TK_KEYWORD(type) ((Token::Type::KEYWORDS_START < (type)) && ((type) < Token::Type::KEYWORDS_END))
#define IS_TK_NUMBER(type) ((Token::Type::NUMBER_START < (type)) && ((type) < Token::Type::NUMBER_END))
#define IS_TK_IDNTIFIER(type) ((type) == Token::TK_IDNETIFIER)

#define IS_TK_INT8(type) ((type) == Token::Type::TK_INT8)
#define IS_TK_INT32(type) ((type) == Token::Type::TK_INT32)
#define IS_TK_UINT32(type) ((type) == Token::Type::TK_UINT32)
#define IS_TK_INT64(type) ((type) == Token::Type::TK_INT64)
#define IS_TK_UINT64(type) ((type) == Token::Type::TK_UINT32)
#define IS_TK_FLOAT32(type) ((type) == Token::Type::TK_FLOAT32)
#define IS_TK_FLOAT64(type) ((type) == Token::Type::TK_FLOAT64)
#define IS_TK_STRING(type) ((type) == Token::Type::TK_STRING)

#define YY_DECL   void PreLex(class TokenList* list)

YY_DECL;

bool ScanBegin(const std::string& filename);
void ScanEnd();

class Token {
public:
    enum Type {
        TK_EXCLAMATION = '!',
        TK_HASH = '#',
        TK_PERCENT = '%',
        TK_AMPERSAND = '&',
        TK_OPENPAREN = '(',
        TK_CLOSEDPAREN = ')',
        TK_ASTER = '*',
        TK_PLUS = '+',
        TK_COMMA = ',',
        TK_MINUS = '-',
        TK_PERIOD = '.',
        TK_SLASH = '/',
        TK_COLON = ':',
        TK_SEMICOLON = ';',
        TK_LT = '<',
        TK_EQUAL = '=',
        TK_GT = '>',
        TK_QUESTION = '?',
        TK_OPENSQUARE = '[',
        TK_CLOSEDSQUARE = ']',
        TK_HAT = '^',
        TK_OPENCURLY = '{',
        TK_VERTICAL = '|',
        TK_CLOSEDCURLY = '}',
        TK_TILDE = '~',

        OPERATER_START = 0x80,
        TK_LOGAND, // &&
        TK_LOGOR, // ||
        TK_EQ, // ==
        TK_NE, // !=
        TK_GE, // >=
        TK_LE, // <=
        TK_LSHIFT, // <<
        TK_RSHIFT, // >>
        TK_ADD_ASSIGN, // +=
        TK_SUB_ASSIGN, // -=
        TK_MUL_ASSIGN, // *=
        TK_DIV_ASSIGN, // /=
        TK_MOD_ASSIGN, // %=
        TK_AND_ASSIGN, // &=
        TK_OR_ASSIGN, // |=
        TK_EXOR_ASSIGN, // ^=
        TK_LSHIFT_ASSIGN, // <<=
        TK_RSHIFT_ASSIGN, // >>=
        TK_INCREMENT, // ++
        TK_DECREMENT, //--
        TK_ARROW, // ->
        TK_DOUBLECOLON, // ::
        TK_DOUBLEHASH,  // ##
        OPERATER_END = 0x100,
        
        KEYWORDS_START = 0x101,
        TK_AUTO,
        TK_BREAK,
        TK_CASE,
        TK_CHAR,
        TK_CONST,
        TK_CONTINUE,
        TK_DEFAULT,
        TK_DO,
        TK_DOUBLE,
        TK_ELSE,
        TK_ENUM,
        TK_EXTERN,
        TK_FLOAT,
        TK_FOR,
        TK_GOTO,
        TK_IF,
        TK_INT,
        TK_LONG,
        TK_REGISTER,
        TK_RETURN,
        TK_SIGNED,
        TK_SIZEOF,
        TK_SHORT,
        TK_STATIC,
        TK_STRUCT,
        TK_SWITCH,
        TK_TYPEDEF,
        TK_UNION,
        TK_UNSIGNED,
        TK_VOID,
        TK_VOLATILE,
        TK_WHILE,
        
        TK_TRUE,
        TK_FALSE,
        TK_BOOL,
        KEYWORDS_END  = 0x200,

        NUMBER_START = 0x201,
        TK_INT32,
        TK_UINT32,
        TK_INT64,
        TK_UINT64,
        TK_FLOAT32,
        TK_FLOAT64,
        TK_INT8,
        TK_BOOLEAN,
        NUMBER_END = 0x300,

        TK_IDNETIFIER = 0x500, // [_a-zA-Z][_a-zA-Z0-9]*
        TK_STRING = 0x400,

        END_OF_FILE = 0x1000
    };
    

public:
    Token(Type type, unsigned line);
    Token(Type type, char value, unsigned line);
    Token(Type type, int value, unsigned line);
    Token(Type type, unsigned int value, unsigned line);
    Token(Type type, long long value, unsigned line);
    Token(Type type, unsigned long long value, unsigned line);
    Token(Type type, float value, unsigned line);
    Token(Type type, double value, unsigned line);
    Token(Type type, std::string* value, unsigned line);
     ~Token();

    void SetNext(Token* next) { mNext = next; }
    const Token* GetNext() const { return mNext; }
    bool IsReplace() const { return mIsReplace; }
    Type GetType() const { return mType; }
    unsigned int GetLine() const { return mLine; }

    char GetINT8() const { return mValue.charval; }
    int GetINT32() const { return mValue.sintval; }
    unsigned int GetUINT32() const { return mValue.uintval; }
    long long GetINT64() const { return mValue.slonglongval; }
    unsigned long long GetUINT64() const { return mValue.ulonglongval; }
    float GetFLOAT32() const { return mValue.floatval; }
    double GetFLOAT64() const { return mValue.doubleval; }
    const std::string& GetSTRING() const { return *(mValue.strval); }

protected:
    union {
        char charval;
        signed int sintval;
        unsigned int uintval;
        signed long long slonglongval;
        unsigned long long ulonglongval;
        float floatval;
        double doubleval;
        std::string* strval;
    } mValue;
    Token* mNext;
    Type mType;
    unsigned int mLine;
    bool mIsReplace;
};

class TokenList {
public:
    TokenList();
    ~TokenList();

    void AddToken(Token::Type type);
    void AddINT32(int value);
    void AddUINT32(unsigned value);
    void AddINT64(long long value);
    void AddUINT64(unsigned long long value);
    void AddFLOAT32(float value);
    void AddFLOAT64(double value);
    void AddCHARACTER(char value);
    void AddSPECIALCHAR(char value);
    void AddSTRING(std::string* str);
    void AddIDENTIFIER(std::string* id);
    void AddKEYWORD(Token::Type type, std::string* keyword);
    
    const Token* GetHead() const { return mHead; }
    const Token* GetTail() const { return mTail; }
    unsigned GetLine() const { return mLine; }
    void LineBreak() { ++mLine; }
    void Error(const std::string& str = "") { std::cerr << "error : line" << mLine << " : " << str << std::endl; }
    
    void PrintTokens(std::stringstream& ss);
private:
    Token* mHead;
    Token* mTail;
    unsigned mLine;
};

