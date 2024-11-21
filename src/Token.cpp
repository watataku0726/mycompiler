#include "Token.h"

Token::Token(Type type, unsigned line)
    :mType(type), mIsReplace(false), mLine(line), mNext(nullptr)
{
    mValue.sintval = 0;
}

Token::Token(Type type, char value, unsigned line)
    :mType(type), mIsReplace(false), mLine(line), mNext(nullptr)
{
    mValue.charval = value;
}

Token::Token(Type type, int value, unsigned line)
    :mType(type), mIsReplace(false), mLine(line), mNext(nullptr)
{
    mValue.sintval = value;
}

Token::Token(Type type, unsigned int value, unsigned line)
    :mType(type), mIsReplace(false), mLine(line), mNext(nullptr)
{
    mValue.uintval = value;
}

Token::Token(Type type, long long value, unsigned line)
    :mType(type), mIsReplace(false), mLine(line), mNext(nullptr)
{
    mValue.slonglongval = value;
}

Token::Token(Type type, unsigned long long value, unsigned line)
    :mType(type), mIsReplace(false), mLine(line), mNext(nullptr)
{
    mValue.ulonglongval = value;
}

Token::Token(Type type, float value, unsigned line)
    :mType(type), mIsReplace(false), mLine(line), mNext(nullptr)
{
    mValue.floatval = value;
}

Token::Token(Type type, double value, unsigned line)
    :mType(type), mIsReplace(false), mLine(line), mNext(nullptr)
{   
    mValue.doubleval = value;
}


Token::Token(Type type, std::string* value, unsigned line) 
    :mType(type), mIsReplace(true), mLine(line), mNext(nullptr)
{
    mValue.strval = value;
}

Token::~Token() {
    if(IS_TK_KEYWORD(mType) || IS_TK_IDNTIFIER(mType) || IS_TK_STRING(mType)) {
        delete mValue.strval;
        mValue.strval = nullptr;
    }
    delete mNext;
}

TokenList::TokenList()
    :mHead(nullptr), mTail(nullptr), mLine(1)
{}

TokenList::~TokenList() {
    delete mHead;
    mHead = nullptr;
    mTail = nullptr;
}

void TokenList::AddToken(Token::Type type) {
    Token* token;
    if(IS_TK_OPERATER(type)) 
        token = new Token(type, mLine);
    else
        return;
    
    if(mTail == nullptr) {
        mHead = token;
        mTail = token;
    } else {
        mTail->SetNext(token);
        mTail = token;
    }
}

void TokenList::AddKEYWORD(Token::Type type, std::string* keyword) {
    Token* token;
    if(IS_TK_KEYWORD(type)) 
        token = new Token(type, keyword, mLine);
    else
        return;

    if(mTail == nullptr) {
        mHead = token;
        mTail = token;
    } else {
        mTail->SetNext(token);
        mTail = token;
    }
}

void TokenList::AddINT32(int value) {
    Token* token = new Token(Token::Type::TK_INT32, value, mLine);

    if(mTail == nullptr) {
        mHead = token;
        mTail = token;
    } else {
        mTail->SetNext(token);
        mTail = token;
    }
}

void TokenList::AddUINT32(unsigned value) {
    Token* token = new Token(Token::Type::TK_UINT32, value, mLine);

    if(mTail == nullptr) {
        mHead = token;
        mTail = token;
    } else {
        mTail->SetNext(token);
        mTail = token;
    }
}

void TokenList::AddINT64(long long value) {
    Token* token = new Token(Token::Type::TK_INT64, value, mLine);

    if(mTail == nullptr) {
        mHead = token;
        mTail = token;
    } else {
        mTail->SetNext(token);
        mTail = token;
    }
}

void TokenList::AddUINT64(unsigned long long value) {
    Token* token = new Token(Token::Type::TK_UINT64, value, mLine);

    if(mTail == nullptr) {
        mHead = token;
        mTail = token;
    } else {
        mTail->SetNext(token);
        mTail = token;
    }
}

void TokenList::AddFLOAT32(float value) {
    Token* token = new Token(Token::Type::TK_FLOAT32, value, mLine);
    
    if(mTail == nullptr) {
        mHead = token;
        mTail = token;
    } else {
        mTail->SetNext(token);
        mTail = token;
    }
}

void TokenList::AddFLOAT64(double value) {
    Token* token = new Token(Token::Type::TK_FLOAT64, value, mLine);
    
    if(mTail == nullptr) {
        mHead = token;
        mTail = token;
    } else {
        mTail->SetNext(token);
        mTail = token;
    }
}

