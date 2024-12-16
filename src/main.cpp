#include "Token.h"
#include <fstream>
#include <ostream>
#include "preparser.hh"
#include "IntNode.h"


int main(int argc, char** argv) {
    if(argc < 2)
        return 0;

    if(!ScanBegin(argv[1])) return 0;
    TokenList *list = new TokenList(); 
    PreLex(list);
    ScanEnd();
#if(0)
    list->PreProcessor();
    std::stringstream ss;
    list->PrintTokens(ss, true);
    delete list;
    std::cout << "//\n" << ss.str();
    std::ofstream file(std::string(argv[1]) + ".c");
    file << ss.rdbuf();
#else
    Integer ret;
    yy1::parser parser(list, ret);
    int par = parser.parse();
    delete list;
    std::cout << ret.String() << std::endl;
#endif
    return 0;
}