#include "Token.h"
#include <sstream>
#include <iostream>

/*==========================================================================*/
/*         Token                                                            */
/*==========================================================================*/

int Token::mNumbers = 0;

Token::Token(Token* token) 
    :mNext(nullptr)
{
    ++mNumbers;
    if(token != nullptr) {
        mType = token->GetType();
        mLine = token->GetLine();
        mStep = token->GetStep();
        mLength = token->GetLength();
        mSpace = token->GetSpace();
        mIsReplace = token->IsReplace();

        if(IS_TK_IDNTIFIER(mType) || IS_TK_STRING(mType) || IS_TK_NUMBER(mType)) {
            mValue.strval = new std::string(token->GetSTRING());
        } else
            mValue = token->mValue;
    } else {
        mType = Token::Type::UNKNOWN_TOKEN;
        mLine = 0;
        mStep = 0;
        mLength = 0;
        mSpace = 0;
        mIsReplace = false;
        mValue.sintval = 0;
    }
}

Token::Token(Type type, bool isReplace, unsigned line, int step, int length, int space)
    :mType(type), mIsReplace(isReplace), mLine(line), mNext(nullptr), mStep(step), mLength(length), mSpace(space)
{   
    ++mNumbers;
    mValue.sintval = 0;
}

Token::Token(Type type, char value, unsigned line, int step, int length, int space)
    :mType(type), mIsReplace(false), mLine(line), mNext(nullptr), mStep(step), mLength(length), mSpace(space)
{
    ++mNumbers;
    mValue.charval = value;
}

Token::Token(Type type, int value, unsigned line, int step, int length, int space)
    :mType(type), mIsReplace(false), mLine(line), mNext(nullptr), mStep(step), mLength(length), mSpace(space)
{
    ++mNumbers;
    mValue.sintval = value;
}
/*
Token::Token(Type type, unsigned int value, unsigned line, int step)
    :mType(type), mIsReplace(false), mLine(line), mNext(nullptr), mStep(step)
{
    mValue.uintval = value;
}

Token::Token(Type type, long long value, unsigned line, int step)
    :mType(type), mIsReplace(false), mLine(line), mNext(nullptr), mStep(step)
{
    mValue.slonglongval = value;
}

Token::Token(Type type, unsigned long long value, unsigned line, int step)
    :mType(type), mIsReplace(false), mLine(line), mNext(nullptr), mStep(step)
{
    mValue.ulonglongval = value;
}

Token::Token(Type type, float value, unsigned line, int step)
    :mType(type), mIsReplace(false), mLine(line), mNext(nullptr), mStep(step)
{
    mValue.floatval = value;
}

Token::Token(Type type, double value, unsigned line, int step)
    :mType(type), mIsReplace(false), mLine(line), mNext(nullptr), mStep(step)
{   
    mValue.doubleval = value;
}
*/
Token::Token(Type type, std::string* value, unsigned line, int step, int length, int space, bool isReplace) 
    :mType(type), mIsReplace(isReplace), mLine(line), mNext(nullptr), mStep(step), mLength(length), mSpace(space)
{
    ++mNumbers;
    mValue.strval = value;
}

Token::~Token() {
    //std::cout << mType << std::endl;
    --mNumbers;
    if(IS_TK_NUMBER(mType) || IS_TK_IDNTIFIER(mType) || IS_TK_STRING(mType)) {
        delete mValue.strval;
        mValue.strval = nullptr;
    }
    //delete mNext;
}

void Token::GetContent(std::string& out) {
    static const char* KEYWORDS[] = {
#define TK_CONST_KEYWORD
#include "TK_code.h"
#undef TK_CONST_KEYWORD
    };

    static const char* OPERATORS[] = {
#define TK_CONST_OPERATOR
#include "TK_code.h"
#undef TK_CONST_OPERATOR
    };

    static const char* PREPROCESSORS[] = {
#define TK_CONST_PREPROCESSOR
#include "TK_code.h"
#undef TK_CONST_PREPROCESSOR
    };
    
    if(IS_TK_SHORT_OPERATER(mType))
        out = (char)mType;
    else if(IS_TK_LONG_OPERATER(mType)) {
        out = OPERATORS[mType - Token::Type::OPERATER_START - 1];
    } else if (IS_TK_KEYWORD(mType)) {
        out = KEYWORDS[mType - Token::Type::KEYWORDS_START - 1];
    } else if (IS_TK_PREPRO(mType)) {
        out = PREPROCESSORS[mType - Token::Type::PREPROCESSOR_START - 1];
    } else if(IS_TK_DEFINED(mType))  {
        out = "defined";
    } else if(IS_TK_IDNTIFIER(mType) || IS_TK_NUMBER(mType)) {
        out =  GetSTRING();
    } else if(IS_TK_INT8(mType)) {
        char tmp = (char)(GetINT8());
        out =  '\'';
        switch(tmp) {
            case '\a':  out +=  "\\a"; break;
            case '\b':  out +=  "\\b"; break;
            case '\f':  out +=  "\\f"; break;
            case '\n':  out +=  "\\n"; break;
            case '\r':  out +=  "\\r"; break;
            case '\t':  out +=  "\\t"; break;
            case '\0':  out +=  "\\0"; break;
            case '\'':  out +=  "\\\""; break;
            case '\\':  out +=  "\\\\"; break;
            default:    out +=  tmp; break;
        }      
        out +=  '\'';      
    } 
    else if(IS_TK_STRING(mType)) {
        out =  '"';
        std::string str = GetSTRING();
        for(int i = 0; i < str.length(); ++i) {
            switch(str[i]) {
                case '\a':  out +=  "\\a"; break;
                case '\b':  out +=  "\\b"; break;
                case '\f':  out +=  "\\f"; break;
                case '\n':  out +=  "\\n"; break;
                case '\r':  out +=  "\\r"; break;
                case '\t':  out +=  "\\t"; break;
                case '\0':  out +=  "\\0"; break;
                case '"':   out +=  "\\\""; break;
                case '\\':  out +=  "\\\\"; break;
                default:    out +=  str[i]; break;
            }
        }
        out +=  '"';
    } else if(IS_TK_LINEBREAK(mType)) {
        out = '\n';
    } else if(IS_TK_ARGUMENT_REPLACE(mType))  {
        std::stringstream ss;
        ss << "arg(" << GetINT32() << ')';
        out =  ss.str();
    } else if(mType == Token::Type::UNKNOWN_TOKEN) {
        out = GetINT8();
    } 
}

