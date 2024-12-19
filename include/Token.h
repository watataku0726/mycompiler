#if !defined(__TOKEN_H__)
#define __TOKEN_H__
#include <string>


#define IS_TK_OPERATER(type) (0 < (type) && (type) < Token::Type::OPERATER_END)
#define IS_TK_SHORT_OPERATER(type) (0 < (type) && (type) < Token::Type::OPERATER_START)
#define IS_TK_LONG_OPERATER(type) ((Token::Type::OPERATER_START < (type)) && ((type) < Token::Type::OPERATER_END))
#define IS_TK_KEYWORD(type) ((Token::Type::KEYWORDS_START < (type)) && ((type) < Token::Type::KEYWORDS_END))
#define IS_TK_NUMBER(type) ((Token::Type::NUMBER_START < (type)) && ((type) < Token::Type::NUMBER_END))
#define IS_TK_IDNTIFIER(type) ((type) == Token::TK_IDNETIFIER)
#define IS_TK_PREPRO(type)  ((Token::Type::PREPROCESSOR_START < (type) && (type) < Token::Type::PREPROCESSOR_END))
#define IS_TK_IF(type)      ((type) == Token::Type::TK_IF)
#define IS_TK_LINEBREAK(type) ((type) == Token::Type::TK_LINEBREAK)
#define IS_TK_DEFINED(type) ((type) == Token::Type::TK_DEFINED)
#define IS_TK_ARGUMENT_REPLACE(type) ((type) == Token::Type::TK_ARGUMENT_REPLACE)
#define IS_TK_ARGUMENT_REPLACE_STR(type) ((type) == Token::Type::TK_ARGUMENT_REPLACE_STR)

#define IS_TK_INT8(type) ((type) == Token::Type::TK_INT8)
#define IS_TK_INT32(type) (((type) == Token::Type::TK_INT32_DEC) || ((type) == Token::Type::TK_INT32_HEX) || ((type) == Token::Type::TK_INT32_OCT))
#define IS_TK_UINT32(type) (((type) == Token::Type::TK_UINT32_DEC) || ((type) == Token::Type::TK_UINT32_HEX) || ((type) == Token::Type::TK_UINT32_OCT))
#define IS_TK_INT64(type) (((type) == Token::Type::TK_INT64_DEC) || ((type) == Token::Type::TK_INT64_HEX) || ((type) == Token::Type::TK_INT64_OCT))
#define IS_TK_UINT64(type) (((type) == Token::Type::TK_UINT64_DEC) || ((type) == Token::Type::TK_UINT64_HEX) || ((type) == Token::Type::TK_UINT64_OCT))
#define IS_TK_FLOAT32(type) ((type) == Token::Type::TK_FLOAT32)
#define IS_TK_FLOAT64(type) ((type) == Token::Type::TK_FLOAT64)
#define IS_TK_STRING(type) ((type) == Token::Type::TK_STRING)



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
#define TK_ENUMDEF_OPERATOR
#include "TK_code.h"
#undef TK_ENUMDEF_OPERATOR
        OPERATER_END,
        
        KEYWORDS_START = 0x101,
#define TK_ENUMDEF_KEYWORD
#include "TK_code.h"
#undef TK_ENUMDEF_KEYWORD
        KEYWORDS_END,

        NUMBER_START = 0x201,
        TK_INT32_DEC,
        TK_INT32_HEX,
        TK_INT32_OCT,
        TK_UINT32_DEC,
        TK_UINT32_HEX,
        TK_UINT32_OCT,
        TK_INT64_DEC,
        TK_INT64_HEX,
        TK_INT64_OCT,
        TK_UINT64_DEC,
        TK_UINT64_HEX,
        TK_UINT64_OCT,
        TK_FLOAT32,
        TK_FLOAT64,
        NUMBER_END,
        TK_INT32,
        TK_UINT32,
        TK_INT64,
        TK_UINT64,

        TK_STRING = 0x400,
        TK_INT8,
        TK_BOOLEAN,

        TK_IDNETIFIER = 0x500, // [_a-zA-Z][_a-zA-Z0-9]*

        PREPROCESSOR_START = 0x601,
#define TK_ENUMDEF_PREPROCESSOR
#include "TK_code.h"
#undef TK_ENUMDEF_PREPROCESSOR
        PREPROCESSOR_END,

        TK_LINEBREAK = 0x800,
        TK_DEFINED = 0x801,

        TK_ARGUMENT_REPLACE = 0x900,
        TK_ARGUMENT_REPLACE_STR = 0x901,

        END_OF_FILE = 0x1000,
        UNKNOWN_TOKEN = ~0,
        START_TOKEN = 0
    };
    

