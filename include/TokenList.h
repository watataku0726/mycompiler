#if !defined(__TOKENLIST_H__)
#define __TOKENLIST_H__
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>

#include "Token.h"

#define YY_DECL   void PreLex(class TokenList* list)

YY_DECL;

bool ScanBegin(const std::string& filename);
void ScanEnd();
void ScanString(const std::string& str, TokenList* list);



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
    void AddSpace(int space) { mSpace = space; }
    
    const Token* GetHead() const;
    const Token* GetTail() const;
    unsigned GetLine() const { return mLine; }
    int GetStep() const { return mStep; }
    void LineBreak() { ++mLine; mStep = 0; }
    void Step(int length) { mStep += length; mLength = length; }
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
    void Clear();
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
    enum NextIF {
        ELIF = 1,
        ELSE = 2,
        ENDIF = 0,
        ERROR = -1,
    } ;
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
    NextIF GetIfBlock(Token* prev, Token*&token, TokenList& out, bool isValid); 
    void Queue(Token* token);

    void Define(Token* prev, Token*& token, Token::Type& type);
    void If(Token* prev, Token*& token, State state);
private:
    std::unordered_map<std::string, MacroContent*> mMacroTable;
    Token* mHead;
    Token* mTail;
    unsigned mLine;
    int mStep;
    int mLength;
    int mSpace;
    unsigned mError;
    unsigned mWarning;
};



#endif // !__TOKENLIST_H__

