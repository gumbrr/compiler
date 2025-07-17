#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <iostream>

enum class Tokentype {
    number_token,
    operator_token,
    identifier_token,
    string_token,
    eof_token,
    unknown_token
};

enum class State {
    start_state,
    number_state,
    identifier_state,
    string_state,
    operator_state
    //accept_state
};

struct Position {
    int row;
    int column;
};

struct Token {
    Tokentype lexical_unit;
    std::string lexeme;
    Position position;
};

class Lexer {
public:
    Lexer(const std::string& input);
    std::vector<Token> tokenize();

private:
    std::string input;
    size_t input_position;
    Position token_position;

    char lookahead();
    char consume();
    bool is_finished();
    void ignore_whitespace();
    Token match_token();
};

#endif 