public:
    explicit Token(Token* token);
    explicit Token(Type type, bool isReplace, unsigned line, int step, int length, int space);
    explicit Token(Type type, char value, unsigned line, int step, int length, int space);
    explicit Token(Type type, int value, unsigned line, int step, int length, int space);
    //Token(Type type, unsigned int value, unsigned line, int step);
    //Token(Type type, long long value, unsigned line, int step);
    //Token(Type type, unsigned long long value, unsigned line, int step);
    //Token(Type type, float value, unsigned line, int step);
    //Token(Type type, double value, unsigned line, int step);
    explicit Token(Type type, std::string* value, unsigned line, int step, int length, int space, bool isReplace);
    ~Token();

    void SetNext(Token* next) { mNext = next; }
    Token* GetNext() const { return mNext; }
    bool IsReplace() const { return mIsReplace; }
    Type GetType() const { return mType; }
    unsigned int GetLine() const { return mLine; }
    int GetStep() const { return mStep; }
    int GetLength() const { return mLength; }
    int GetSpace() const { return mSpace; }

    void ChangeArg2Str() {
        if(IS_TK_ARGUMENT_REPLACE(mType))
            mType = Type::TK_ARGUMENT_REPLACE_STR;
    }

    char GetINT8() const { return mValue.charval; }
    int GetINT32() const { return mValue.sintval; }
    //unsigned int GetUINT32() const { return mValue.uintval; }
    //long long GetINT64() const { return mValue.slonglongval; }
    //unsigned long long GetUINT64() const { return mValue.ulonglongval; }
    //float GetFLOAT32() const { return mValue.floatval; }
    //double GetFLOAT64() const { return mValue.doubleval; }
    const std::string& GetSTRING() const { return *(mValue.strval); }

    void GetContent(std::string& out);
protected:
    union {
        char charval;
        signed int sintval;
        //unsigned int uintval;
        //signed long long slonglongval;
        //unsigned long long ulonglongval;
        //float floatval;
        //double doubleval;
        std::string* strval;
    } mValue;
    Token* mNext;
    Type mType;
    unsigned int mLine;
    int mStep;
    int mLength;
    int mSpace;
    bool mIsReplace;

private:
    static int mNumbers;
public:
    static int GetNumbers() { return mNumbers; }

};

/*
class PreProToken : public Token {
public:
    PreProToken(Token::Type type, unsigned line, int step)
        :mNextPrePro(nullptr), mPrevPrePro(nullptr), mList(nullptr)
        ,Token(type, line, step)    
    {
        mIsReplace = true;
    }
    ~PreProToken() { delete mList; }

    const PreProToken* GetNextPrePro() const { return mNextPrePro; }
    const PreProToken* GetPrevPrePro() const { return mPrevPrePro; }
    void SetNextPrePro(PreProToken* token) { mNextPrePro = token; }
    void SetPrevPrePro(PreProToken* token) { mPrevPrePro = token; }

protected:
    PreProToken* mNextPrePro;
    PreProToken* mPrevPrePro;
    TokenList* mList;
};

class ObjectMacroToken : public PreProToken {
public:
    ObjectMacroToken(unsigned line, int step)
        : mContent(nullptr)
        , PreProToken(Token::Type::TK_MACRO_OBJECT, line, step)
        {}
    ~ObjectMacroToken() { delete mContent; }

protected:
    std::string* mContent;
};

class FucntionMacroToken : public PreProToken {
public:
    FucntionMacroToken(unsigned line, int step)
        : mContent(nullptr), mArgs(nullptr), mNumArgs(0)
        , PreProToken(Token::Type::TK_MACRO_FUNCTION, line, step)
        {}
    ~FucntionMacroToken() { delete mContent; delete mArgs; }

protected:
    struct ArgList {
        std::string* mArg;
        struct ArgList* mNext;
        ~ArgList() { delete mArg; delete mNext; }
    }* mArgs;
    std::string* mContent;
    unsigned mNumArgs;
};

class IFToken : public PreProToken {
    IFToken(unsigned line, int step)
        :mComtent(nullptr), mExpr(nullptr), mELSEToken(nullptr)
        ,PreProToken(Token::Type::TK_PREPRO_IF, line, step)
        {}
    ~IFToken() { delete mComtent; delete mExpr; delete mELSEToken; }

protected:
    std::string* mComtent;
    TokenList* mExpr;
    IFToken* mELSEToken;
};

class INCLUDEToken : public PreProToken {
    INCLUDEToken(unsigned line, int step);
    ~INCLUDEToken();
};

*/

#endif // !__TOKEN_H__