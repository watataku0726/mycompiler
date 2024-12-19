#include "TokenList.h"


#include "IntNode.h"
#include "preparser.hh"

const Token* TokenList::GetHead() const { return mHead; }

const Token* TokenList::GetTail() const { return mTail; }


TokenList::TokenList()
    :mLine(1), mError(0), mWarning(0), mLength(0), mSpace(0)
{
    mHead = new Token(Token::Type::START_TOKEN, false, 0, 0, 0, 0);
    mTail = mHead;
}

TokenList::~TokenList() {
    //delete mHead;
    Token* t = mHead, *t1 = nullptr;
    while(1) {
        if(t == nullptr)
            break;
        t1 = t->GetNext();
        delete t;
        t = t1; 
    }
    mHead = nullptr;
    mTail = nullptr;

    for(auto macro : mMacroTable) {
        delete macro.second;
    }
}

void TokenList::Clear() {
    Token* tmp1 = mHead->GetNext(), *tmp2 = nullptr;
    while(tmp1 != nullptr) {
        tmp2 = tmp1->GetNext();
        delete tmp1;
        tmp1 = tmp2;
    }
    mHead->SetNext(nullptr);
    mTail = mHead;

    for(auto macro : mMacroTable) {
        delete macro.second;
    }
}

void TokenList::AddToken(Token::Type type) {
    Token* token;
    if(IS_TK_OPERATER(type)) 
        token = new Token(type, false, mLine, mStep, mLength, mSpace);
    else if(IS_TK_KEYWORD(type))
        token = new Token(type, true, mLine, mStep, mLength, mSpace);
    else if(IS_TK_PREPRO(type))
        token = new Token(type, true, mLine, mStep, mLength, mSpace);
    else if(IS_TK_DEFINED(type))
        token = new Token(type, true, mLine, mStep, mLength, mSpace);
    else {
        mSpace = 0;
        return;
    }
        
    //if(type == '(')
    //    std::cout << mStep << " : " << mLine << std::endl;
    mSpace = 0;
    mTail->SetNext(token);
    mTail = token;
}
#if(0)
void TokenList::AddKEYWORD(Token::Type type, std::string* keyword) {
    Token* token;
    if(IS_TK_KEYWORD(type)) 
        token = new Token(type, keyword, mLine, mStep);
    else
        return; 

    mTail->SetNext(token);
    mTail = token;
}
void TokenList::AddINT32(Token::Type type, int value) {
    Token* token = new Token(type, value, mLine, mStep);

    mTail->SetNext(token);
    mTail = token;
}

void TokenList::AddUINT32(unsigned value) {
    Token* token = new Token(Token::Type::TK_UINT32, value, mLine, mStep);

    mTail->SetNext(token);
    mTail = token;
}

void TokenList::AddINT64(long long value) {
    Token* token = new Token(Token::Type::TK_INT64, value, mLine, mStep);

    mTail->SetNext(token);
    mTail = token;
}

void TokenList::AddUINT64(unsigned long long value) {
    Token* token = new Token(Token::Type::TK_UINT64, value, mLine, mStep);

    mTail->SetNext(token);
    mTail = token;
}

void TokenList::AddFLOAT32(float value) {
    Token* token = new Token(Token::Type::TK_FLOAT32, value, mLine, mStep);
    
    mTail->SetNext(token);
    mTail = token;
}

void TokenList::AddFLOAT64(double value) {
    Token* token = new Token(Token::Type::TK_FLOAT64, value, mLine, mStep);
    
    mTail->SetNext(token);
    mTail = token;
}
#endif

void TokenList::AddNUMBER(Token::Type type, std::string* str) {
    Token* token = new Token(type, str, mLine, mStep, mLength, mSpace, false);

    mSpace = 0;
    mTail->SetNext(token);
    mTail = token;
}

void TokenList::AddCHARACTER(char value) {
    Token* token = new Token(Token::Type::TK_INT8, value, mLine, mStep, mLength, mSpace);
    
    mSpace = 0;
    mTail->SetNext(token);
    mTail = token;
}

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
    token = new Token(Token::Type::TK_INT8, tmp, mLine, mStep, mLength, mSpace);

    mSpace = 0;
    mTail->SetNext(token);
    mTail = token;
}

void TokenList::AddSTRING(std::string* str) {
    Token* token = new Token(Token::Type::TK_STRING, str, mLine, mStep, mLength, mSpace, false);
    
    mSpace = 0;
    mTail->SetNext(token);
    mTail = token;
}

void TokenList::AddIDENTIFIER(std::string* id) {
    Token* token = new Token(Token::Type::TK_IDNETIFIER, id, mLine, mStep, mLength, mSpace, true);
    //std::cout << *id << mStep << " " << mLine << std::endl;
    mSpace = 0;
    mTail->SetNext(token);
    mTail = token;
}

void TokenList::AddUnknownToken(char value) {
    Token* token = new Token(Token::Type::UNKNOWN_TOKEN, value, mLine, mStep, mLength, mSpace);
    
    mSpace = 0;
    mTail->SetNext(token);
    mTail = token;
}

