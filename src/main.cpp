#include "Token.h"


int main(int argc, char** argv) {
    if(argc < 2)
        return 0;
    
    if(!ScanBegin(argv[1])) return 0;
    TokenList *list = new TokenList(); 
    PreLex(list);
    ScanEnd();
    std::stringstream ss;
    list->PrintTokens(ss);
    std::cout << ss.rdbuf();
    delete list;
    return 0;
}