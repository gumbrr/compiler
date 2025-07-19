#include "debug.h"

std::string Debug::token_type_to_string(Tokentype type) {
    switch (type) {
        case Tokentype::number_token: return "number";
        case Tokentype::operator_token: return "operator";
        case Tokentype::identifier_token: return "identifier";
        case Tokentype::string_token: return "string";
        case Tokentype::eof_token: return "eof";
        case Tokentype::unknown_token: return "unknown";
        default: return "invalid";
    }
}

void Debug::print_tokens(const std::string& input) {
    std::cout << "input: \"" << input << "\"\n";
    Lexer lexer(input);
    auto tokens = lexer.tokenize();
    for (const auto& token : tokens) {
        std::cout << "token(" << Debug::token_type_to_string(token.lexical_unit)
                  << ", " << token.lexeme << " "
                  << ",  " << token.position.row << ":" << token.position.column
                  << ")\n";
    }
    std::cout << "--------\n";
}