void TokenList::AddLineBreakToken() {
    Token* token = new Token(Token::Type::TK_LINEBREAK, false, mLine, mStep, mLength, mSpace);

    mSpace = 0;
    mTail->SetNext(token);
    mTail = token;
}

void TokenList::Queue(Token* token) {
    if(token == nullptr) {
        mTail->SetNext(nullptr);
    } else {
        mTail->SetNext(token);
        mTail = token;
    }

}

Token* TokenList::Dequeue() {
    Token* token = mHead->GetNext();
    if(token != nullptr) {
        if(token == mTail) {
            mTail = mHead;
        }    
        mHead->SetNext(token->GetNext());
    }

    return token;
}

void TokenList::PrintTokens(std::stringstream& ss, bool number) {
    std::string str;
    unsigned line = 1;
    
    for(Token* token = mHead; token != nullptr; token = token->GetNext()) {
        token->GetContent(str);
        for(int i = 0; i < token->GetSpace(); ++i)
            ss << " ";
        ss << str;
    }
}

void TokenList::PreProcessor() {
    Token *token = mHead->GetNext(), *prev = mHead;
    Token::Type type;
    bool erasue;
    State state = State::INITIAL;
    Token* hash = nullptr;

    while(1) {
        //std::cout << type << " " << state << std::endl;
        if(token == nullptr)
            break;
        type = token->GetType();
        erasue = false;
        switch(state) {
            case State::INITIAL: {
                if(token->IsReplace() /*&& !IS_TK_DEFINED(type)*/) {
                    /*Macro Replace*/
                    if(!ReplaceToken(prev, token)) {
                        ConvertPrePro2ID(prev, token);
                    } 
                } else if(type == Token::Type::TK_HASH) {
                    if(prev == mHead || IS_TK_LINEBREAK(prev->GetType())) {
                        state = State::PREPRO;
                        hash = token;
                        prev->SetNext(token->GetNext());
                        token = prev;
                        //erasue = true;
                    } else 
                        Error(token->GetLine(), token->GetStep(), "Unsupported character : \"#\"");
                    
                } else if(type == Token::Type::TK_DOUBLEHASH) {
                    Error(token->GetLine(), token->GetStep(), "Unsupported character : \"##\"");
                    //erasue = true;
                }
                /*else if(type == Token::Type::UNKNOWN_TOKEN) {
                    std::string str;
                    str += token->GetINT8();
                    Error(token->GetLine(), token->GetStep(), "Unknown character : \"" + str + "\"");
                    erasue = true;
                } */
                break;
            }
            case State::PREPRO: {
                switch(type) {
                    case Token::Type::TK_DEFINE:
                        state = State::DEFINE;
                        erasue = true;
                        break;
                    case Token::Type::TK_UNDEF:
                        state = State::UNDEF;
                        erasue = true;
                        break;
                    case Token::Type::TK_IF:
                        state = State::IF;
                        erasue = true;
                        break;
                    case Token::Type::TK_IFDEF:
                        state = State::IFDEF;
                        erasue = true;
                        break;
                    case Token::Type::TK_IFNDEF:
                        state = State::IFNDEF;
                        erasue = true;
                        break;
                    case Token::Type::TK_INCLUDE:
                        state = State::INCLUDE;
                        erasue = true;
                        break;
                    default: {
                        std::string str;
                        token->GetContent(str);
                        Error(token->GetLine(), token->GetStep(), "invalid preprocessing directive: #" + str);
                        //GotoNextLineBreak(prev, token);
                        //Token* tmp = new Token((Token::Type)('#'), 0, prev->GetLine() + 1, 0);
                        //prev->SetNext(tmp);
                        //tmp->SetNext(token);
                        prev->SetNext(hash);
                        hash->SetNext(token);
                        prev = hash;
                        state = State::INITIAL;
                    }    
                    }
                break;
            }
            case State::DEFINE: {
                Define(prev, token, type);
                state = State::INITIAL;
                break;
            }
            case State::UNDEF: {
                if(token->IsReplace() && !IS_TK_DEFINED(type)) {
                    ErauseMacroTable(token->GetSTRING());
                    GotoNextLineBreak(prev, token);
                    type = token->GetType();
                } else {
                    if(IS_TK_LINEBREAK(type)) {
                        Error(token->GetLine(), token->GetStep(), " no macro name given in #undef directive");
                    } else{
                        std::string str;
                        token->GetContent(str);
                        Error(token->GetLine(), token->GetStep(), "\""+ str + "\" cannot be used as a macro");
                    }
                    GotoNextLineBreak(prev, token);
                    type = token->GetType();
                }
                state = State::INITIAL;
                break;
            }
            case State::IF: 
            case State::IFDEF:
            case State::IFNDEF: {
                If(prev, token, state);
                state = State::INITIAL;
                break;
            }
            case State::INCLUDE: {

                state = State::INITIAL;
                break;
            }
        }

        if(erasue) {
            delete hash;
            hash = nullptr;
            if(prev == nullptr) {
                mHead = token->GetNext();
                delete token;
                token = mHead;
            } else {
                prev->SetNext(token->GetNext());
                delete token;
                token = prev->GetNext();
            }
        } else {
            prev = token;
            token = token->GetNext();
        }
    }
#if !defined(NDEBUG)
    for(auto mac : mMacroTable) {
        std::cout << mac.first << "\n\t";
        Token* tmp = mac.second->head;
        while(tmp != nullptr) {
            std::string str;
            tmp->GetContent(str);
            std::cout << str << " ";
            tmp = tmp->GetNext();
        }
        std::cout << std::endl;
    }
#endif
}

