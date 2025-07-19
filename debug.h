#ifndef DEBUG_H
#define DEBUG_H

#include "lexer.h"

class Debug {
public:
    static std::string token_type_to_string(Tokentype type);

    static void print_tokens(const std::string& input);
};

#endif
