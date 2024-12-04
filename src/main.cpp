#include "Token.h"
#include <fstream>
#include <ostream>

int main(int argc, char** argv) {
    if(argc < 2)
        return 0;
    
    if(!ScanBegin(argv[1])) return 0;
    TokenList *list = new TokenList(); 
    PreLex(list);
    ScanEnd();
    list->PreProcessor();
    std::stringstream ss;
    list->PrintTokens(ss, true);
    delete list;
    std::cout << "//\n" << ss.str();
    std::ofstream file(std::string(argv[1]) + ".c");
    file << ss.rdbuf();
    return 0;
}