void TokenList::Define(Token* prev, Token*& token, Token::Type& type) {
    if(token->IsReplace() && !IS_TK_DEFINED(type)) {
        std::string macroName;
        token->GetContent(macroName);
        Token* tmp = token->GetNext();
        if(tmp == nullptr || IS_TK_LINEBREAK(tmp->GetType())) {
            RegObjectMacroTable(macroName, nullptr);
            GotoNextLineBreak(prev, token);
        } else {
            if(tmp->GetType() == (Token::Type)('(') && (tmp->GetStep() - token->GetStep()) == 1) {
                    //std::cout << "not3" << std::endl;
                Token* tmp2;
                bool isID = true;
                Argument* arglist = nullptr, *tail = nullptr;
                delete token;
                if(tmp->GetNext() != nullptr &&tmp->GetNext()->GetType() == (Token::Type)(')'))
                    isID = false;
                else {
                    while(1) {
                        tmp2 = tmp->GetNext();
                        delete tmp;
                        tmp = tmp2;
                        if(tmp == nullptr || IS_TK_LINEBREAK(tmp->GetType())) {
                            if(isID)
                                Error(tmp->GetLine(), tmp->GetStep(), "expected parameter name before end of line");
                            else
                                Error(tmp->GetLine(), tmp->GetStep(), " expected ')' before end of line");
                            isID = true;
                            break;
                        }
                        if(isID) {
                            if(tmp->IsReplace()) {
                                Argument* arg;
                                if(IS_TK_IDNTIFIER(tmp->GetType())) {
                                    arg = new Argument(Token::Type::TK_IDNETIFIER, tmp->GetSTRING());
                                } else arg = new Argument(tmp->GetType());
                                
                                if(arglist == nullptr) {
                                    arglist = arg;
                                    tail = arg;
                                } else {
                                    tail->next = arg;
                                    tail = arg;
                                }
                            } else break;
                            isID = false;
                        } else {
                            if(tmp->GetType() == (Token::Type)(')'))
                                break;
                            isID = true;
                            if(tmp->GetType() != (Token::Type)(',')) {
                                std::string str;
                                tmp->GetContent(str);
                                Error(tmp->GetLine(), tmp->GetStep(), "expected ',' or ')', found " + str );
                                break;
                            }
                                
                        }  
                    }
                }
                if(!isID) { // OK
                    tmp2 = tmp->GetNext();
                    delete tmp;
                    tmp = tmp2;
                    Token* contentStart = nullptr;
                    if(tmp != nullptr && !IS_TK_LINEBREAK(tmp->GetType())) {
                        contentStart = tmp;
                        while(1) {
                            tmp2 = tmp->GetNext();
                            if(tmp2 == nullptr) {
                                tmp = tmp2;
                                break;
                            } else if(IS_TK_LINEBREAK(tmp2->GetType())) {
                                tmp->SetNext(nullptr);
                                tmp = tmp2;//->GetNext();
                                //delete tmp2;
                                tmp2 = nullptr;
                                break;
                            }
                            tmp = tmp2;
                        }
                    } 
                    prev->SetNext(tmp);
                    token = prev;
                    type = token->GetType();
                    RegFunctionMacroTable(macroName, arglist, contentStart);
                } else { // Error
                    while(1) {
                        if(arglist == nullptr)
                            break;
                        Argument* tmp = arglist->next;
                        delete arglist;
                        arglist = tmp;
                    }
                }
                tmp2 = tmp->GetNext();
                prev->SetNext(tmp2);
                token = prev;
                type = token->GetType();
            } else {
                Token* tmp2 = nullptr;
                Token* contentStart = tmp;
                while(1) {
                    tmp2 = tmp->GetNext();
                    if(tmp2 == nullptr) {
                        tmp = tmp2;
                        break;
                    } else if(IS_TK_LINEBREAK(tmp2->GetType())) {
                        tmp->SetNext(nullptr);
                        tmp = tmp2;//->GetNext();
                        //delete tmp2;
                        tmp2 = nullptr;
                        break;
                    }
                    tmp = tmp2;
                }
                prev->SetNext(tmp);
                token = prev;
                type = token->GetType();
                RegObjectMacroTable(macroName, contentStart);
            }
        }
    } else {
        if(IS_TK_LINEBREAK(type)) {
            Error(token->GetLine(), token->GetStep(), " no macro name given in #define directive");
        } else{
            std::string str;
            token->GetContent(str);
            Error(token->GetLine(), token->GetStep(), "\""+ str + "\" cannot be used as a macro");
        }
        GotoNextLineBreak(prev, token);
        type = token->GetType();
    }
    
}

