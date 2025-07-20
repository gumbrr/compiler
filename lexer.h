#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <iostream>
#include <unordered_set>

enum class Tokentype {
    number_token,
    operator_token,
    identifier_token,
    string_token,
    keyword_token,
    left_paren_token,
    right_paren_token,
    eof_token,
    unknown_token
};

enum class State {
    start_state,
    number_state,
    identifier_state,
    string_state,
    operator_state
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
    std::unordered_set<std::string> keywords = {"if", "else", "while", "for", "return", "break", "continue","true", "false", "null"};

    char lookahead();
    char consume();
    bool is_finished();
    void ignore_whitespace();
    Token match_token();
};

#endif 