#if(0)
void TokenList::PrintTokens(std::stringstream& ss, bool number) {
    unsigned line = 1;
    if(number)
        ss << line++ << " ";
    for(Token* token = mHead; token != nullptr; token = token->GetNext()) {
        bool space = true;
        Token::Type type = token->GetType();
        if(IS_TK_SHORT_OPERATER(type))
            ss << (char)type;
        else if(IS_TK_LONG_OPERATER(type)||IS_TK_KEYWORD(type) || IS_TK_PREPRO(type) || IS_TK_DEFINED(type)) {
            switch(type) {
                case Token::Type::TK_LOGAND:        ss << "&&"; break;
                case Token::Type::TK_LOGOR:         ss << "||"; break;
                case Token::Type::TK_EQ:            ss << "=="; break;
                case Token::Type::TK_NE:            ss << "!="; break;
                case Token::Type::TK_GE:            ss << ">="; break;
                case Token::Type::TK_LE:            ss << "<="; break;
                case Token::Type::TK_LSHIFT:        ss << "<<"; break;
                case Token::Type::TK_RSHIFT:        ss << ">>"; break;
                case Token::Type::TK_ADD_ASSIGN:    ss << "+="; break;
                case Token::Type::TK_SUB_ASSIGN:    ss << "-="; break;
                case Token::Type::TK_MUL_ASSIGN:    ss << "*="; break;
                case Token::Type::TK_DIV_ASSIGN:    ss << "/="; break;
                case Token::Type::TK_MOD_ASSIGN:    ss << "%="; break;
                case Token::Type::TK_AND_ASSIGN:    ss << "&="; break;
                case Token::Type::TK_OR_ASSIGN:     ss << "|="; break;
                case Token::Type::TK_EXOR_ASSIGN:   ss << "^="; break;
                case Token::Type::TK_LSHIFT_ASSIGN: ss << "<<="; break;
                case Token::Type::TK_RSHIFT_ASSIGN: ss << ">>="; break;
                case Token::Type::TK_INCREMENT:     ss << "++"; break;
                case Token::Type::TK_DECREMENT:     ss << "--"; break;
                case Token::Type::TK_ARROW:         ss << "->"; break;
                case Token::Type::TK_DOUBLECOLON:   ss << "::"; break;
                case Token::Type::TK_DOUBLEHASH:    ss << "##"; break;
                case Token::Type::TK_AUTO:          ss << "auto"; break;
                case Token::Type::TK_BREAK:         ss << "break"; break;
                case Token::Type::TK_CASE:          ss << "case"; break;
                case Token::Type::TK_CHAR:          ss << "char"; break;
                case Token::Type::TK_CONST:         ss << "const"; break;
                case Token::Type::TK_CONTINUE:      ss << "continue"; break;
                case Token::Type::TK_DEFAULT:       ss << "default"; break;
                case Token::Type::TK_DO:            ss << "do"; break;
                case Token::Type::TK_DOUBLE:        ss << "double"; break;
                case Token::Type::TK_ELSE:          ss << "else"; break;
                case Token::Type::TK_ENUM:          ss << "enum"; break;
                case Token::Type::TK_EXTERN:        ss << "extern"; break;
                case Token::Type::TK_FLOAT:         ss << "float"; break;
                case Token::Type::TK_FOR:           ss << "for"; break;
                case Token::Type::TK_GOTO: ss << "goto"; break;
                case Token::Type::TK_IF: ss << "if"; break;
                case Token::Type::TK_INT: ss << "int"; break;
                case Token::Type::TK_LONG: ss << "long"; break;
                case Token::Type::TK_REGISTER: ss << "register"; break;
                case Token::Type::TK_RETURN: ss << "return"; break;
                case Token::Type::TK_SIGNED: ss << "signed"; break;
                case Token::Type::TK_SIZEOF: ss << "sizeof"; break;
                case Token::Type::TK_SHORT: ss << "short"; break;
                case Token::Type::TK_STATIC: ss << "static"; break;
                case Token::Type::TK_STRUCT: ss << "struct"; break;
                case Token::Type::TK_SWITCH: ss << "switch"; break;
                case Token::Type::TK_TYPEDEF: ss << "typedef"; break;
                case Token::Type::TK_UNION: ss << "union"; break;
                case Token::Type::TK_UNSIGNED: ss << "unsigned"; break;
                case Token::Type::TK_VOID: ss << "void"; break;
                case Token::Type::TK_VOLATILE: ss << "volatile"; break;
                case Token::Type::TK_WHILE: ss << "while"; break;
                case Token::Type::TK_TRUE: ss << "true"; break;
                case Token::Type::TK_FALSE: ss << "false"; break;
                case Token::Type::TK_BOOL: ss << "bool"; break;
                case Token::Type::TK_NULLPTR: ss << "nullptr"; break;
                case Token::Type::TK_DEFINE: ss <<  "define"; break;
                case Token::Type::TK_UNDEF: ss <<  "undef"; break;
                case Token::Type::TK_DEFINED: ss <<  "defined"; break;
                case Token::Type::TK_ELIF: ss <<  "elif"; break;
                case Token::Type::TK_IFDEF: ss <<  "ifdef"; break;
                case Token::Type::TK_IFNDEF: ss <<"ifndef"; break;
                case Token::Type::TK_ENDIF: ss <<  "endif"; break;
                case Token::Type::TK_INCLUDE: ss <<  "include"; break;
            }
        } else if(IS_TK_IDNTIFIER(type) || IS_TK_NUMBER(type)) 
            ss << token->GetSTRING();
        else if(IS_TK_INT8(type)) {
            char tmp = (char)(token->GetINT8());
            ss << '\'';
            switch(tmp) {
                case '\a':  ss << "\\a"; break;
                case '\b':  ss << "\\b"; break;
                case '\f':  ss << "\\f"; break;
                case '\n':  ss << "\\n"; break;
                case '\r':  ss << "\\r"; break;
                case '\t':  ss << "\\t"; break;
                case '\0':  ss << "\\0"; break;
                case '\'':  ss << "\\\""; break;
                case '\\':  ss << "\\\\"; break;
                default:    ss << tmp; break;
            }      
            ss << '\'';      
        } else if(IS_TK_STRING(type)) {
            ss << '"';
            std::string str = token->GetSTRING();
            for(int i = 0; i < str.length(); ++i) {
                switch(str[i]) {
                    case '\a':  ss << "\\a"; break;
                    case '\b':  ss << "\\b"; break;
                    case '\f':  ss << "\\f"; break;
                    case '\n':  ss << "\\n"; break;
                    case '\r':  ss << "\\r"; break;
                    case '\t':  ss << "\\t"; break;
                    case '\0':  ss << "\\0"; break;
                    case '"':   ss << "\\\""; break;
                    case '\\':  ss << "\\\\"; break;
                    default:    ss << str[i]; break;
                }
            }
            ss << '"';
        } else if(IS_TK_LINEBREAK(type)){
            space = false;
            ss << '\n';
            if(number)
                ss << line++ << " ";
        } else if(type == Token::Type::UNKNOWN_TOKEN ) {
            ss << token->GetINT8();
        }
        
        /*
        Token* tmp = token->GetNext();
        if(tmp) {
            if(tmp->GetLine() == token->GetLine()) {
               int space = tmp->GetStep() - token->GetStep() - 1;
                std::cout << space << std::endl;;
                for(int i = 0; i < space; ++i) {
                    ss << ' ';
                } 
            }
        }*/
       if(space)
        ss << ' ';
    }
    ss << '\n';
}
#endif