void TokenList::Erasue(Token* prev, Token*& token) {
    if(prev == nullptr) {
        mHead = token->GetNext();
        delete token;
        token = nullptr;
    } else if(prev->GetNext() == token) {
        prev->SetNext(token->GetNext());
        delete token;
        token = prev;
    }
}

void TokenList::GotoNextLineBreak(Token* prev, Token*& token) {
    Token::Type type = token->GetType();
    while( token != nullptr && !IS_TK_LINEBREAK(type)) {
        Token* tmp = token->GetNext();
        delete token;
        token = tmp;
        type = token->GetType();
    }
#if(0)
    if(token != nullptr) {
        std::cout << "goood" << std::endl;
        Token* tmp = token->GetNext();
        delete token;
        token = tmp;
    }
#endif
    prev->SetNext(token);
    token = prev;
      
}

void TokenList::ConvertPrePro2ID(Token* prev, Token*& token) {
    Token::Type type = token->GetType();
    if(IS_TK_PREPRO(type)) {
        std::string* str = new std::string();
        token->GetContent(*str);
        /*switch(type) {
            case Token::Type::TK_DEFINE:    *str = "define";  break;
            case Token::Type::TK_UNDEF:     *str = "undef"; break;
            case Token::Type::TK_ELIF:      *str = "elif"; break;
            case Token::Type::TK_IFDEF:     *str = "ifdef"; break;
            case Token::Type::TK_IFNDEF:    *str = "ifndef"; break;
            case Token::Type::TK_ENDIF:     *str = "endif"; break;
            case Token::Type::TK_INCLUDE:   *str = "include"; break;   
            default:    delete str; str == nullptr; break;
        }*/
        if(str) {
            Token* tmp = new Token(Token::Type::TK_IDNETIFIER, str, token->GetLine(), token->GetStep(), token->GetLength(), token->GetSpace());
            tmp->SetNext(token->GetNext());
            prev->SetNext(tmp);
            delete token;
            token = tmp;
        }
    } else if(IS_TK_DEFINED(type)) {
        std::string* str = new std::string("defined");
        Token* tmp = new Token(Token::Type::TK_IDNETIFIER, str, token->GetLine(), token->GetStep(), token->GetLength(), token->GetSpace(), false);
        tmp->SetNext(token->GetNext());
        prev->SetNext(tmp);
        delete token;
        token = tmp;
    }
}

void TokenList::RegObjectMacroTable(const std::string& name, Token* head) {
    Token start(Token::Type::START_TOKEN, false, 0, 0, 0, 0);
    Token* prev = &start, *token = head;
    start.SetNext(head);
    bool error = false;

    if(token !=  nullptr && token->GetType() == Token::Type::TK_DOUBLEHASH) {
        Error(token->GetLine(), token->GetStep(), "'##' cannot appear at either end of a macro expansion");
        error = true;
    }

    while(token != nullptr) {
        if(token->IsReplace()) {
            if(!ReplaceToken(prev, token)) {
                ConvertPrePro2ID(prev, token);
            }
        }
        prev = token;
        token = token->GetNext();
    }

    if(prev !=  nullptr && prev->GetType() == Token::Type::TK_DOUBLEHASH) {
        Error(prev->GetLine(), prev->GetStep(), "'##' cannot appear at either end of a macro expansion");
        error = true;
    }

    MacroContent* cont = new MacroContent(start.GetNext(), false, 0);
    if(error) {
        delete cont;
        return;
    }
    auto iter = mMacroTable.find(name);
    if(iter != mMacroTable.end()) {
        Warnig(start.GetNext()->GetLine(), 0, "\"" + name + "\" redefined");
        delete iter->second;
        iter->second = cont;
    } else {
        mMacroTable.emplace(name, cont);
    }
    
#if(0)
    Token* tmp;
    while(1) {
        if(head == nullptr)
            break;
        tmp = head->GetNext();
        delete head;
        head = tmp;
    }
#endif
}

