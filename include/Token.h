#if !defined(__TOKEN_H__)
#define __TOKEN_H__
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>

#define IS_TK_OPERATER(type) (0 < (type) && (type) < Token::Type::OPERATER_END)
#define IS_TK_SHORT_OPERATER(type) (0 < (type) && (type) < Token::Type::OPERATER_START)
#define IS_TK_LONG_OPERATER(type) ((Token::Type::OPERATER_START < (type)) && ((type) < Token::Type::OPERATER_END))
#define IS_TK_KEYWORD(type) ((Token::Type::KEYWORDS_START < (type)) && ((type) < Token::Type::KEYWORDS_END))
#define IS_TK_NUMBER(type) ((Token::Type::NUMBER_START < (type)) && ((type) < Token::Type::NUMBER_END))
#define IS_TK_IDNTIFIER(type) ((type) == Token::TK_IDNETIFIER)
#define IS_TK_PREPRO(type)  ((Token::Type::START_PREPROCESSOR < (type) && (type) < Token::Type::END_PREPROCESSOR))
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

#define YY_DECL   void PreLex(class TokenList* list)

YY_DECL;

bool ScanBegin(const std::string& filename);
void ScanEnd();
void ScanString(const std::string& str, TokenList* list);

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
        TK_NULLPTR,
        KEYWORDS_END  = 0x200,

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
        NUMBER_END = 0x300,
        TK_INT32,
        TK_UINT32,
        TK_INT64,
        TK_UINT64,

        TK_STRING = 0x400,
        TK_INT8,
        TK_BOOLEAN,

        TK_IDNETIFIER = 0x500, // [_a-zA-Z][_a-zA-Z0-9]*

        START_PREPROCESSOR = 0x601,
        TK_DEFINE,
        TK_UNDEF,
        TK_ELIF,
        TK_IFDEF,
        TK_IFNDEF,
        TK_ENDIF,
        TK_INCLUDE,
        END_PREPROCESSOR = 0x700,

        TK_LINEBREAK = 0x800,
        TK_DEFINED = 0x801,

        TK_ARGUMENT_REPLACE = 0x900,
        TK_ARGUMENT_REPLACE_STR = 0x901,

        END_OF_FILE = 0x1000,
        UNKNOWN_TOKEN = ~0,
        START_TOKEN = 0
    };
    

public:
    Token(Token* token);
    Token(Type type, bool isReplace, unsigned line, int step, int length);
    Token(Type type, char value, unsigned line, int step, int length);
    Token(Type type, int value, unsigned line, int step, int length);
    //Token(Type type, unsigned int value, unsigned line, int step);
    //Token(Type type, long long value, unsigned line, int step);
    //Token(Type type, unsigned long long value, unsigned line, int step);
    //Token(Type type, float value, unsigned line, int step);
    //Token(Type type, double value, unsigned line, int step);
    Token(Type type, std::string* value, unsigned line, int step, int legth, bool isReplace = true);
    ~Token();

    void SetNext(Token* next) { mNext = next; }
    Token* GetNext() const { return mNext; }
    bool IsReplace() const { return mIsReplace; }
    Type GetType() const { return mType; }
    unsigned int GetLine() const { return mLine; }
    int GetStep() const { return mStep; }
    int GetLength() const { return mLength; }

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
    bool mIsReplace;
};

class TokenList {
public:
    TokenList();
    ~TokenList();

    void AddToken(Token::Type type);
    void AddNUMBER(Token::Type type, std::string* str);
#if(0)
    void AddINT32(Token::Type type, int value);
    void AddUINT32(Token::Type type, unsigned value);
    void AddINT64(Token::Type type, long long value);
    void AddUINT64(Token::Type type, unsigned long long value);
    void AddFLOAT32(float value);
    void AddFLOAT64(double value);
#endif
    void AddCHARACTER(char value);
    void AddSPECIALCHAR(char value);
    void AddSTRING(std::string* str);
    void AddIDENTIFIER(std::string* id);
    //void AddKEYWORD(Token::Type type, std::string* keyword);
    void AddUnknownToken(char value);
    void AddLineBreakToken();
    
    const Token* GetHead() const { return mHead; }
    const Token* GetTail() const { return mTail; }
    unsigned GetLine() const { return mLine; }
    int GetStep() const { return mStep; }
    void LineBreak() { ++mLine; mStep = 0; }
    void Step(int length = 0) { mStep += length; mLength = length; }
    void Error(const std::string& str = "") { std::cerr << "error : line" << mLine << ":" << mStep << ": " << str << std::endl; ++mError; }
    void Error(unsigned line, int step, const std::string& str = "") {
        std::cerr << "error : line" << line << ":" << step << ": " << str << std::endl; ++mError;
    }
    void Warnig(const std::string& str = "") { std::cerr << "warnig : line" << mLine << ":" << mStep << ": " << str << std::endl; ++mWarning; }
    void Warnig(unsigned line, int step, const std::string& str = "") {
        std::cerr << "warnig : line" << line << ":" << step << ": " << str << std::endl; ++mWarning;
    }
    void PrintTokens(std::stringstream& ss, bool number = false);
    void PreProcessor();

    Token* Dequeue();
public:
#if(0)
    void StartPrePro(Token::Type type);
    void EndPrePro();

    void SetMacroContent(std::string* content);
    void SetIFContent(std::string* content);

    void SetMacroName(std::string* name);
    void AddMacroArg(std::string* arg);
    void AddMacroComma();

    void AddIFSpace();
    void AddIFExpr(Token::Type type);
    void AddIFIDENTIFIER(std::string* id);
    void AddIFUINT32(unsigned int value);
    void AddIFUINT64(unsigned long long value);
    void AddIFINT32(int value);
    void AddIFINT64(long long value);
    void AddElse();

    void SetIncludeFile(std::string* filename);
#endif
private:
    enum State {
        INITIAL,
        PREPRO,
        DEFINE,
        UNDEF,
        IF,
        IFDEF,
        IFNDEF,
        INCLUDE,
    };
    struct Argument {   
        Argument* next;
        Token::Type type;
        std::string str;
        Argument(Token::Type _type, const std::string& _str = "")
            :type(_type), str(_str), next(nullptr) {}
    };
    struct MacroContent {
        Token* head;
        int numArgs;
        bool isFunction;
        MacroContent(Token* _head, bool _isFunction, int _numArgs)
            :head(_head), isFunction(_isFunction), numArgs(_numArgs) {}
        ~MacroContent() {
            while(1) {
                if(head == nullptr)
                    break;
                Token* tmp = head->GetNext();
                delete head;
                head = tmp;
            }
        }
    };
    void Erasue(Token* prev, Token*& token);
    void RegObjectMacroTable(const std::string& name, Token* head);
    void RegFunctionMacroTable(const std::string& name, Argument* arglist, Token* head);
    void ErauseMacroTable(const std::string& name);
    bool ReplaceToken(Token* prev, Token*& token);
    void DeleteTokens(std::vector<Token*>& vec);
    Token* CopyTokens(Token* head, Token*& out);
    TokenList* PastTokens(Token* opr1, Token* opr2);
    
    void GotoNextLineBreak(Token* prev, Token*& token);
    void ConvertPrePro2ID(Token* prev, Token*& token);

    bool ConstExpr(Token* prev, Token*& token);

    void Define(Token* prev, Token*& token, Token::Type& type);
    void If(Token* prev, Token*& token, State state);
private:
    std::unordered_map<std::string, MacroContent*> mMacroTable;
    Token* mHead;
    Token* mTail;
    unsigned mLine;
    int mStep;
    int mLength;
    unsigned mError;
    unsigned mWarning;
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