void TokenList::AddCHARACTER(char value) {
    Token* token = new Token(Token::Type::TK_INT8, value, mLine);
    
    if(mTail == nullptr) {
        mHead = token;
        mTail = token;
    } else {
        mTail->SetNext(token);
        mTail = token;
    }
}
//[abfnrt\\'\"?0]
void TokenList::AddSPECIALCHAR(char value) {
    Token* token;
    char tmp = value;
    switch(value) {
        case 'a':   tmp = '\a'; break;
        case 'b':   tmp = '\b'; break;
        case 'f':   tmp = '\f'; break;
        case 'n':   tmp = '\n'; break;
        case 'r':   tmp = '\r'; break;
        case 't':   tmp = '\t'; break;
        case '0':   tmp = '\0'; break;
        default:     break;
    }
    token = new Token(Token::Type::TK_INT8, tmp, mLine);

    if(mTail == nullptr) {
        mHead = token;
        mTail = token;
    } else {
        mTail->SetNext(token);
        mTail = token;
    }
}

void TokenList::AddSTRING(std::string* str) {
    Token* token = new Token(Token::Type::TK_STRING, str, mLine);
    
    if(mTail == nullptr) {
        mHead = token;
        mTail = token;
    } else {
        mTail->SetNext(token);
        mTail = token;
    }
}

void TokenList::AddIDENTIFIER(std::string* id) {
    Token* token = new Token(Token::Type::TK_IDNETIFIER, id, mLine);
    
    if(mTail == nullptr) {
        mHead = token;
        mTail = token;
    } else {
        mTail->SetNext(token);
        mTail = token;
    }
}

void TokenList::PrintTokens(std::stringstream& ss) {
    unsigned line = mHead->GetLine();
    for(const Token* token = mHead; token != nullptr; token = token->GetNext()) {
        if(line < token->GetLine()) {
            ss << '\n';
            line = token->GetLine();
        }
        const Token::Type type = token->GetType();
        if(IS_TK_SHORT_OPERATER(type))
            ss << (char)type;
        else if(IS_TK_LONG_OPERATER(type)) {
            std::string oper = "";
            switch(type) {
                case Token::Type::TK_LOGAND:        oper = "&&"; break;
                case Token::Type::TK_LOGOR:         oper = "||"; break;
                case Token::Type::TK_EQ:            oper = "=="; break;
                case Token::Type::TK_NE:            oper = "!="; break;
                case Token::Type::TK_GE:            oper = ">="; break;
                case Token::Type::TK_LE:            oper = "<="; break;
                case Token::Type::TK_LSHIFT:        oper = "<<"; break;
                case Token::Type::TK_RSHIFT:        oper = ">>"; break;
                case Token::Type::TK_ADD_ASSIGN:    oper = "+="; break;
                case Token::Type::TK_SUB_ASSIGN:    oper = "-="; break;
                case Token::Type::TK_MUL_ASSIGN:    oper = "*="; break;
                case Token::Type::TK_DIV_ASSIGN:    oper = "/="; break;
                case Token::Type::TK_MOD_ASSIGN:    oper = "%="; break;
                case Token::Type::TK_AND_ASSIGN:    oper = "&="; break;
                case Token::Type::TK_OR_ASSIGN:     oper = "|="; break;
                case Token::Type::TK_EXOR_ASSIGN:   oper = "^="; break;
                case Token::Type::TK_LSHIFT_ASSIGN: oper = "<<="; break;
                case Token::Type::TK_RSHIFT_ASSIGN: oper = ">>="; break;
                case Token::Type::TK_INCREMENT:     oper = "++"; break;
                case Token::Type::TK_DECREMENT:     oper = "--"; break;
                case Token::Type::TK_ARROW:         oper = "->"; break;
                case Token::Type::TK_DOUBLECOLON:   oper = "::"; break;
                case Token::Type::TK_DOUBLEHASH:    oper = "##"; break;
            }
            ss << oper;
        } else if(IS_TK_KEYWORD(type) || IS_TK_IDNTIFIER(type)) 
            ss << token->GetSTRING();
        else if(IS_TK_INT8(type))
            ss << (int)(token->GetINT8());
        else if(IS_TK_INT32(type))
            ss << token->GetINT32();
        else if(IS_TK_INT64(type))
            ss << token->GetINT64() << 'L';
        else if(IS_TK_UINT32(type))
            ss << token->GetUINT32() << 'U';
        else if(IS_TK_UINT64(type))
            ss << token->GetUINT64() << 'U' << 'L';
        else if(IS_TK_FLOAT32(type))
            ss << token->GetFLOAT32() << 'f';
        else if(IS_TK_FLOAT64(type))
            ss << token->GetFLOAT64();
        else if(IS_TK_STRING(type)) {
            ss << '"';
            std::string str = token->GetSTRING();
            for(int i = 0; i < str.length(); ++i) {
                switch(str[i]) {
                    case '\a':   ss << "\\a"; break;
                    case '\b':   ss << "\\b"; break;
                    case '\f':   ss << "\\f"; break;
                    case '\n':   ss << "\\n"; break;
                    case '\r':   ss << "\\r"; break;
                    case '\t':   ss << "\\t"; break;
                    case '\0':   ss << "\\0"; break;
                    default:  ss << str[i]; break;
                }
            }
            ss << '"';
        } else {

        }
        ss << ' ';
    }
    ss << '\n';
}