void TokenList::RegFunctionMacroTable(const std::string& name, Argument* arglist, Token* head) {
    Token start(Token::Type::START_TOKEN, false, 0, 0, 0, 0);
    Token* prev = &start, *token = head;
    int argNum = 0;
    start.SetNext(head);
    bool error = false;
    while(1) {
        Argument* arg = arglist;
        if(arg == nullptr)
            break;
        arglist = arg->next;
        prev = &start;
        token = prev->GetNext();
        while(token != nullptr) {
            if(token->IsReplace()) {
                if(token->GetType() == arg->type) {
                    if(!IS_TK_IDNTIFIER(arg->type) || (IS_TK_IDNTIFIER(arg->type) && (token->GetSTRING() == arg->str))) {
                        Token* tmp = new Token(Token::Type::TK_ARGUMENT_REPLACE, argNum, token->GetLine(), token->GetStep(), token->GetLength(), token->GetSpace());
                        tmp->SetNext(token->GetNext());
                        prev->SetNext(tmp);
                        delete token;
                        token = tmp;
                    }
                }
            }
            prev = token;
            token = token->GetNext();
        }
        ++argNum;
        delete arg;
    }

    prev = &start;
    token = prev->GetNext();
    if(token !=  nullptr && token->GetType() == Token::Type::TK_DOUBLEHASH) {
        Error(token->GetLine(), token->GetStep(), "'##' cannot appear at either end of a macro expansion");
        error = true;
    }

    while(token != nullptr) {
        if(token->IsReplace()) {
            if(!ReplaceToken(prev, token)) {
                ConvertPrePro2ID(prev, token);
            }
        } /*else if(token->GetType() == Token::Type::UNKNOWN_TOKEN) {
            std::string str;
            str += token->GetINT8();
            Error(token->GetLine(), token->GetStep(), "Unknown character : \"" + str + "\"");
        } */else if(token->GetType() == (Token::Type)('#')) {
            Token* tmp = token->GetNext();
            if(IS_TK_ARGUMENT_REPLACE(tmp->GetType())) {
                tmp->ChangeArg2Str();
                prev->SetNext(tmp);
                delete token;
                token = tmp;
            } else {
                Error(token->GetLine(), token->GetStep(), "'#' is not followed by a macro parameter");
                error = true;
            }
        }
        prev = token;
        token = token->GetNext();
    }

    if(prev !=  nullptr && prev->GetType() == Token::Type::TK_DOUBLEHASH) {
        Error(prev->GetLine(), prev->GetStep(), "'##' cannot appear at either end of a macro expansion");
        error = true;
    }

    MacroContent* cont = new MacroContent(start.GetNext(), true, argNum);
    if(error) {
        delete cont;
        return;
    }
    auto iter = mMacroTable.find(name);
    if(iter != mMacroTable.end()) {
        Warnig(start.GetNext()->GetLine(), 0, "\"" + name + "\" redefined");
        delete iter->second;
        iter->second = cont;
    } else {
        mMacroTable.emplace(name, cont);
    }
#if (0)    
    Token* tmp;
    while(1) {
        if(head == nullptr)
            break;
        tmp = head->GetNext();
        delete head;
        head = tmp;
    }
#endif
}

void TokenList::ErauseMacroTable(const std::string& name) {
    mMacroTable.erase(name);
}

void TokenList::DeleteTokens(std::vector<Token*>& vec){
    for(Token* token : vec) {
        Token *tmp = token, *tmp2 = nullptr;
        while(1) {
            if(tmp == nullptr)
                break;
            tmp2 = tmp->GetNext();
            delete tmp;
            tmp = tmp2;
        }
    }
    vec.clear();
}

Token* TokenList::CopyTokens(Token* head, Token*& out) {
    Token *ret = nullptr;
    if(head != nullptr) {
        Token* tmp = head->GetNext(), *tmp2 = nullptr, *tmp3 = nullptr;
        out = new Token(head);
        tmp2 = out;
        while(1) {
            if(tmp == nullptr)
                break;
            tmp3 = new Token(tmp);
            tmp2->SetNext(tmp3);
            tmp = tmp->GetNext();
            tmp2 = tmp3;
        }
        ret = tmp2;
    } else out = nullptr;
    
    return ret;
}

TokenList* TokenList::PastTokens(Token* opr1, Token* opr2) {
    std::string str = "", str1 = "", str2 = "";
    TokenList* list = new TokenList();
    if(!IS_TK_LINEBREAK(opr1->GetType()))
        opr1->GetContent(str1);
    if(!IS_TK_LINEBREAK(opr2->GetType()))
        opr2->GetContent(str2);
    str = str1 + str2;
    ScanString(str, list);

    return list;//new Token(Token::Type::TK_COMBINED_ID, str,opr1->GetLine(), opr1->GetStep());
    //return new Token(Token::Type::TK_IDNETIFIER, str,opr1->GetLine(), opr1->GetStep());
}

bool TokenList::ReplaceToken(Token* prev, Token*& token) {
    //std::cout << (token->GetType() != Token::Type::TK_IDNETIFIER ? "" : token->GetSTRING()) << std::endl;
    bool ret = false;
    std::string name;
    token->GetContent(name);
    auto iter = mMacroTable.find(name);
    Token* start = nullptr;
    if(iter != mMacroTable.end()) {
        if(iter->second->isFunction) {
            std::vector<Token*> vec(iter->second->numArgs, nullptr);
            Token *tmp1 = token->GetNext();
            if(tmp1 != nullptr && tmp1->GetType() == (Token::Type)('(')) {
                int num = 0, depth = 0;
                Token *head = nullptr, *tmp2 = tmp1->GetNext();
                tmp1->SetNext(nullptr);
                while(1) {
                    //std::cout << depth << std::endl;
                    if(tmp2 == nullptr) {
                        DeleteTokens(vec);
                        break;
                    } else if(tmp2->GetType() == (Token::Type)(')')) {
                        if(depth != 0) {
                            --depth;
                            tmp1 = tmp2;
                            tmp2 = tmp1->GetNext();
                        }
                        else {
                            tmp1->SetNext(nullptr);
                            vec[num++] = head;
                            delete token->GetNext();
                            token->SetNext(tmp2->GetNext());
                            delete tmp2;
                            tmp1 = tmp2 = nullptr;
                            if(iter->second->numArgs != num) {
                                std::stringstream ss;
                                ss  << "macro \"" << token->GetSTRING() << "\" requires " 
                                    << iter->second->numArgs << " arguments, but only " << num << "given";
                                Error(token->GetLine(), token->GetStep(), ss.str());
                                DeleteTokens(vec);
                            } else {
                                ret = true;
                            }
                            break;
                        }
                    } else if(tmp2->GetType() == (Token::Type)(',')) {
                        tmp1->SetNext(nullptr);
                        vec[num++] = head;
                        head = nullptr;
                        tmp1 = tmp2;
                        tmp2 = tmp1->GetNext();
                    } else {
                        if(tmp2->GetType() == (Token::Type)('('))
                            ++depth;

                        if(head == nullptr)
                            head = tmp2;
                        tmp1 = tmp2;
                        tmp2 = tmp1->GetNext();
                    }
                }
            }
            //std::cout << "owata" << std::endl;
            if(ret) {
                Token* tmp3 = nullptr, *tmp4 = nullptr;
                Token tk(Token::Type::START_TOKEN, 0, 0, 0, 0, 0);
                CopyTokens(iter->second->head, tmp3);
                tk.SetNext(tmp3);
                tmp4 = tmp3;
                tmp3 = &tk;
                start = &tk;
                while(1) {
                    if(tmp4 == nullptr)
                        break;

                    if(IS_TK_ARGUMENT_REPLACE(tmp4->GetType())) {
                        int idx = tmp4->GetINT32();
                        Token* tmp5 = nullptr, *tmp6 = CopyTokens(vec[idx], tmp5);
                        if(tmp5 != nullptr) {
                            tmp3->SetNext(tmp5);
                            tmp6->SetNext(tmp4->GetNext());
                            delete tmp4;
                            tmp4 = tmp6;
                        } else {
                            tmp3->SetNext(tmp4->GetNext());
                            delete tmp4;
                            tmp4 = tmp3;
                        }
                    } else if(IS_TK_ARGUMENT_REPLACE_STR(tmp4->GetType())) {
                        std::string* str = new std::string(""), tmpstr;
                        int idx = tmp4->GetINT32();
                        Token* tmp5 = vec[idx];
                        bool space = false;
                        while(tmp5 != nullptr) {
                            //std::cout << "owatea" << std::endl;
                            if(!IS_TK_LINEBREAK(tmp5->GetType())) {
                                tmp5->GetContent(tmpstr);
                                *str += tmpstr;
                                if(space)
                                    *str += " ";
                                space = true;
                            }
                            tmp5 = tmp5->GetNext();
                        }
                        tmp5 = new Token(Token::Type::TK_STRING, str, tmp4->GetLine(), tmp4->GetStep(), token->GetLength(), token->GetSpace());
                        tmp3->SetNext(tmp5);
                        tmp5->SetNext(tmp4->GetNext());
                        delete tmp4;
                        tmp4 = tmp5->GetNext();
                        if(tmp4 == nullptr)
                            break;
                    }

                    tmp3 = tmp4;
                    tmp4 = tmp4->GetNext();
                    
                }
                start = start->GetNext();
                DeleteTokens(vec);
            }
        } else {
            CopyTokens(iter->second->head, start);
            ret = true;
        }
    }

    if(ret) {              
        Token* tmp = start;
        if(tmp == nullptr) {
            prev->SetNext(token->GetNext());
            delete token;
            token = prev;
        } else {
            //std::cout << "owata" << std::endl;
            Token* tail = nullptr,  *pretail = nullptr;
            Token tk(Token::Type::START_TOKEN, 0, 0, 0, 0, 0);
            tk.SetNext(start);
            start = &tk;
            tail = start;
            //std::cout << "owata" << std::endl;
            while(1) {
                if(tmp == nullptr)
                    break;
                //std::cout << "owaeta" << std::endl;
                if(tmp->GetType() == Token::Type::TK_DOUBLEHASH) {
                    Token* tmp2 = tmp->GetNext();
                    if(tmp2 == nullptr) {
                        Error(tmp->GetLine(), tmp->GetStep(), "'##' cannot appear at either end of a macro expansion");
                    } else if(tmp2->GetType() == Token::Type::TK_DOUBLEHASH) {
                        delete tmp;
                        tail->SetNext(tmp2);
                        tmp = tail;
                        tail = pretail;
                    } else {
                        if(tail->GetType() == Token::Type::START_TOKEN) {
                            delete tmp;
                            tail->SetNext(tmp2);
                            tmp = tail;
                            tail = nullptr;
                            //std::cout << "OK2" << std::endl;
                        } else {
                            //std::cout << "OK" << std::endl;
                            TokenList* list = PastTokens(tail, tmp2);
                            if(list->mTail->GetType() != Token::Type::START_TOKEN) {
                                list->mTail->SetNext(tmp2->GetNext());
                                pretail->SetNext(list->mHead->GetNext());
                                list->mHead->SetNext(nullptr);
                                delete tmp, tmp2, tail;
                                tail = pretail;
                                tmp = list->mTail;
                            } 
                            /*tmp3->SetNext(tmp2->GetNext());
                            pretail->SetNext(tmp3);
                            delete tmp, tmp2, tail;
                            tail = pretail;
                            tmp = tmp3;*/
                            delete list;
                        }
                    }
                }
                pretail = tail;
                tail = tmp;
                tmp = tail->GetNext();
            }
            start = start->GetNext();
            prev->SetNext(start);
            tail->SetNext(token->GetNext());
            delete token;
            token = prev;
        }
    }

    return ret;
}


bool TokenList::ConstExpr(Token* prev, Token*& token) {
    TokenList list;// = new TokenList();
    Token* tmp1 = nullptr, *tmp2 = nullptr;
    int state = 0; // 0 : initial , 1 : defined, 2 : (, 3 : )
    bool erase = false, error = false, ret = false;
    list.mHead->SetNext(token);
    while(1) {
        list.mTail = token;
        if(token->GetNext() == nullptr) {
            Error(prev->GetLine() + 1, 0, "unterminated #if");
            //delete list;
            prev->SetNext(nullptr);
            token = nullptr;
            return false;
        }
        token = token->GetNext();
        if(IS_TK_LINEBREAK(token->GetType())) {
            prev->SetNext(token);
            list.mTail->SetNext(nullptr);
            break;
        }
    }
    tmp1 = list.mHead;
    tmp2 = list.mHead->GetNext();
    while(tmp2 != nullptr) {
        switch(state) {
            // initial
            case 0 : {
                if(IS_TK_DEFINED(tmp2->GetType())) {
                    state = 1;
                    erase = true;
                } else if(tmp2->IsReplace() && !ReplaceToken(tmp1, tmp2)) {
                    ConvertPrePro2ID(tmp1, tmp2);
                }
                break;
            }
            //defined
            case 1 : {
                if(tmp2->IsReplace()) {
                    std::string str;
                    Token *tk;
                    Token::Type type;
                    tmp2->GetContent(str);
                    type = (mMacroTable.find(str) == mMacroTable.end()) ? Token::Type::TK_FALSE : Token::Type::TK_TRUE;
                    tk = new Token(type, false, tmp2->GetLine(), tmp2->GetStep(), tmp2->GetLength(), tmp2->GetSpace());
                    tk->SetNext(tmp2->GetNext());
                    tmp1->SetNext(tk);
                    delete tmp2;
                    tmp2 = tk;
                    state = 0;
                } else if(tmp2->GetType() == (Token::Type)('(')) {
                    state = 2;
                    erase = true;
                } else {
                    Error(tmp2->GetLine(), tmp2->GetStep(), "operator \"defined\" requires an identifier");
                    error = true;
                }
                break;
            }
            // (
            case 2 : {
                if(tmp2->IsReplace()) {
                    std::string str;
                    Token *tk;
                    Token::Type type;
                    tmp2->GetContent(str);
                    type = (mMacroTable.find(str) == mMacroTable.end()) ? Token::Type::TK_FALSE : Token::Type::TK_TRUE;
                    tk = new Token(type, false, tmp2->GetLine(), tmp2->GetStep(), tmp2->GetLength(), tmp2->GetSpace());
                    tk->SetNext(tmp2->GetNext());
                    tmp1->SetNext(tk);
                    delete tmp2;
                    tmp2 = tk;
                    state = 3;
                } else {
                    Error(tmp2->GetLine(), tmp2->GetStep(), "operator \"defined\" requires an identifier");
                    error = true;
                }
                break;
            }
            // )
            case 3 : {
                if(tmp2->GetType() == (Token::Type)(')')) {
                    state = 0;
                    erase = true;
                } else {
                    Error(tmp2->GetLine(), tmp2->GetStep(), "missing ')' after \"defined\"");
                    error = true;
                }
                break;
            }
        }
        if(error)
            break;

        if(erase) {
            tmp1->SetNext(tmp2->GetNext());
            delete tmp2;
            tmp2 = tmp1->GetNext();
            erase = false;
        } else {
            tmp1 = tmp2;
            tmp2 = tmp1->GetNext();
        }
    }
    
    if(!error && state == 0) {
        Integer i;
        yy1::parser parser(&list, i);
        int errorNum = parser.parse();
        if(list.mError != 0 || errorNum != 0) 
            error = true;
        else
            ret = !i.IsZero();
    } else if (state == 1 || state == 2) {
        Error(list.mTail->GetLine(), list.mTail->GetStep(), "operator \"defined\" requires an identifier");
    } else if (state == 3) {
        Error(list.mTail->GetLine(), list.mTail->GetStep(), "missing ')' after \"defined\"");
    }
    //delete list;
    return error ? false : ret;
}

TokenList::NextIF TokenList::GetIfBlock(Token* prev, Token*&token, TokenList& out, bool isValid) {
    enum LocalState{
        INITIAL,
        LINEBREAK,
        HASH,
    } state = LocalState::INITIAL;
    Token::Type type;
    Token* hash = nullptr;
    int depth = 0;
    NextIF ret  = NextIF::ENDIF;
    bool halt = false;


    while(token != nullptr) {
        type = token->GetType();
        std::string str;
        token->GetContent(str);
        switch(state) {
            case LocalState::INITIAL: {
                if(IS_TK_LINEBREAK(type))
                    state = LocalState::LINEBREAK;
                out.Queue(token);
            }
            break;
            case LocalState::LINEBREAK: {
                if(type == (Token::Type)('#')) {
                    state = LocalState::HASH;
                    hash = token;
                } else if(IS_TK_LINEBREAK(type)) {
                    out.Queue(token);
                } else {
                    state = LocalState::INITIAL;
                    out.Queue(token);
                }
            }
            break;
            case LocalState::HASH: {
                if(type == Token::Type::TK_IF) {
                    out.Queue(hash);
                    out.Queue(token);
                    ++depth;
                    hash = nullptr;
                } else if(type == Token::Type::TK_ELIF) {
                    if(depth == 0) {
                        halt = true;
                        ret = NextIF::ELIF;
                    } else {
                        out.Queue(hash);
                        out.Queue(token);
                        hash = nullptr;
                    }
                } else if(type == Token::Type::TK_ELSE) {
                    if(depth == 0) {
                        halt = true;
                        ret = NextIF::ELSE;
                    } else {
                        out.Queue(hash);
                        out.Queue(token);
                        hash = nullptr;
                    }
                } else if(type == Token::Type::TK_ENDIF) {
                    if(depth == 0) {
                        halt = true;
                        ret = NextIF::ENDIF;
                    } else {
                        out.Queue(hash);
                        out.Queue(token);
                        --depth;
                        hash = nullptr;
                    }
                } else {
                    out.Queue(hash);
                    out.Queue(token);
                    hash = nullptr;
                }
                state = LocalState::INITIAL;
            }
            break;
            default:
                break;
        }
        
        if(halt) {
            delete hash;
            hash = nullptr;
            prev->SetNext(token->GetNext());
            delete token;
            token = prev->GetNext();
            out.Queue(nullptr);
            break;
        }
        else
            token = token->GetNext();
    }

    if(!halt) {
        Error(prev->GetLine() + 1, 0, "unterminated #if");
        prev->SetNext(nullptr);
        return NextIF::ERROR;
    }

    return ret;
}

void TokenList::If(Token* prev, Token*& token, State state) {
    bool isvalid = false;
    TokenList list; 
    while(1) {
        switch(state) {
            case State::IF: {
                isvalid = ConstExpr(prev, token);
                break;
            }
            case State::IFDEF: {
                if(!token->IsReplace()) {
                    Error(token->GetLine(), token->GetStep(), "macro names must be identifiers");
                } else {
                    std::string str;
                    token->GetContent(str);
                    isvalid = (mMacroTable.find(str) != mMacroTable.end());
                    GotoNextLineBreak(prev, token);
                    token = prev->GetNext();
                }
                break;
            }
            case State::IFNDEF: {
                if(!token->IsReplace()) {
                    Error(token->GetLine(), token->GetStep(), "macro names must be identifiers");
                } else {
                    std::string str;
                    token->GetContent(str);
                    isvalid = (mMacroTable.find(str) == mMacroTable.end());
                    GotoNextLineBreak(prev, token);
                    token = prev->GetNext();
                }
                break;
            }
            default:
                return;
        }

        if(token == nullptr) {
            return;
        }

        NextIF ret = GetIfBlock(prev, token, list, isvalid);
        if(ret == NextIF::ERROR) 
            break;

        if(isvalid) {
            Token* tmp1 = nullptr;
            list.mTail->SetNext(token);
            prev->SetNext(list.mHead->GetNext());
            list.mHead->SetNext(nullptr);
            tmp1 = list.mTail;
            list.mTail = list.mHead;
            if(ret != NextIF::ENDIF) {
                while((ret = GetIfBlock(tmp1, token, list, false)) != NextIF::ENDIF && ret != NextIF::ERROR) {
                    list.Clear();
                }
                list.Clear();
                
            }
            
        } else {
            list.Clear();
        }

        if(ret == NextIF::ENDIF || token == nullptr)
            break;
        else if(ret == NextIF::ELSE) {
            ret = GetIfBlock(prev, token, list, isvalid);
            if(ret != NextIF::ENDIF) {
                break;
            } else {
                list.mTail->SetNext(token);
                prev->SetNext(list.mHead->GetNext());
                list.mHead->SetNext(nullptr);
                list.mTail = list.mHead;
                break;
            }
        }
        state = State::IF;
    }
    token = prev;
}